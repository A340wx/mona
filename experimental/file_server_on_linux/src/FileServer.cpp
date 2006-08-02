#include "FileServer.h"

using namespace MonAPI;
using namespace std;

#define IRQ_PRIMARY   14
#define IRQ_SECONDARY 15

FileServer::FileServer()
{
    vmanager_ = new VnodeManager();
}

FileServer::~FileServer()
{
    delete vmanager_;
    delete rootFS_;
    for (FileSystems::iterator it = mountedFSs_.begin(); it != mountedFSs_.end(); it++)
    {
        delete (*it);
    }
    cd_->close();
    delete cd_;
    delete fd_;
}

int FileServer::initializeFileSystems()
{
    if (initializeRootFileSystem() != MONA_SUCCESS)
    {
        printf("initialize RootFileSystem error %s %s:%d\n", __func__, __FILE__, __LINE__);
        return MONA_FAILURE;
    }
    if (initializeMountedFileSystems() != MONA_SUCCESS)
    {
        printf("initializeMountedFileSystems error %s %s:%d\n", __func__, __FILE__, __LINE__);
        return MONA_FAILURE;
    }
    vmanager_->setRoot(rootFS_->getRoot());
    return MONA_SUCCESS;
}

int FileServer::initializeMountedFileSystems()
{
    // ProcessFileSystem
    FileSystem* pfs = new ProcessFileSystem(vmanager_);
    if (pfs->initialize() != MONA_SUCCESS)
    {
        printf("ProcessFileSystem initialize Error\n");
        delete pfs;
        return MONA_FAILURE;
    }
    vmanager_->mount(rootFS_->getRoot(), "process", pfs->getRoot());
    mountedFSs_.push_back(pfs);

    // FAT12FileSystem
    fd_ = new FDCDriver();
    FileSystem* ffs = new FAT12FileSystem(fd_, vmanager_);
    if (ffs->initialize() != MONA_SUCCESS)
    {
        printf("FAT12FileSystem initialize Error\n");
        delete ffs;
        return MONA_FAILURE;
    }
    vmanager_->mount(rootFS_->getRoot(), "fd", ffs->getRoot());
    mountedFSs_.push_back(ffs);
    return MONA_SUCCESS;
}

int FileServer::initializeRootFileSystem()
{
#ifdef ON_LINUX
    cd_ = new IDEDriver(IRQ_PRIMARY, IRQ_SECONDARY);
    cd_->open();
#else
    // user mode I/O
    syscall_get_io();

    // IDE Driver
    cd_ = new IDEDriver(IRQ_PRIMARY, IRQ_SECONDARY);

    // find CD-ROM
    int controller, deviceNo;
    if (!this->cd->findDevice(IDEDriver::DEVICE_ATAPI, 0x05, &controller, &deviceNo))
    {
        printf("CD-ROM Not Found\n");
        delete cd_;
        return MONA_FAILURE;
    }

    // set irq number
    byte irq = controller == IDEDriver::PRIMARY ? IRQ_PRIMARY : IRQ_SECONDARY;

    // enable interrupts
    monapi_set_irq(irq, MONAPI_TRUE, MONAPI_TRUE);
    syscall_set_irq_receiver(irq);

    // CD Select Device
    if (!cd_->selectDevice(controller, deviceNo))
    {
        printf("select device NG error code = %d\n", this->cd->getLastError());
        delete this->cd;
        return MONA_FAILURE;
    }

#endif

    rootFS_ = new ISO9660FileSystem(cd_, vmanager_);
    if (rootFS_->initialize() != MONA_SUCCESS)
    {
        printf("CD Boot Initialize Error\n");
        delete rootFS_;
        delete cd_;
        return MONA_FAILURE;
    }
    return MONA_SUCCESS;
}

monapi_cmemoryinfo* FileServer::readFileAll(const string& file)
{
    dword fileID;
    dword tid = monapi_get_server_thread_id(ID_FILE_SERVER);
    int ret = vmanager_->open(file, 0, false, tid, &fileID);
    if (ret != MONA_SUCCESS) return NULL;

    Stat st;
    ret = vmanager_->stat(fileID, &st);
    if (ret != MONA_SUCCESS) return NULL;

    monapi_cmemoryinfo* mi;
    ret = vmanager_->read(fileID, st.size, &mi);
    if (ret != MONA_SUCCESS) return NULL;
    return mi;
}

void FileServer::messageLoop()
{
    for (MessageInfo msg;;)
    {
        if (Message::receive(&msg)) continue;

        switch (msg.header)
        {
        case MSG_VFS_FILE_OPEN:
        {
            dword tid = msg.from; // temporary
            dword fildID;
            bool create = msg.arg1 == MONAPI_TRUE;
            int ret = vmanager_->open(msg.str, 0, create, tid, &fildID);
            Message::reply(&msg, ret == MONA_SUCCESS ? fildID : MONA_FAILURE);
            break;
        }
        case MSG_VFS_FILE_SEEK:
        {
            int ret = vmanager_->seek(msg.arg1 /* fileID */, msg.arg2 /* offset */, msg.arg3 /* origin */);
            Message::reply(&msg, ret == MONA_SUCCESS ? MONA_SUCCESS : MONA_FAILURE);
            break;
        }
        case MSG_VFS_FILE_READ:
        {
            dword fileID = msg.arg1;
            monapi_cmemoryinfo* memory;
            int ret = vmanager_->read(fileID, msg.arg2 /* size */, &memory);
            if (ret != MONA_SUCCESS)
            {
                Message::reply(&msg, MONA_FAILURE);
            }
            else
            {
                Message::reply(&msg, memory->Handle, memory->Size);
            }
            break;
        }
        case MSG_VFS_FILE_WRITE:
        {
            printf("%s %s:%d\n", __func__, __FILE__, __LINE__);fflush(stdout);// debug
            dword fileID = msg.arg1;
            monapi_cmemoryinfo* memory;
            memory = monapi_cmemoryinfo_new();
            memory->Handle = msg.arg3;
            memory->Owner  = msg.from;
            memory->Size   = msg.arg2;
            monapi_cmemoryinfo_map(memory);
            int ret = vmanager_->write(fileID, msg.arg2 /* size */, memory);
//            monapi_cmemoryinfo_dispose(memory);
//            monapi_cmemoryinfo_delete(memory);
            Message::reply(&msg, ret);
            break;
        }
        case MSG_VFS_FILE_CLOSE:
        {
            int ret = vmanager_->close(msg.arg1);
            Message::reply(&msg, ret == MONA_SUCCESS ? MONA_SUCCESS : MONA_FAILURE);
            break;
        }
        case MSG_VFS_FILE_GET_SIZE:
        {
            Stat st;
            int ret = vmanager_->stat(msg.arg1, &st);
            Message::reply(&msg, ret == MONA_SUCCESS ? MONA_SUCCESS : MONA_FAILURE, st.size);
            break;
        }
        case MSG_VFS_FILE_READ_DIRECTORY:
        {
            monapi_cmemoryinfo* memory;
            int ret = vmanager_->readdir(msg.str, &memory);
            if (ret != MONA_SUCCESS)
            {
                Message::reply(&msg, MONA_FAILURE);
            }
            else
            {
                dword handle = memory->Handle;
                dword size = memory->Size;
                monapi_cmemoryinfo_delete(memory);
                Message::reply(&msg, handle, size);
            }
            break;
        }
        case MSG_STOP_SERVER:
            // end
            Message::reply(&msg, MONA_SUCCESS);
            return;
            break;
        default:
            break;
        }
    }
}

int64_t FileServer::GetST5DecompressedSize(monapi_cmemoryinfo* mi)
{
    int64_t ret = 0;
    ret = tek_checkformat(mi->Size, (unsigned char*)mi->Data);
    return ret;
}

monapi_cmemoryinfo* FileServer::ST5Decompress(monapi_cmemoryinfo* mi)
{
    int64_t size = GetST5DecompressedSize(mi);
    if (size < 0) return NULL;

    // if size >= 4GB abort...
    if ((size >> 32) > 0) return NULL;

    monapi_cmemoryinfo* ret = new monapi_cmemoryinfo();
    if (!monapi_cmemoryinfo_create(ret, (dword)(size + 1), 0))
    {
        monapi_cmemoryinfo_delete(ret);
        return NULL;
    }
    ret->Size--;

    if (tek_decode(mi->Size, mi->Data, ret->Data) != 0) {
        // Decompress failed
        monapi_cmemoryinfo_dispose(ret);
        monapi_cmemoryinfo_delete(ret);
        return NULL;
    }

    ret->Data[ret->Size] = 0;
    return ret;
}

monapi_cmemoryinfo* FileServer::ST5DecompressFile(const char* file)
{
    monapi_cmemoryinfo* mi = readFileAll(file);
    monapi_cmemoryinfo* ret = NULL;
    if (mi == NULL) return ret;

    ret = ST5Decompress(mi);
    monapi_cmemoryinfo_dispose(mi);
    monapi_cmemoryinfo_delete(mi);
    return ret;
}

/*!
    \file  elf.cpp
    \brief elf utility

    Copyright (c) 2003 Higepon
    All rights reserved.
    License=MIT/X Licnese

    \author  HigePon
    \version $Revision$
    \date   create:2003/09/06 update:$Date$
*/

#include <elf.h>
#include <string.h>
#include <global.h>
#include <io.h>
#include <syscalls.h>

#define SHARED_MM_ERROR -1
#define FAT_INIT_ERROR  -2
#define FAT_OPEN_ERROR  -3

// int loadProcess(const char* path, const char* file, bool isUser) {


//     static dword sharedId = 0x1000;
//     sharedId++;

//     int    fileSize;
//     int    readTimes;
//     byte*  buf;
//     bool   isOpen;
//     bool   isAttaced;
//     FAT12* fat;

//     while (Semaphore::down(&g_semaphore_shared));
//     isOpen = SharedMemoryObject::open(sharedId, 4096 * 5);
//     isAttaced = SharedMemoryObject::attach(sharedId, g_processManager->getCurrentProcess(), 0x80000000);
//     Semaphore::up(&g_semaphore_shared);

//     if (!isOpen || !isAttaced) return SHARED_MM_ERROR;

//     g_fdcdriver->motor(ON);
//     g_fdcdriver->recalibrate();
//     g_fdcdriver->recalibrate();
//     g_fdcdriver->recalibrate();

//     fat = new FAT12((DiskDriver*)g_fdcdriver);
//     if (!fat->initilize()) return FAT_INIT_ERROR;

//     if (!fat->open(path, file, FAT12::READ_MODE)) return FAT_OPEN_ERROR;

//     fileSize  = fat->getFileSize();

//     readTimes = fileSize / 512 + (fileSize % 512 ? 1 : 0);

//     buf = (byte*)malloc(512 * readTimes);

//     if (buf == NULL) return -1;

//     for (int i = 0; i < readTimes; i++) {
//         if (!fat->read(buf + 512 * i)) {
//             g_console->printf("read failed %d", i);
//             while (true);
//         }
//     }

//     if (!fat->close()) {
//         info(ERROR, "close failed");
//     }

//     ELFLoader* loader = new ELFLoader();

//     //    g_console->printf("elf size = %d", loader->prepare((dword)buf));
//     loader->prepare((dword)buf);

//     /* prod_ code */
//     dword entrypoint = loader->load((byte*)0x80000000);

//     //    g_console->printf("entrypoint=%x", entrypoint);
//     delete(loader);
//     free(buf);

//     Process* process = g_processManager->create(isUser ? ProcessManager::USER_PROCESS : ProcessManager::KERNEL_PROCESS, file);

//     while (Semaphore::down(&g_semaphore_shared));
//     isOpen = SharedMemoryObject::open(sharedId, 4096 * 5);
//     isAttaced = SharedMemoryObject::attach(sharedId, process, 0xA0000000);
//     Semaphore::up(&g_semaphore_shared);
//     if (!isOpen || !isAttaced) panic("loadProcess: not open");

//     while (Semaphore::down(&g_semaphore_shared));
//     SharedMemoryObject::detach(sharedId, g_processManager->getCurrentProcess());
//     Semaphore::up(&g_semaphore_shared);

//     g_processManager->add(process);
//     Thread*  thread = g_processManager->createThread(process, entrypoint);
//     g_processManager->join(process, thread);

//     return 0;
// }

/*----------------------------------------------------------------------
    loadProcess
----------------------------------------------------------------------*/
int loadProcess(const char* path, const char* file, bool isUser) {

    /* shared ID */
    static dword sharedId = 0x1000;
    sharedId++;

    int    fileSize;
    int    readTimes;
    bool   isOpen;
    bool   isAttaced;
    dword entrypoint;
    FAT12* fat;
    ELFLoader *loader;
    byte* buf;

    /* only one process can use fd */
    while (Semaphore::down(&g_semaphore_fd));
    g_fdcdriver->motor(ON);
    g_fdcdriver->recalibrate();
    g_fdcdriver->recalibrate();
    g_fdcdriver->recalibrate();

    /* read FAT */
    fat = new FAT12((DiskDriver*)g_fdcdriver);
    if (!fat->initilize()) {
        Semaphore::up(&g_semaphore_fd);
        return -1;
    }

    /* file open */
    if (!fat->open(path, file, FAT12::READ_MODE)) {
        delete fat;
        Semaphore::up(&g_semaphore_fd);
        return -1;
    }

    /* get file size and allocate buffer */
    fileSize  = fat->getFileSize();
    readTimes = fileSize / 512 + (fileSize % 512 ? 1 : 0);
    buf       = (byte*)malloc(512 * readTimes);
    if (buf == NULL) {
        delete fat;
        Semaphore::up(&g_semaphore_fd);
        return -1;
    }

    /* read */
    for (int i = 0; i < readTimes; i++) {
        if (!fat->read(buf + 512 * i)) {
            delete fat;
            free(buf);
            Semaphore::up(&g_semaphore_fd);
            return -1;
        }
    }

    /* close */
    if (!fat->close()) {
        delete fat;
        Semaphore::up(&g_semaphore_fd);
    }
    g_fdcdriver->motor(false);
    delete fat;
    Semaphore::up(&g_semaphore_fd);

    /* attach Shared to this process */
    while (Semaphore::down(&g_semaphore_shared));
    isOpen    = SharedMemoryObject::open(sharedId, 4096 * 5);
    isAttaced = SharedMemoryObject::attach(sharedId, g_processManager->getCurrentProcess(), 0x80000000);
    Semaphore::up(&g_semaphore_shared);
    if (!isOpen || !isAttaced) {
        free(buf);
        return -1;
    }

    /* load */
    loader = new ELFLoader();
    loader->prepare((dword)buf);
    entrypoint = loader->load((byte*)0x80000000);
    delete(loader);
    free(buf);

    /* create process */
    Process* process = g_processManager->create(isUser ? ProcessManager::USER_PROCESS : ProcessManager::KERNEL_PROCESS, file);

    /* attach binary image to process */
    while (Semaphore::down(&g_semaphore_shared));
    isOpen    = SharedMemoryObject::open(sharedId, 4096 * 5);
    isAttaced = SharedMemoryObject::attach(sharedId, process, 0xA0000000);
    Semaphore::up(&g_semaphore_shared);
    if (!isOpen || !isAttaced) {
        return -1;
    }

    /* detach from this process */
    while (Semaphore::down(&g_semaphore_shared));
    SharedMemoryObject::detach(sharedId, g_processManager->getCurrentProcess());
    Semaphore::up(&g_semaphore_shared);

    /* now process is loaded */
    g_processManager->add(process);
    Thread*  thread = g_processManager->createThread(process, entrypoint);
    g_processManager->join(process, thread);
    return 0;
}

ELFLoader::ELFLoader() {

}

ELFLoader::~ELFLoader() {

}

int ELFLoader::prepare(dword elf) {

    int size = 0;

    /* check ELF header */
    header_  = (ELFHeader*)elf;
    if (!isValidELF()) return errorCode_;

    /* Program Header */
    pheader_ = (ELFProgramHeader*)((dword)header_ + header_->phdrpos);

    /* get size of image */
    for (int i = 0; i < header_->phdrcnt; i++) {

        if (pheader_[i].type == PT_LOAD) {

            size += pheader_[i].memorysize;
        }
    }

    return size;
}

dword ELFLoader::load(byte* toAddress) {



    for (int i = 0; i < header_->phdrcnt; i++) {

        if (pheader_[i].type == PT_LOAD && pheader_[i].filesize == pheader_[i].memorysize) {

            memcpy((void*)(toAddress + pheader_[i].virtualaddr - pheader_->virtualaddr), (void*)((dword)header_ + pheader_[i].offset), pheader_[i].filesize);

        } else if (pheader_[i].type == PT_LOAD && pheader_[i].filesize != pheader_[i].memorysize) {

            memset((void*)(toAddress + pheader_[i].virtualaddr - header_->entrypoint), 0, pheader_[i].memorysize);
        }

    }

    return header_->entrypoint;
}

int ELFLoader::getErrorCode() const {

    return errorCode_;
}

bool ELFLoader::isValidELF() {

    /* check magic number */
    if (header_->magic[0] != 0x7F || header_->magic[1] != 'E'
        || header_->magic[2] != 'L' ||header_->magic[3] != 'F') {

        errorCode_ = ELF_ERROR_NOT_ELF;
        return false;
    }

    /* little endian, version 1, x86 */
    if (header_->clazz != 1 || header_->headerversion != 1 || header_->archtype != 3) {

        errorCode_ = ELF_ERORR_NOT_SUPPORTED_ELF;
        return false;
    }

    /* check executable */
    if (header_->type != 2) {

        errorCode_ = ELF_ERORR_NOT_EXECUTABLE;
        return false;
    }

    /* valid ELF */
    return true;
}

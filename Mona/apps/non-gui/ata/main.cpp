#include <monapi.h>
#include "IDEDriver.h"

using namespace MonAPI;

int MonaMain(List<char*>* pekoe)
{
    /* ��撡���������⒡���ɒ��I/O�����ޒ����蒡���� */
    syscall_get_io();

    /* �����󒥹��Ȓ�钥������ǒ�ϒ�ǒ�Ւ����뒥Ȓ��Primary:Master��Β�ǒ�В�������������򒤵��쒤ƒ����ޒ����蒡� */
    IDEDriver ide;

    /* ��쒱���ǒ�В�������������Ò�� */
    int type = ide.getDeviceType(IDEDriver::PRIMARY, IDEDriver::MASTER);

    if (type != IDEDriver::DEVICE_ATA)
    {
        printf("primary master device is not ATA\n");
        return 1;
    }

    char buf[1024];
    memset(buf, 0, sizeof(buf));

    /* lba 1������1024byte��ޒ�Ȓ�ᒤ蒤ߒ�����512byte���1�ñ��̒�ǒ�� */
    printf("read result = %d", ide.read(1, buf, 1024));

    /* ��ɒ�������ƒ��FD��˒�ݒ¸ */
    FileOutputStream fos("/HDD.LOG");
    fos.open();

    fos.write((byte*)buf      , 512);
    fos.write((byte*)(buf + 512), 512);

    fos.close();

    return 0;
}

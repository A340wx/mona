#include <userlib.h>

int MonaMain(List<char*>* pekoe)
{
    /* ��ͭ��������� */
    dword pid = Message::lookup("SHELL.SVR");

    /* ����ޥåץ��֥������ȼ��� */
    MemoryMap* mm = MemoryMap::create();

    /* ��ʬ��0x90005000��pid��0x90000000��1M�Х��ȥޥåԥ󥰤��� */
    dword sharedid = mm->map(pid, 0x90000000, 0x90005000, 1 * 1024 * 1024);

    /* ��ͭ���ꥢ�˽񤭹��� */
    strcpy((char*)0x90005000, "data share top");
    strcpy((char*)0x90095000, "data share bottom");

    //    mm->unmap(sharedid);

    for (;;);
}


// int MonaMain(List<char*>* pekoe)
// {
//     int result;
//     byte buf[32];

//     if (pekoe->isEmpty())
//     {
//         printf("usage: HELLO.ELF pathToFile\n");
//         return -1;
//     }

//     FileInputStream fis(pekoe->get(0));

//     if (0 != (result = fis.open()))
//     {
//         printf("can not open %s\n", pekoe->get(0));
//         return -1;
//     }

//     printf("file size = %d\n", fis.getFileSize());

//     if (fis.read(buf, 32))
//     {
//         printf("can not read %s\n", pekoe->get(0));
//         fis.close();
//         return -1;
//     }

//     printf("contents\n");
//     sleep(5000);

//     for (int i = 0; i < 32; i++)
//     {
//         printf("[%x]", buf[i]);
//     }

//     fis.close();

//     return 0;
// }

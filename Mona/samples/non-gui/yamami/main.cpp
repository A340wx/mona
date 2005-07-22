/*!
    \file   main.cpp
    \brief  Yamami Code:Mones �����[�X�O �e��e�X�g���W�b�N cvsadd
    
    cvs test

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/08/28 update:$Date$
*/

#include <sys/types.h>
#include <monapi.h>
#include <pci/Pci.h>
#include <sys/HashMap.h>

//���L�������g�p
#include <monapi/cmemoryinfo.h>

using namespace MonAPI;

#define MAIN_10






#ifdef MAIN_10

#include <monesoc/Socket.h>

//Code:Mones UDP���C�u���� �����O�����e�X�g
int MonaMain(List<char*>* pekoe)
{

    //�����ŁAMones�Ƀ��b�Z�[�W�𑗂�
    MessageInfo info;

    dword targetID = Message::lookupMainThread("MONES.EX5");
    if (targetID == 0xFFFFFFFF)
    {
        logprintf("MONES.EX5 not found\n");
        exit(1);
    }

    //Mones�֓o�^
    //�|�[�g2600�Ń��X��
    Message::create(&info, MSG_MONES_REGIST, 0, 2600, 0, NULL);
    // send
    if (Message::send(targetID, &info)) {
        logprintf("MSG_MONES_REGIST error\n");
    }
    
    
    /* Message loop */
    //�����Ń��b�Z�[�W���[�v���āA������҂��Ă݂�B
    for (;;)
    {
        /* receive */
        if (!Message::receive(&info))
        {
            
            switch(info.header)
            {
            case MSG_MONES_ICMP_NOTICE:
                //�Ԃ��Ă�����
                logprintf("Reply \n");
                
                Socket *soc;
                
                //���L������
                logprintf("use commonMem Handle = %d : Size = %d \n",info.arg2 , info.arg3);
                monapi_cmemoryinfo* cmSoc;

                cmSoc = monapi_cmemoryinfo_new();
                cmSoc->Handle = info.arg2;
                cmSoc->Size   = info.arg3;
                
                monapi_cmemoryinfo_map(cmSoc);
                
                //���L����������Socket�����o���B
                //logprintf("Pre memcpy(soc,cmSoc->Data\n");
                //soc = new Socket();
                //memcpy(soc,cmSoc->Data , sizeof(Socket));
                //logprintf("After memcpy(soc,cmSoc->Data\n");
                
                soc = (Socket*)cmSoc->Data;

                //Socket����A�p�P�b�g(�o�C�g��)�����o���B
                //UDP�́A�ő咴����Ɠǂݎ̂Ă�BTCP�̓t���[���䂪�K�v UDPSocket ��TCPSocket�̎d��
                packet_cmemoryinfo pcm;
                
                pcm = soc->getBuffer(0);
                
                logprintf("pcm = soc->getBuffer(0);Call!! \n");
                
                logprintf("use Pcm Handle = %d : Size = %d \n",pcm.Handle , pcm.Size);
                
                //soc->recvBuff->removeAt(0);


                //���L����������p�P�b�g �o�C�g ���擾                
                monapi_cmemoryinfo* cmPacByte;
                
                cmPacByte = monapi_cmemoryinfo_new();
                cmPacByte->Handle = pcm.Handle;
                cmPacByte->Size   = pcm.Size;
                monapi_cmemoryinfo_map(cmPacByte);                

                char buff[1024];
                
                memcpy(buff,cmPacByte->Data , sizeof(buff));                
                
                printf("%s\n",buff);
                
                //Socket�́A�A�v���ŋ��L������������Ȃ�!!
                //monapi_cmemoryinfo_dispose(cmSoc);
                //monapi_cmemoryinfo_delete(cmSoc);                

                monapi_cmemoryinfo_dispose(cmPacByte);
                monapi_cmemoryinfo_delete(cmPacByte);                
                
                
                return 0;
                
                break;

            default:
                /* igonore this message */
                break;
            }

        }
    }
    
    return 0;

}

#endif





#ifdef MAIN_9

class AlcTest
{
    public:
        int aaa;
        char bbb;
        byte mema[4096];
};



//�������A���P�[�^�e�X�g
int MonaMain(List<char*>* pekoe)
{

    byte *mem;
    
    //malloc
    mem = (byte*)malloc(4096);
    
    //free
    free(mem);
    
    //new
    PciInf *pciinfo;
    //PCI���C�u�����N���X�̃C���X�^���X��
    AlcTest* alc = new AlcTest();
    
    delete alc;
    
    return 0;
}

#endif





#ifdef MAIN_1

//Yamami FileOutputStream�g�p�e�X�g
int MonaMain(List<char*>* pekoe)
{
    //Yamami �e�X�g���W�b�N

    int reti;

    char buf[1024];
    memset(buf, 0, sizeof(buf));

    sprintf(buf , "protType:%04x \n",1234);

    //FileOutputStream �̃e�X�g
    FileOutputStream fos("YTEST.TXT");

    printf("fileout:open=%d\n", fos.open());

    reti = fos.write((byte*)buf , 512);
    printf("fileout:read=%d\n", reti);

    printf("fos close pre\n");
    fos.close();
    printf("fos close after\n");
    return 0;
}

#endif

#ifdef MAIN_2

//Yamami Pci���C�u�����g�p�e�X�g
int MonaMain(List<char*>* pekoe)
{
    PciInf *pciinfo;
    
    //PCI���C�u�����N���X�̃C���X�^���X��
    Pci* pcilib = new Pci();
    
    pciinfo = pcilib->CheckPciExist(0x10EC,0x8029);
    
    if(pciinfo->Exist == 0){
        //�f�o�C�X��������΁A���̏���\��
        //printf("VendorName=%s\n",(const char*)pciinfo->VendorName);
        //printf("DeviceName=%s\n",(const char*)pciinfo->DeviceName);
        printf("DeviceNo=%d\n",pciinfo->DeviceNo);
        printf("BaseAd=%x\n",pciinfo->BaseAd);
        printf("IrqLine=%x\n",pciinfo->IrqLine);
    }
    else{
        printf("Device Not Exist!! \n");
    }
    
    
    pciinfo = pcilib->CheckPciExist(0x10AA,0x80AA);
    
    if(pciinfo->Exist == 0){
        //�f�o�C�X��������΁A���̏���\��
        //printf("VendorName=%s\n",(const char*)pciinfo->VendorName);
        //printf("DeviceName=%s\n",(const char*)pciinfo->DeviceName);
        printf("DeviceNo=%d\n",pciinfo->DeviceNo);
        printf("BaseAd=%x\n",pciinfo->BaseAd);
        printf("IrqLine=%x\n",pciinfo->IrqLine);
    }
    else{
        printf("Device Not Exist!! \n");
    }
    
    return 0;

}

#endif


#ifdef MAIN_3

struct REPLY_WAIT{
    int ip;         /* Request IP address. */
    int repFlg;         /* Reply flag. */
    int wait;
    char mac[6];        /* Reply mac buffer. */
};

//HLIST�g�p�e�X�g
int MonaMain(List<char*>* pekoe)
{
    List<REPLY_WAIT*>* testList;
    REPLY_WAIT* addWork;
    
    testList = new HList<REPLY_WAIT*>();
    
    
    for (int i = 0; i < 1000; i++) {
        addWork = new REPLY_WAIT();
        addWork->ip = i;
        addWork->wait = i;
        sprintf(addWork->mac , "%d",i*2);
        
        //�����ŁAHList�֒ǉ�
        testList->add(addWork);
    }
    
//    for (int i = 0; i < testList->size() ; i++) {
//
//        REPLY_WAIT* p = testList->get(i);
//        
//        printf("ip=%d wait=%d mac=%s \n", p->ip , p->wait , p->mac);
//        
//        //���̌�A�����Ń��X�g����폜����Ƃǂ��Ȃ�H
//        testList->removeAt(i);
//        //�J�E���^�f�N�������g������B
//        i--;
//        
//    }
    
    REPLY_WAIT* getWork;
    
    //2�����Ƃ肾���Ă݂�B
    for (int i = 0; i < 2 ; i++) {
        getWork = testList->removeAt(0);
        printf("ip=%d wait=%d mac=%s \n", getWork->ip , getWork->wait , getWork->mac);
    }
    
    //�r���ǉ�
    addWork = new REPLY_WAIT();
    addWork->ip = 5;
    addWork->wait = 5;
    sprintf(addWork->mac , "%d",5*2);
    
    //�����ŁAHList�֒ǉ�
    testList->add(addWork);
    
    
    //�擪�v�f���A�Ƃ葱���������o���B
    while(testList->isEmpty() == false){
        getWork = testList->removeAt(0);
        logprintf("ip=%d wait=%d mac=%s \n", getWork->ip , getWork->wait , getWork->mac);
        logprintf("count=%d\n",testList->size());
    }
    
    
    printf("testList->size() = %d\n",testList->size());
    
    return 0;

}


#endif


#ifdef MAIN_4


//Yamami ���ȃ��b�Z�[�W�ʒm�e�X�g
int MonaMain(List<char*>* pekoe)
{

    MessageInfo info;

    // �e�X�g�T�[�o��ID��������
    dword targetID = Message::lookupMainThread("YAMAS.EX2");
    if (targetID == 0xFFFFFFFF)
    {
        printf("local!!!! yamas:INIT not found\n");
        exit(1);
    }

    // create message
    Message::create(&info, MSG_YAMATEST, 0, 0, 0, NULL);
    // send
    if (Message::send(targetID, &info)) {
        printf("local!!!! yamas:INIT error\n");
    }

    
    return 0;

}

#endif



#ifdef MAIN_5


struct REPLY_WAIT{
    int ip;         /* Request IP address. */
    int repFlg;         /* Reply flag. */
    int wait;
    char mac[6];        /* Reply mac buffer. */
};

//HashMap�g�p�e�X�g
int MonaMain(List<char*>* pekoe)
{
    HashMap<REPLY_WAIT*>* testHash;
    
    REPLY_WAIT* addWork;
    char IpKey[10];    //

    
    testHash = new HashMap<REPLY_WAIT*>(3);
    
    //for (int i = 0; i < 3; i++) {
    for (int i = 0; i < 5; i++) {
        //�v�f���𒴂���Ƃǂ��Ȃ�H�H
        addWork = new REPLY_WAIT();
        addWork->ip = i;
        addWork->wait = i;
        sprintf(addWork->mac , "%d",i*2);
        
        //IP�A�h���X���AMAP�̃L�[��(String��)
        sprintf(IpKey , "%08x",i);
        
        //�����ŁAHashMap�֒ǉ�
        testHash->put(IpKey , addWork);
        
    }
    
    //for (int i = 0; i < testHash->size() ; i++) {
    for (int i = 0; i < 5 ; i++) {

        //IP�A�h���X���AMAP�̃L�[��(String��)
        sprintf(IpKey , "%08x",i);

        REPLY_WAIT* p = testHash->get(IpKey);
        
        printf("ip=%d wait=%d mac=%s \n", p->ip , p->wait , p->mac);
        
    }
    
    return 0;

}

#endif



#ifdef MAIN_6

struct REPLY_WAIT{
    int ip;         /* Request IP address. */
    int repFlg;         /* Reply flag. */
    int wait;
    char mac[6];        /* Reply mac buffer. */
};

//���L�������e�X�g
int MonaMain(List<char*>* pekoe)
{
    
    //�܂��Amonapi_cmemoryinfo�\���̂�new
    monapi_cmemoryinfo* cmInfo = new monapi_cmemoryinfo();
    
    REPLY_WAIT* addWork;
    
    if (!monapi_cmemoryinfo_create(cmInfo, (dword)(sizeof(REPLY_WAIT) + 1), 0))
    {
        monapi_cmemoryinfo_delete(cmInfo);
        printf("monapi_cmemoryinfo_create error\n");
    }
    
    //���̎��_�ŉ����Z�b�g����Ă���H
    logprintf("monapi_cmemoryinfo_create after!!!\n");
    
    logprintf("cmInfo->Handle = %x\n",cmInfo->Handle);
    logprintf("cmInfo->Owner = %x\n",cmInfo->Owner);
    logprintf("cmInfo->Size = %x\n",cmInfo->Size);
    //���L���������}�b�v�AData�v�f�Ɋm�ۂ����o�C�g�񂪃Z�b�g�����B
    monapi_cmemoryinfo_map(cmInfo);
    
    logprintf("monapi_cmemoryinfo_map after!!!\n");
    
    //���ۂɋ��L�������ցA�������Z�b�g
    //addWork = new REPLY_WAIT();
    //���L�������\���̂�Data���A�ړI�̌^�փL���X�g
    addWork = (REPLY_WAIT*)cmInfo->Data;
    
    addWork->ip = 10;
    addWork->wait = 1;
    sprintf(addWork->mac , "%d",123);
    
    logprintf("cmemory use!! after!!!\n");
    
    logprintf("ClintSide!! ip=%d wait=%d mac=%s \n", addWork->ip , addWork->wait , addWork->mac);
    

    //�����ŁA�e�X�g�p�T�[�o�ɋ��L��������Handle�𑗂�
    MessageInfo info;

    dword targetID = Message::lookupMainThread("YAMAS.EX2");
    if (targetID == 0xFFFFFFFF)
    {
        printf("local!!!! yamas:INIT not found\n");
        exit(1);
    }

    // create message
    Message::create(&info, MSG_YAMATEST, cmInfo->Handle, cmInfo->Size, 0, NULL);
    // send
    if (Message::send(targetID, &info)) {
        printf("local!!!! yamas:INIT error\n");
    }

    
    
    return 0;

}

#endif




#ifdef MAIN_7

//IP�֘A�̃w�b�_�͂ǂ��ɒ�`���ׂ����H
//�Ƃ肠�����AMones����MoDefine��������include
#include "../../../src/servers/mones/MonesDefine.h"


//Code:Mones IP���M�e�X�g
int MonaMain(List<char*>* pekoe)
{

    if(pekoe->size() < 1){
        printf("Arguments is few!\n");
        printf("usage: ping host\n");
        return 0;
    }
    
    
    //printf("pekoe->get(0)=%s\n",pekoe->get(0));
    
    int a,b,c,d;
    
    sscanf(pekoe->get(0),"%d.%d.%d.%d",&a,&b,&c,&d);
    
    //printf("a=%d\n",a);
    //printf("b=%d\n",b);
    //printf("c=%d\n",c);
    //printf("d=%d\n",d);

    //IP�A�h���X�g�ݗ���
    dword ipaddr;
    ipaddr = 0;
    ipaddr = (byte)a;
    ipaddr = (ipaddr << 8) + (byte)b;
    ipaddr = (ipaddr << 8) + (byte)c;
    ipaddr = (ipaddr << 8) + (byte)d;
    
    printf("Pinding %s\n",pekoe->get(0));

    //�����ŁAMones�Ƀ��b�Z�[�W�𑗂�
    MessageInfo info;

    dword targetID = Message::lookupMainThread("MONES.EX5");
    if (targetID == 0xFFFFFFFF)
    {
        printf("MONES.EX5 not found\n");
        exit(1);
    }

    //Mones�֓o�^
    // create message
    Message::create(&info, MSG_MONES_REGIST, ipaddr, 0, 0, NULL);
    // send
    if (Message::send(targetID, &info)) {
        printf("MSG_MONES_REGIST error\n");
    }
    
    
    //IP���M
    // create message
    Message::create(&info, MSG_MONES_IP_SEND, 0, 0, 0, NULL);

    //ICMP�p�P�b�g�̍쐬
    int icmp_size;
    icmp_size=40;
    
    char icmp_buf[40];
    
    ICMP_HEADER *volatile icmpHead;
    icmpHead=(ICMP_HEADER*)icmp_buf;
    
    
    //data�̕���������
    memcpy(icmpHead->data , "abcdefghijklmnopqrstuvwabcdefghi",32);
    
    //ICMP�w�b�_�[�̐ݒ�
    icmpHead->type=ICMP_TYPE_ECHOREQ;
    icmpHead->code=0;
    //�`�F�b�N�T���͂����ł͌v�Z���Ȃ��BMones�ɔC����
    //icmpHead->chksum=0;
    //icmpHead->chksum=MoPacUtl::calcCheckSum((dword*)icmpHead,icmp_size);

    info.arg1 = 0;  //���L���������g�p���Ȃ�
    info.arg2 = ipaddr;
    
    memcpy(info.str , icmp_buf,icmp_size);
    info.length = icmp_size;


    // send
    if (Message::send(targetID, &info)) {
        printf("MSG_MONES_IP_SEND error\n");
    }
    
    
    /* Message loop */
    //�����Ń��b�Z�[�W���[�v���āA������҂��Ă݂�B
    for (;;)
    {
        /* receive */
        if (!Message::receive(&info))
        {
            
            switch(info.header)
            {
            case MSG_MONES_ICMP_NOTICE:
                //IP�v�����Ԃ��Ă�����
                printf("Reply from %s\n",pekoe->get(0));
                return 0;
                
                break;

            default:
                /* igonore this message */
                break;
            }

        }
    }
    
    return 0;

}

#endif


#ifdef MAIN_8

//logprintf ��'%' �o�̓e�X�g
int MonaMain(List<char*>* pekoe)
{

    printf("%c",'%');  //����
    printf("%c",'?');  //����
    printf("%c",'\\'); //����
    printf("%");       //����͏o�Ȃ����ǁA����Ő���B
    printf("\n");

    logprintf("%c",'%');  //�~�o�͂���Ȃ�!!!
    logprintf("%c",'?');  //����
    logprintf("%c",'\\'); //����
    logprintf("%");       //����͏o�Ȃ����ǁA����Ő���B
    logprintf("\n");

    char pacbuf[128];
    char drawBuff[128];
    
    pacbuf[0] = 0x7d;
    pacbuf[1] = 0x8d;
    
    
    for(int i = 0 ; i < 2 ; i++){
        sprintf(drawBuff , "%2x",(byte)pacbuf[i]);
        printf("%s\n",drawBuff);
    }
    
    return 0;
}

#endif

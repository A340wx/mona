/*!
    \file   main.cpp
    \brief  Yamami Code:Mones ping ���ǂ�
    
    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2005/05/09 update:$Date$
*/

//���� 2005/08/09���݁B�����Ȃ�!!! MonaMain�̈�������??

#include <sys/types.h>
#include <monapi.h>
#include <sys/HashMap.h>
#include <monalibc/stdio.h>

//IP�֘A�̃w�b�_�͂ǂ��ɒ�`���ׂ����H
//�Ƃ肠�����AMones����MoDefine��������include
#include "../../netprot/MonesDefine.h"


using namespace MonAPI;


//Code:Mones ICMP���M
int MonaMain(List<char*>* pekoe)
{

    if(pekoe->size() < 1){
        printf("Arguments is few!\n");
        printf("usage: ping host\n");
        return 0;
    }
    
    
    printf("pekoe->get(0)=%s\n",pekoe->get(0));
    
    int a,b,c,d;
    
    sscanf(pekoe->get(0),"%d.%d.%d.%d",&a,&b,&c,&d);
    
    printf("a=%d\n",a);
    printf("b=%d\n",b);
    printf("c=%d\n",c);
    printf("d=%d\n",d);

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

    info.arg1 = 1;  //IPPROTO_ICMP
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
                for(int i = 0 ; i < info.length ; i++){
                    printf("%x ",info.str[i]);
                }
                
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


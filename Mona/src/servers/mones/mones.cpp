/*!
  \file  mones.cpp
  \brief Code:Mones���C��

  Copyright (c) 2004 Yamami
  All rights reserved.
  License=MIT/X Licnese

  \author  Yamami
  \version $Revision$
  \date   create:2004/08/08 update:$Date$
*/


//�����ŁAMones�̃O���[�o���I�u�W�F�N�g���C���X�^���X������
#define MONES_GLOBAL_VALUE_DEFINED
#include "MonesGlobal.h"

#include <monapi.h>
#include "AbstractMonic.h"
#include "MoEther.h"
#include "MoIcmp.h"
#include "MonesConfig.h"
#include "MonesLoader.h"



using namespace MonAPI;


/*!
    \brief MonaMain
        Code:Mones���C��

    \param List<char*>* pekoe

    \author  Yamami
    \date    create:2004/08/08 update:2004/10/31
*/
int MonaMain(List<char*>* pekoe)
{
    
    //TO DO �Ƃ肠�����A30�v���Z�X�܂�OK 
    MonesRList = new HList<MONES_IP_REGIST*>();
    MONES_IP_REGIST *regist;
    
    //syscall_get_io  
    //���̃v���Z�X���쒆�́AIO��������x��3�܂ŋ�����
    syscall_get_io();
    
    // NIC�̃C���X�^���X��
    // MonesLoader�N���X�o�R�ŃC���X�^���X������B
    AbstractMonic* insAbstractNic;
    
    MonesLoader* insNicLoader = new MonesLoader();
    insNicLoader->setup();
    insAbstractNic = insNicLoader->getNicInstance();
    //NIC�̃��[�h�Ɏ��s�����ꍇ�́AMones�I��
    if(insAbstractNic == 0){
        printf("NIC Error Mones Quit \n");
        return 0;
    }
    
    //Ether�N���X�̃C���X�^���X��
    g_MoEther = new MoEther();
    g_MoEther->etherInit(insAbstractNic);

    //ARP�N���X�̃C���X�^���X��
    g_MoArp = new MoArp();
    g_MoArp->initArp(insAbstractNic);

    //IP�N���X�̃C���X�^���X��
    g_MoIp = new MoIp();
    g_MoIp->initIp(insAbstractNic);


    // initilize destination list
    //List<dword>* destList = new HList<dword>();
    MessageInfo info;

    // Server start ok
    dword targetID = Message::lookupMainThread("MONITOR.BIN");
    if (targetID == 0xFFFFFFFF)
    {
        printf("Mones:INIT not found\n");
        exit(1);
    }

    // create message
    Message::create(&info, MSG_SERVER_START_OK, 0, 0, 0, NULL);

    // send
    if (Message::send(targetID, &info)) {
        printf("Mones:INIT error\n");
    }

    //�l�b�g���[�N��IRQ�}�X�NEnable
    insAbstractNic->enableNetWork();

    //IRQ���V�[�o�Ƃ��ēo�^ (IRQ�́ANIC�h���C�o�N���X��蓾��)
    syscall_set_irq_receiver(insAbstractNic->getNicIRQ());

    /* Message loop */
    //�����Ń��b�Z�[�W���[�v
    for (;;)
    {
        /* receive */
        if (!Message::receive(&info))
        {
            
            switch(info.header)
            {
            case MSG_INTERRUPTED:
                
                //printf("MSG_INTERRUPTED\n");
                
                dword    i;
                
                //�p�P�b�g��M
                insAbstractNic->frame_input();
                
                //Ether�N���X�ɓo�^
                i = g_MoEther->setEtherFrame(insAbstractNic->frame_buf ,insAbstractNic->frame_len);
                //�C�[�T�l�b�g�t���[����M����
                i = g_MoEther->receiveEther();
                
                break;


            //Mones�֓o�^
            case MSG_MONES_REGIST:
            //case 5:
                
                printf("MSG_MONES_REGIST\n");
                
                //�ʐM�Ǘ����X�g�ɓo�^
                //TO DO TCP���T�|�[�g����΁A�{���́AIP�����ł͖����A�|�[�g�ԍ���
                regist = new MONES_IP_REGIST();
                regist->tid = info.from;
                regist->ip = info.arg1;
                
                MonesRList->add(regist);
                
                break;


            //Yamami!! TO DO �p�P�b�g���M�����A������
            //�A�v������̃p�P�b�g���M�v��
            case MSG_MONES_IP_SEND:
                //�p�P�b�g���M
                //TO DO �P���ɁA�����Ńe�X�g�p��IP�p�P�b�g���쐬�����M�v��
                printf("MSG_MONES_IP_SEND\n");
                
                int ret;
                dword ip;
                TRANS_BUF_INFO tbi;
                
                ICMP_HEADER *icmpHead;
                icmpHead = new ICMP_HEADER();
                
                //testPacket = new char(100);
                
                //���M�� 10.0.2.2(QEMU GW)
                ip = 0x0A000202;
                
                
                //ICMP�w�b�_�[�̐ݒ�
                icmpHead->type=ICMP_TYPE_ECHOREQ;
                icmpHead->code=0;
                icmpHead->chksum=0;
                //icmpHead->chksum=MoPacUtl::calcCheckSum((dword*)icmpHead,size);
                icmpHead->chksum=MoPacUtl::calcCheckSum((dword*)icmpHead,0);

                //���M�o�b�t�@�e�[�u���̐ݒ�
                tbi.data[2]=NULL;
                tbi.size[2]=0;
                tbi.data[1]=(char*)icmpHead;
                //tbi.size[1]=size;
                tbi.size[1]=0;
                tbi.ipType=IPPROTO_ICMP;
    
                ret = g_MoIp->transIp(&tbi , MoPacUtl::swapLong(ip) ,0, 0);

                //delete icmpHead;
                
                break;

            //ARP�҂������Wake Up
            case MSG_MONES_WAKEUP_ARP_WAIT:
                
                printf("MSG_MONES_WAKEUP_ARP_WAIT\n");
                
                MAC_REPLY_WAIT* nowWait;
                
                //ARP�v���҂����X�g�̌���
                for (int i = 0; i < g_MoArp->macWaitList->size() ; i++) {
                    nowWait = g_MoArp->macWaitList->get(i);
                    
                    if(nowWait->repFlg == 1){
                        //ARP�����ς݂Ȃ�A�҂��p�P�b�g�𑗐M����B
                        ret = g_MoIp->transIp(nowWait->ipPacketBuf , nowWait->ip ,0, 0);
                        
                        //�Ҕ����Ă���IP�p�P�b�g�o�b�t�@�̉��
                        free(nowWait->ipPacketBuf);
                        
                        //�҂����X�g����폜
                        g_MoArp->macWaitList->removeAt(i);
                        //�J�E���^�f�N�������g������B
                        i--;
                    }
                }
                

                
                break;

            default:
                /* igonore this message */
                break;
            }

        }
    }
    return 0;
}


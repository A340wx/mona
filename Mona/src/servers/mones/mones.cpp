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
    int ret;
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
    
    //Ne2000MoNic* insAbstractNic = new Ne2000MoNic();
    
    
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


//Yamami �f�o�b�O
//FileOutputStream fos("MONES.LOG", true);
//printf("open=%x\n", fos.open());

//char logStr[1024];    //���O�o�͕�����


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

            //Yamami!! �p�P�b�g���M�����A������
            //case MSG_NET_PACKET_SEND:
                //�p�P�b�g���M
                //�e�X�g ����MAC�A�h���X�֏o�͏���
                // insAbstractNic->frame_output( (byte *)ne_test_pattern, ether_mac_addr, ne_sizeof_test_pattern, 0x0806 );
                //�z�X�g�A�h���X�֏o�͏���
                // insAbstractNic->frame_output( (byte *)ne_test_pattern, dest_ether_mac_addr, ne_sizeof_test_pattern, 0x0806 );

                //break;


            default:
                /* igonore this message */
                break;
            }

        }
    }
    return 0;
}


/*!
    \file   MoUdp.cpp
    \brief  UDP�v���g�R�������N���X

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2005/05/11 update:$Date$
*/

/*! \class MoUdp
 *  \brief UDP�v���g�R�������N���X
 */



#include "MoUdp.h"
#include "MonesConfig.h"
#include "MonesGlobal.h"

/*!
    \brief initialize
         MoUdp �R���X�g���N�^
    \author Yamami
    \date   create:2004/09/20 update:
*/
MoUdp::MoUdp()
{

}

/*!
    \brief initialize
         MoUdp initIp
    \author Yamami
    \param  AbstractMonic *pminsNic [in] NIC�N���X�ւ̃|�C���^
    \date   create:2004/09/20 update:
*/
void MoUdp::initUdp(AbstractMonic *pminsNic ) 
{
    //NIC�N���X��ێ�
    insAbstractNic = pminsNic;
    return;
}


/*!
    \brief initialize
         MoUdp �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/08/20 update:
*/
MoUdp::~MoUdp() 
{

}


/*!
    \brief receiveUdp
         UDP�v���g�R����M ����
    \param  IP_HEADER *ipHead [in] IP�w�b�_�ւ̃|�C���^
    \return int ���� 
        
    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
int MoUdp::receiveUdp(IP_HEADER *ipHead)
{
    DUMMY_HEADER dmyhead;
    
    int udp_size;
    UDP_HEADER *udp;

    udp=(UDP_HEADER*)ipHead->data;

    //udp_size=MoPacUtl::swapShort(ipHead->len)-sizeof(IP_HEADER);
    udp_size=MoPacUtl::swapShort(udp->len);

    // �`�F�b�N�T���̊m�F
    // UDP�̃`�F�b�N�T���́A�^���w�b�_�����čs���B
    dmyhead.srcip=ipHead->srcip;
    dmyhead.dstip=ipHead->dstip;
    dmyhead.tmp=0;
    dmyhead.prot=ipHead->prot;
    dmyhead.len=udp->len;
    if(MoPacUtl::calcCheckSumDummyHead((dword*)&dmyhead,(dword*)udp,sizeof(DUMMY_HEADER),udp_size)){
        logprintf("udp_size = %d\n",udp_size);
        logprintf("udp->chksum = %x\n",MoPacUtl::swapShort(udp->chksum));
        logprintf("udp CheckSum BAD!!\n");
        return 0;
    }

    saveRecv(ipHead,udp_size+sizeof(IP_HEADER));

    return 0;
}


/*!
    \brief transUdp
         UDP���M ����
    \param  word dstip [in] ���M��IP�A�h���X
    \param  byte type [in] UDP�^�C�v
    \param  UDP_HEADER *udpHead [in] UDP�w�b�_�ւ̃|�C���^
    \param  int size [in] �p�P�b�g�T�C�Y
    \return ����
        
    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
void MoUdp::transUdp(dword dstip, byte type, byte code, UDP_HEADER *udpHead, int size)
{
    
    TRANS_BUF_INFO tbi;

    //UDP�w�b�_�[�̐ݒ�
    //udpHead->type=type;
    //udpHead->code=code;
    //udpHead->chksum=0;
    //udpHead->chksum=MoPacUtl::calcCheckSum((dword*)udpHead,size);

    //���M�o�b�t�@�e�[�u���̐ݒ�
    //tbi.data[2]=NULL;
    //tbi.size[2]=0;
    //tbi.data[1]=(char*)udpHead;
    //tbi.size[1]=size;
    //tbi.ipType=IPPROTO_UDP;

    g_MoIp->transIp(&tbi,dstip,0,0);
}


/*!
    \brief saveRecv
         UDP������M ����
    \param  IP_HEADER *ipHead [in] IP�w�b�_
    \param  int size [in] �p�P�b�g�T�C�Y
    \return ����
    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
void MoUdp::saveRecv(IP_HEADER *ipHead, int size)
{
    MessageInfo info;
    MONES_IP_REGIST *regist;

    int udp_size;
    UDP_HEADER *udp;

    udp=(UDP_HEADER*)ipHead->data;
    udp_size=MoPacUtl::swapShort(ipHead->len)-sizeof(IP_HEADER);

    //�����œ���UDP�p�P�b�g���f�o�b�O
    if (MoPacUtl::swapShort(udp->dstport) == 2600){
        char buf[1530];
        memset(buf,0,sizeof(buf));
//        logprintf("srcip = %x\n",MoPacUtl::swapLong(ipHead->srcip));
//        logprintf("dstport = %x\n",MoPacUtl::swapShort(udp->dstport));
//        logprintf("size = %x\n",udp_size);
        memcpy(buf, udp->data , udp_size);
        for(int i = 0; i < udp_size ; i++){
            logprintf("%c",buf[i]);
        }
    }

    //�o�^���Ă���v���Z�X�ɒʒm����B
    for (int i = 0; i < MonesRList->size() ; i++) {
        regist = MonesRList->get(i);
        
        //UDP�̓R�l�N�V�������X�Ȃ̂ŁA�|�[�g�ԍ��̂݁H
        if(regist->port == MoPacUtl::swapShort(udp->dstport)){
            //�o�^����Ă���IP����у|�[�g�ւ�UDP�p�P�b�g�Ȃ�΁A���b�Z�[�W�ʒm
            // create message
            Message::create(&info, MSG_MONES_ICMP_NOTICE, 0, 0, 0, NULL);
            
            //MoPacUtl�Ń��b�Z�[�W�Ƀp�P�b�g���Z�b�g
            int reti = MoPacUtl::createPacMsg(&info , udp->data , udp_size);
            
            // send
            if (Message::send(regist->tid, &info)) {
                //printf("MoUdp::saveRecv error\n");
            }
            break;
            
        }
    }
}

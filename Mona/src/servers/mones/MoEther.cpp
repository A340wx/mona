/*!
    \file   MoEther.cpp
    \brief  �C�[�T�l�b�g�����N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/08/12 update:$Date$
*/

/*! \class MoEther
 *  \brief �C�[�T�l�b�g�����N���X
 */


#include "MonesGlobal.h"



/*!
    \brief initialize
         MoEther �R���X�g���N�^
    \author Yamami
    \date   create:2004/08/12 update:
*/
MoEther::MoEther()
{
    
}

/*!
    \brief initialize
         MoEther etherInit
    \author Yamami
    \param  AbstractMonic *pminsNic [in] �h���C�o�N���X�ւ̃|�C���^(�{���́A���ۃN���X)
    \date   create:2004/08/12 update:
*/
void MoEther::etherInit(AbstractMonic *pminsNic) 
{

    
    //�C�[�T�l�b�g�t���[���ێ����X�g ����
    /* keyinfo list */
    //Ether_FrameList_ = new HList<ETHER_FRAME*>();

    //�����ێ���NIC�h���C�o�֊i�[
    insAbstractNic = pminsNic;

    return;
}


/*!
    \brief initialize
         MoEther �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/08/12 update:
*/
MoEther::~MoEther() 
{
    //delete Ether_FrameList_;
}


/*!
    \brief setEtherFrame
         �C�[�T�l�b�g�t���[���Z�b�g

    \param  byte *frameBuf [in] �C�[�T�l�b�g�t���[���o�b�t�@
    \param  int size [in] �C�[�T�l�b�g�t���[���T�C�Y
    \return int ���� 
        
    \author Yamami
    \date   create:2004/08/12 update:
*/
int MoEther::setEtherFrame(byte *frameBuf, int size)
{
    
    // allocate ETHER_FRAME
    //ETHER_FRAME* frame = (ETHER_FRAME*)malloc(sizeof(ETHER_FRAME));
    
    //�t���[���o�b�t�@�̃N���A
    memset(&Ether_FrameBuf_ , 0 ,sizeof(Ether_FrameBuf_));
    
    // �t���[���̃R�s�[
    memcpy(&Ether_FrameBuf_ , frameBuf , size);

    //�����ŁA�p�P�b�g���[�e�B���e�B�N���X���g���āA�G���f�B�A���ϊ�
    //�t���[���^�C�v
    Ether_FrameBuf_.type = MoPacUtl::packet_get_2byte(frameBuf , 12);

//2005/05/06 �t���[���^�C�v��\��
//printf("Ether_FrameBuf_.type:%x \n",Ether_FrameBuf_.type);
    
    //���X�g�ɒǉ�
    //Ether_FrameList_->add(frame);

    return 0;

}



/*!
    \brief receiveEther
         �C�[�T�l�b�g�t���[����M���� 
    \return int ���� 
        
    \author Yamami
    \date   create:2004/08/22 update:
*/
int MoEther::receiveEther()
{

    // �t���[�����e�v���g�R���ɓn��
    switch(Ether_FrameBuf_.type)
    {
        case ETHER_PROTO_IP:
            return g_MoIp->receiveIp((IP_HEADER*)Ether_FrameBuf_.data);
            break;
        case ETHER_PROTO_ARP:
            return g_MoArp->receiveArp((ARP_HEADER*)Ether_FrameBuf_.data);
            break;
            
    }
    
    return 0;
}



/*!
    \brief sendEther
         �C�[�T�l�b�g�t���[�����M���� 
    \param  byte *pkt [in] ���M�p�P�b�g�ւ̃|�C���^
    \param  dword dest_ip [in] ���M��IP�A�h���X
    \param  dword size [in] ���M�T�C�Y
    \return int ���� 
        
    \author Yamami
    \date   create:2004/08/28 update:
*/
void MoEther::sendEther(byte *pkt , dword dest_ip , dword size)
{

    //Yamami?? ������ ���M�́A�A�v��������R�[�������͂� ����M�ŃN���X�͕�����ׂ����H
    //byte   *mac;

    /* ARP �e�[�u������ */
    //mac=arp_lookup(dest_ip);
    
    //���M
    //frame_output( pkt, mac, size, ETHER_PROTO_IP );
}


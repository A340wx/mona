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
#include "MoEther.h"


/*!
    \brief initialize
         MoEther �R���X�g���N�^
    \author Yamami
    \date   create:2004/08/12 update:
*/
MoEther::MoEther()
{
    //printf("MoEther Constructor\n");
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
    Ether_FrameList_ = new HList<ETHER_FRAME*>();

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
    delete Ether_FrameList_;
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
    ETHER_FRAME* frame = (ETHER_FRAME*)malloc(sizeof(ETHER_FRAME));
    // �t���[���̃R�s�[
    memcpy(frame , frameBuf , size);

    //�����ŁA�p�P�b�g���[�e�B���e�B�N���X���g���āA�G���f�B�A���ϊ�
    //�t���[���^�C�v
    frame->type = MoPacUtl::packet_get_2byte(frameBuf , 12);

//2005/05/06 �t���[���^�C�v��\��
//printf("frame->type:%x \n",frame->type);
    
    //���X�g�ɒǉ�
    Ether_FrameList_->add(frame);

    return 0;

}


/*!
    \brief getEtherFrame
         �C�[�T�l�b�g�t���[���擾 
    \param  byte* frameBuf [in] �C�[�T�l�b�g�t���[���o�b�t�@�ւ̃|�C���^
    \return int ���� 
        
    \author Yamami
    \date   create:2004/08/12 update:
*/
int MoEther::getEtherFrame(ETHER_FRAME *frameBuf)
{
    

    ETHER_FRAME* tempEther = Ether_FrameList_->removeAt(Ether_FrameList_->size() - 1);

    if (tempEther == NULL) {
        printf("tmp Null!!\n");
        return 0;
    }

    /* copy to keyinfo */
    memcpy(frameBuf, tempEther, sizeof(ETHER_FRAME));
    
    free(tempEther);
    
    return 1;

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
    int reti;
    
    // allocate ETHER_FRAME
    ETHER_FRAME* frame = (ETHER_FRAME*)malloc(sizeof(ETHER_FRAME));
    
    reti = getEtherFrame(frame);

    //Yamami�f�o�b�O
    //int i;
    //for(i=0;i<60;i++){
    //    printf("%d:%x ",i,frame->data[i]);
    //}
    //printf("\n");

    // �t���[�����e�v���g�R���ɓn��
    switch(frame->type)
    {
        case ETHER_PROTO_IP:
            return g_MoIp->receiveIp((IP_HEADER*)frame->data);
            break;
        case ETHER_PROTO_ARP:
            return g_MoArp->receiveArp((ARP_HEADER*)frame->data);
            break;
            
    }
    
    return 0;
}




/*!
    \brief receiveEther
         �C�[�T�l�b�g�t���[����M���� 
         �o�b�t�@�����O�����A���ڏ�����
    \param  byte* frameBuf [in] �C�[�T�l�b�g�t���[���o�b�t�@�ւ̃|�C���^
    \return int ���� 
    \author Yamami
    \date   create:2004/11/15 update:$Date$
*/
//int MoEther::receiveEther(ETHER_FRAME *frameBuf)
//{
//    
//    // �t���[�����e�v���g�R���ɓn��
//    switch(frameBuf->type)
//    {
//        case ETHER_PROTO_IP:
//            return g_MoIp->receiveIp((IP_HEADER*)frameBuf->data);
//            break;
//        case ETHER_PROTO_ARP:
//            return g_MoArp->receiveArp((ARP_HEADER*)frameBuf->data);
//            break;
//            
//    }
//    
//    return 0;
//}



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


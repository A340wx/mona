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

    //printf("MoEther init\n");
    
    //�C�[�T�l�b�g�t���[���ێ����X�g ����
    /* keyinfo list */
    Ether_FrameList_ = new HList<ETHER_FRAME*>();

    //�����ێ���NIC�h���C�o�֊i�[
    insAbstractNic = pminsNic;

    //ARP�N���X���C���X�^���X��  Yamami?? ������ARP��IP�N���X�̓C���X�^���X�����ׂ����H
    //2004/09/04 ARP�N���X�́Amones.cpp(���C��)�ŃC���X�^���X�����A�O���[�o���|�C���^�ŕێ�����B
    //g_MoArp = new MoArp();
    //g_MoArp->initArp(insAbstractNic);

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
    \param  byte* frameBuf [in] �C�[�T�l�b�g�t���[���o�b�t�@�ւ̃|�C���^
    \param  byte *mac [in] �C�[�T�l�b�g�t���[���T�C�Y
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
//int MoEther::getEtherFrame()
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
        case DIX_TYPE_IP:
            return g_MoIp->receiveIp((IP_HEADER*)frame->data);
            break;
        case DIX_TYPE_ARP:
            return g_MoArp->receiveArp((ARP_HEADER*)frame->data);
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


/*!
    \file   MoIcmp.cpp
    \brief  ICMP�v���g�R�������N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/09/20 update:$Date$
*/

/*! \class MoIcmp
 *  \brief ICMP�v���g�R�������N���X
 */



#include "MoIcmp.h"
#include "MonesConfig.h"
#include "MonesGlobal.h"

/*!
    \brief initialize
         MoIcmp �R���X�g���N�^
    \author Yamami
    \date   create:2004/09/20 update:
*/
MoIcmp::MoIcmp()
{

}

/*!
    \brief initialize
         MoIcmp initIp
    \author Yamami
    \param  AbstractMonic *pminsNic [in] NIC�N���X�ւ̃|�C���^
    \date   create:2004/09/20 update:
*/
void MoIcmp::initIp(AbstractMonic *pminsNic ) 
{
    //NIC�N���X��ێ�
    insAbstractNic = pminsNic;
    return;
}


/*!
    \brief initialize
         MoIcmp �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/08/20 update:
*/
MoIcmp::~MoIcmp() 
{

}


/*!
    \brief receiveIcmp
         ICMP�v���g�R����M ����
    \param  IP_HEADER *ipHead [in] IP�w�b�_�ւ̃|�C���^
    \return int ���� 
        
    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
int MoIcmp::receiveIcmp(IP_HEADER *ipHead)
{
    int icmp_size;
    ICMP_HEADER *icmp;

    icmp=(ICMP_HEADER*)ipHead->data;

    icmp_size=MoPacUtl::swapShort(ipHead->len)-sizeof(IP_HEADER);

    /* �`�F�b�N�T���̊m�F�B */
    if(MoPacUtl::calcCheckSum((dword*)icmp,icmp_size)){
        return 0;
    }


    switch(icmp->type)
    {
        case ICMP_TYPE_ECHOREQ:
            transIcmp(ipHead->srcip,ICMP_TYPE_ECHOREP,0,icmp,icmp_size);
            break;
        case ICMP_TYPE_ECHOREP:
            //return saveRecv(ipHead,icmp_size+sizeof(IP_HEADER));
            break;
    }

    return 0;
}


/*!
    \brief transIcmp
         ICMP���M ����
    \param  word dstip [in] ���M��IP�A�h���X
    \param  byte type [in] ICMP�^�C�v
    \param  ICMP_HEADER *icmpHead [in] IP�w�b�_�ւ̃|�C���^
    \param  int size [in] �p�P�b�g�T�C�Y
    \return int ���� 
        
    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
void MoIcmp::transIcmp(dword dstip, byte type, byte code, ICMP_HEADER *icmpHead, int size)
{
    TRANS_BUF_INFO tbi;

    //ICMP�w�b�_�[�̐ݒ�
    icmpHead->type=type;
    icmpHead->code=code;
    icmpHead->chksum=0;
    icmpHead->chksum=MoPacUtl::calcCheckSum((dword*)icmpHead,size);

    //���M�o�b�t�@�e�[�u���̐ݒ�
    tbi.data[2]=NULL;
    tbi.size[2]=0;
    tbi.data[1]=(char*)icmpHead;
    tbi.size[1]=size;
    tbi.ipType=IPPROTO_ICMP;

    g_MoIp->transIp(&tbi,dstip,0,0);
}

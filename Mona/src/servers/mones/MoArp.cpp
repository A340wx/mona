/*!
    \file   MoArp.cpp
    \brief  ARP�v���g�R�������N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/08/28 update:$Date$
*/

/*! \class MoArp
 *  \brief ARP�v���g�R�������N���X
 */



#include "MoArp.h"
#include "MonesConfig.h"
#include "MonesGlobal.h"

/*!
    \brief initialize
         MoArp �R���X�g���N�^
    \author Yamami
    \date   create:2004/08/28 update:
*/
MoArp::MoArp()
{
    //printf("MoArp Constructor\n");
}

/*!
    \brief initialize
         MoArp initArp
    \author Yamami
    \param  AbstractMonic *pminsNic [in] NIC�N���X�ւ̃|�C���^
    \date   create:2004/08/28 update:
*/
void MoArp::initArp(AbstractMonic *pminsNic ) 
{
    //NIC�N���X��ێ�
    insAbstractNic = pminsNic;
    return;
}


/*!
    \brief initialize
         MoArp �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/08/28 update:
*/
MoArp::~MoArp() 
{

}


/*!
    \brief receiveArp
         ARP�v���g�R����M ����
    \param  ARP_HEADER *arpHead [in] ARP�w�b�_�ւ̃|�C���^
    \return int ���� 
        
    \author Yamami
    \date   create:2004/08/28 update:2004/08/29
*/
int MoArp::receiveArp(ARP_HEADER *arpHead)
{
    
    int rest=0;
    
    // IP�̊m�F
    // ����IP���̗v���Ŗ�����΁A�������Ȃ��B
    if(arpHead->dstIp!=MoPacUtl::swapLong(G_MonesCon.getGl_myIpAdr() )){
        return 0;
    }

//
//    Yamami�f�o�b�O
//    char logStr[1024];    //���O�o�͕�����
//
//    sprintf(logStr , "swapLong(G_MonesCon.getGl_myIpAdr):%04x dstIp:%04x \n",
//                MoPacUtl::swapLong(G_MonesCon.getGl_myIpAdr),arpHead->dstIp);
//    sprintf(logStr , "swapLong(G_MonesCon.getGl_myIpAdr):%04x dstIp:%04x \n",
//                MoPacUtl::swapLong(G_MonesCon.getGl_myIpAdr),arpHead->dstIp);
//    sprintf(logStr , "G_MonesCon.getGl_myIpAdr:%04x \n",
//                G_MonesCon.getGl_myIpAdr);
//    sprintf(logStr , "G_MonesCon.getGl_myIpAdr:%04x \n",
//                G_MonesCon.getGl_myIpAdr);
//    sprintf(logStr , "hardType:%02x \n",
//                arpHead->hardType);
//    printf(logStr);
//    
//    sprintf(logStr , "protType:%02x \n",
//                arpHead->protType);
//    printf(logStr);
//
//    sprintf(logStr , "hardAddrLen:%01x \n",
//                arpHead->hardAddrLen);
//    printf(logStr);
//    
//    sprintf(logStr , "protAddrLen:%01x \n",
//                arpHead->protAddrLen);
//    printf(logStr);
//
//    sprintf(logStr , "opeCode:%02x \n",
//                arpHead->opeCode);
//    printf(logStr);
//
//    sprintf(logStr , "srcMac:%02x:%02x:%02x:%02x:%02x:%02x \n",
//                arpHead->srcMac[0],
//                arpHead->srcMac[1],
//                arpHead->srcMac[2],
//                arpHead->srcMac[3],
//                arpHead->srcMac[4],
//                arpHead->srcMac[5]);
//    printf(logStr);
//
//    sprintf(logStr , "srcIp:%04x \n",
//                arpHead->srcIp);
//    printf(logStr);
//
//    sprintf(logStr , "dstMac:%02x:%02x:%02x:%02x:%02x:%02x \n",
//                arpHead->dstMac[0],
//                arpHead->dstMac[1],
//                arpHead->dstMac[2],
//                arpHead->dstMac[3],
//                arpHead->dstMac[4],
//                arpHead->dstMac[5]);
//    printf(logStr);
//
//    sprintf(logStr , "dstIp:%04x \n",
//                arpHead->dstIp);
//    printf(logStr);



    // �I�y���[�V�����R�[�h�̊m�F
    switch(MoPacUtl::swapShort(arpHead->opeCode))
    {
        //ARP�v��
        case OPE_CODE_ARP_REQ:
            transArp(arpHead->srcIp,arpHead->srcMac, OPE_CODE_ARP_REP);
            
            //�L���b�V���ɓo�^ 2004/08/28������
            //addCache(arpHead->srcIp,arpHead->srcMac); 
            break;
        //ARP����
        case OPE_CODE_ARP_REP:
            //������
            //rest=receiveReply(arpHead->srcIp,arpHead->srcMac);
            break;
        
        //RARP�v��
        case OPE_CODE_RARP_REQ:
        //RARP����
        case OPE_CODE_RARP_REP:
            break;
    }

    return rest;

}



static char broadcastMac[]={0xff,0xff,0xff,0xff,0xff,0xff};

 /*!
    \brief transArp
         ARP�������� ����
    \param  dword dstip [in] ���M��IP�A�h���X
    \param  byte *dstmac [in] ���M��MAC�A�h���X
    \param  word opecode [in] �I�y���[�V�����R�[�h
    \return void ���� 
        
    \author Yamami
    \date   create:2004/08/28 update:
*/
void MoArp::transArp(dword dstip, byte *dstmac, word opecode)
{
    ARP_HEADER head;

    //�����p ARP�w�b�_�t���[���쐬
    head.hardType=MoPacUtl::swapShort(HARD_TYPE_ETHER);
    head.protType=MoPacUtl::swapShort(PROT_TYPE_IP);
    head.hardAddrLen=6;
    head.protAddrLen=4;
    head.opeCode=MoPacUtl::swapShort(opecode);
    memcpy(head.srcMac,insAbstractNic->ether_mac_addr,6);
    head.srcIp=MoPacUtl::swapLong(G_MonesCon.getGl_myIpAdr() );
    if(memcmp(dstmac,broadcastMac,6)==0){
    head.srcIp=MoPacUtl::swapLong(G_MonesCon.getGl_myIpAdr() );
    }else{
        memcpy(head.dstMac,dstmac,6);
    }
    head.dstIp=dstip;  //�����͎󂯎�����܂ܕԋp����̂ŁA�G���f�B�A���ϊ��͕s�v

    //���M���� �����ł́A���ڃh���C�o���R�[��
    insAbstractNic->frame_output((byte *)&head , dstmac , sizeof(head) , DIX_TYPE_ARP);

}

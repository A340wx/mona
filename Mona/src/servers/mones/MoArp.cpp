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
    //ARP�L���b�V��������
    
    ArpCache = new HashMap<char*>(ARP_CACHE_NUM);
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

    // �I�y���[�V�����R�[�h�̊m�F
    switch(MoPacUtl::swapShort(arpHead->opeCode))
    {
        //ARP�v��
        case OPE_CODE_ARP_REQ:
            transArp(arpHead->srcIp,arpHead->srcMac, OPE_CODE_ARP_REP);
            
            //�L���b�V���ɓo�^
            addArpCache(arpHead->srcIp,(char*)arpHead->srcMac); 
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


/*!
    \brief addArpCache
         ARP�L���b�V���o�^����
    \param  dword ip [in] �o�^IP�A�h���X
    \param  char *mac [in] �o�^MAC�A�h���X
    \return void ���� 
        
    \author Yamami
    \date   create:2004/09/19 update:
*/
void MoArp::addArpCache(dword ip, char *mac)
{

    char IpKey[10];    //IP�A�h���X�L�[

    //IP�A�h���X���AMAP�̃L�[��(String��)
    sprintf(IpKey , "%08x",ip);
    ArpCache->put(IpKey , mac);

}


/*!
    \brief searchCache
         ARP�L���b�V����������
    \param  dword ip [in] �o�^IP�A�h���X
    \return char *mac [in] ��������MAC�A�h���X ������Ȃ��ꍇ��NULL
        
    \author Yamami
    \date   create:2004/09/19 update:
*/
char* MoArp::searchCache(dword ip)
{
    char IpKey[10];    //IP�A�h���X�L�[
    char *RetMacValue;
    
    //HashMap���猟��
    //IP�A�h���X���AMAP�̃L�[��(String��)
    sprintf(IpKey , "%08x",ip);
    RetMacValue = ArpCache->get(IpKey);

    return RetMacValue;
}




/*!
    \brief getMac
         ARP IP�A�h���X��������
    \param  dword ip [in] IP�A�h���X
    \param  byte *mac [OUT] ����MAC�A�h���X�ւ̃|�C���^
    \return void ���� 
        
    \author Yamami
    \date   create:2004/09/20 update:
*/
int MoArp::getMac(dword ip,char *mac)
{
    enum{
        RETRY_COUNT=3,          // ���g���C���M��
        REQUEST_TIMEOUT=2000,   // ���N�G�X�g�^�C���A�E�g�~���b
    };

    char *retmac;

    //int rest;
    //REPLY_WAIT *wait;
    //int i;
    //REPLY_WAIT *p;


    // �L���b�V��������
    if((retmac=searchCache(ip))!=NULL)
    {
        //�L���b�V�����猩����΁A�Ԃ��B
        memcpy(mac,retmac,6);
        return 0;
    }

/*

    // ���M����
    if((wait=kmalloc(sizeof(REPLY_WAIT)))==NULL)return -ENOMEM;
    wait->ip=ip;
    wait->repFlg=0;
    wait->next=replyWait;
    replyWait=wait;

    // ���N�G�X�gARP�𑗐M
    for(i=0;;)
    {
        transArp(num,ip,broadcastMac,OPE_CODE_ARP_REQ);
        wait->wait.flag=0;
        wait_intr(&wait->wait,REQUEST_TIMEOUT,TASK_SIGNAL_WAIT);
        if(wait->repFlg)
        {
            addCache(ip,wait->mac);
            memcpy(mac,wait->mac,6);
            rest=0;
            break;
        }
        if(++i>=RETRY_COUNT)
        {
            rest=-ENETUNREACH;
            break;
        }
    }

    // ���M�㏈��
    if(replyWait==wait)replyWait=wait->next;
    else
    {
        for(p=replyWait;p->next!=wait;p=p->next);
        p->next=wait->next;
    }
    kfree(wait);

    return rest;

*/

}


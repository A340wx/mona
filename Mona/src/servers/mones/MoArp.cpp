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
    ArpCache = new HashMap<byte*>(ARP_CACHE_NUM);
    //ARP�v���҂����X�g������
    macWaitList = new HList<MAC_REPLY_WAIT*>();
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
    \date   create:2004/08/28 update:$Date$
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
            
            //�v�����󂯂������A�L���b�V���ɓo�^
            addArpCache(arpHead->srcIp,arpHead->srcMac); 
            
            break;
            
        //ARP����
        case OPE_CODE_ARP_REP:
            rest=receiveReply(arpHead->srcIp,arpHead->srcMac);
            break;
        
        //RARP�v��
        case OPE_CODE_RARP_REQ:
        //RARP����
        case OPE_CODE_RARP_REP:
            break;
    }

    return rest;

}



/*!
    \brief receiveReply
         ARP��M����
    \param  dword srcip [in] ���M��IP�A�h���X
    \param  byte *mac [in] ���M��MAC�A�h���X
    \return void ���� 
        
    \author Yamami
    \date   create:2004/11/15 update:$Date$
*/
int MoArp::receiveReply(dword srcip,byte *mac)
{
    
    MAC_REPLY_WAIT* nowWait;
    int findFlag = 0;
    
    //ARP�v���҂����X�g�̌���
    for (int i = 0; i < macWaitList->size() ; i++) {
        nowWait = macWaitList->get(i);
        
        nowWait->wait++;
        if(nowWait->ip == srcip){
            //�v���҂���IP�Ȃ�
            //MAC�A�h���X�R�s�[
            memcpy(nowWait->mac ,mac ,6);
            nowWait->repFlg = 1;

            //ARP�L���b�V���o�^
            addArpCache(srcip,mac); 
            
            //findFlag�I��
            findFlag = 1;
        }
    }
    
    if(findFlag == 1){
        //Mones���g�փ��b�Z�[�W�ʒm
        MessageInfo info;
        dword targetID = Message::lookupMainThread("MONES.EX5");  //TO DO ���̒T�����ǂ��Ȃ���ȁ[
        // create message
        Message::create(&info, MSG_MONES_WAKEUP_ARP_WAIT, 0, 0, 0, NULL);
        Message::send(targetID, &info);
    }
    
    return 0;
}


//static char broadcastMac[]={0xff,0xff,0xff,0xff,0xff,0xff};
static byte broadcastMac[]={0xff,0xff,0xff,0xff,0xff,0xff};

/*!
    \brief transArp
         ARP���M���� (ARP�����AARP�v��)
    \param  dword dstip [in] ���M��IP�A�h���X
    \param  byte *dstmac [in] ���M��MAC�A�h���X
    \param  word opecode [in] �I�y���[�V�����R�[�h
    \return void ���� 
        
    \author Yamami
    \date   create:2004/08/28 update:$Date$
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
    insAbstractNic->frame_output((byte *)&head , dstmac , sizeof(head) , ETHER_PROTO_ARP);

}


/*!
    \brief addArpCache
         ARP�L���b�V���o�^����
    \param  dword ip [in] �o�^IP�A�h���X
    \param  char *mac [in] �o�^MAC�A�h���X
    \return void ���� 
        
    \author Yamami
    \date   create:2004/09/19 update:$Date$
*/
void MoArp::addArpCache(dword ip, byte *mac)
{

    char IpKey[10];    //IP�A�h���X�L�[
    
    byte* setMac;
    
    setMac = new byte(6);
    memcpy(setMac,mac,6);

    //IP�A�h���X���AMAP�̃L�[��(String��)
    sprintf(IpKey , "%08x",ip);
    ArpCache->put(IpKey , setMac);

}


/*!
    \brief searchCache
         ARP�L���b�V����������
    \param  dword ip [in] �o�^IP�A�h���X
    \return char *mac [in] ��������MAC�A�h���X ������Ȃ��ꍇ��NULL
        
    \author Yamami
    \date   create:2004/09/19 update:$Date$
*/
byte* MoArp::searchCache(dword ip)
{
    char IpKey[10];    //IP�A�h���X�L�[
    byte *RetMacValue;
    
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
    \return int 0:�L���b�V���q�b�g 0�ȊO:ARP�v�����������A���̑҂��ԍ�
        
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
int MoArp::getMac(dword ip,byte *mac)
{
    MAC_REPLY_WAIT* nowWait;
    int waitNumber;
    
    enum{
        RETRY_COUNT=3,          // ���g���C���M��
        REQUEST_TIMEOUT=2000,   // ���N�G�X�g�^�C���A�E�g�~���b
    };

    byte *retmac;
    

    // �L���b�V��������
    if((retmac=searchCache(ip))!=NULL)
    {
        //�L���b�V�����猩����΁A�Ԃ��B
        memcpy(mac,retmac,6);
        return 0;
    }


    //�L���b�V���ɖ����̂�ARP�v��

    // ���M���� �҂����X�g�ɓo�^
    nowWait = new MAC_REPLY_WAIT();
    
    nowWait->ip=ip;
    nowWait->repFlg=0;
    nowWait->wait=0;

    //�҂����X�g�ɒǉ�
    macWaitList->add(nowWait);
    //�҂��ԍ��̎擾
    //TO DO Yamami!!! �����X���b�h�Z�[�t�ɂ��Ȃ��Ƃ�΂����E�E�E
    waitNumber = macWaitList->size();

    // ���N�G�X�gARP�𑗐M
    //�u���[�h�L���X�g�ŁAARP�v��
    transArp(ip,broadcastMac,OPE_CODE_ARP_REQ);
    
    // �҂��ԍ���ԋp
    return waitNumber;

}


/*!
    \file   MoIp.cpp
    \brief  IP�v���g�R�������N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/09/20 update:$Date$
*/

/*! \class MoIp
 *  \brief IP�v���g�R�������N���X
 */



#include "MoIp.h"
#include "MonesConfig.h"
#include "MonesGlobal.h"

/*!
    \brief initialize
         MoIp �R���X�g���N�^
    \author Yamami
    \date   create:2004/09/20 update:
*/
MoIp::MoIp()
{

}

/*!
    \brief initialize
         MoIp initIp
    \author Yamami
    \param  AbstractMonic *pminsNic [in] NIC�N���X�ւ̃|�C���^
    \date   create:2004/09/20 update:
*/
void MoIp::initIp(AbstractMonic *pminsNic ) 
{
    //NIC�N���X��ێ�
    insAbstractNic = pminsNic;
    return;
}


/*!
    \brief initialize
         MoIp �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/08/20 update:
*/
MoIp::~MoIp() 
{

}


/*!
    \brief receiveIp
         IP�v���g�R����M ����
    \param  IP_HEADER *ipHead [in] IP�w�b�_�ւ̃|�C���^
    \return int ���� 
        
    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
int MoIp::receiveIp(IP_HEADER *ipHead)
{

    /* �`�F�b�N�T���̊m�F�B */
    if(MoPacUtl::calcCheckSum((dword*)ipHead,(ipHead->verhead&0xf)*4)){
        return 0;
    }

    /* ��ʃv���g�R���֓n���B */
    switch(ipHead->prot)
    {
        //case IPPROTO_TCP:
        //  return g_MoIcmp->receiveTcp(ipHead);
        //case IPPROTO_UDP:
        //  return g_MoIcmp->receiveUdp(ipHead);
        case IPPROTO_ICMP:
          return g_MoIcmp->receiveIcmp(ipHead);
    }

    return 0;
}


/*!
    \brief transIp
         IP�v���g�R�����M ����
    \param  TRANS_BUF_INFO *tbi [in] ���M�o�b�t�@�\���̂ւ̃|�C���^
    \param  dword dstip [in] ���M��IP�A�h���X
    \param  byte tos [in] �T�[�r�X�^�C�v
    \param  int flag [in] �t���O
    \return int ���� 

    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
int MoIp::transIp(TRANS_BUF_INFO *tbi, dword dstip, byte tos, int flag)
{

    byte *transPacket; //�p�P�b�g���M�o�b�t�@

    char dstmac[6];
    dword transip;
    //int num;
    int rest;
    IP_HEADER ipHead;
    int max,total;
    //int trans;

    //Yamami �����Ń��[�e�B���O�����H�H �Ƃ肠�����Adst = trans�Ƃ���B
    transip = dstip;

    // ���M�� MAC�A�h���X�擾(ARP����)
    if((rest=g_MoArp->getMac(transip,dstmac))<0){
        return rest;
    }

    //IP�w�b�_���쐬����B
    ipHead.verhead=IP_HEAD_VERSION|(sizeof(IP_HEADER)/4);
    ipHead.tos=tos;
    
    //GET_ID(ipHead.id);
    //Yamami �����̓X���b�h�Z�[�t�ɂ���K�v������H
    ipHead.id++;
    
    ipHead.ttl=255;
    ipHead.prot=tbi->ipType;
    ipHead.srcip=MoPacUtl::swapLong(G_MonesCon.getGl_myIpAdr());
    ipHead.dstip=dstip;
    ipHead.chksum=0;

    //���MTBL
    tbi->type=ETHER_PROTO_IP;
    tbi->data[0]=(char*)&ipHead;
    tbi->size[0]=sizeof(IP_HEADER);         // IP header size.
    //max=ethDev[num].mtu-sizeof(IP_HEADER);  // �f�[�^�ő呗�M�T�C�Y�B
    max=G_MonesCon.getGl_myMTU()-sizeof(IP_HEADER);  // �f�[�^�ő呗�M�T�C�Y�B
    total=tbi->size[1]+tbi->size[2];        // �f�[�^�g�[�^���T�C�Y�B

    if(total<=max)
    {
        
        
        //���M�v���p�P�b�g�T�C�Y��MTU�ȉ��Ȃ��
        //IP�T�C�Y
        ipHead.len=MoPacUtl::swapShort(tbi->size[0]+total);
        //�t���O
        ipHead.frag=MoPacUtl::swapShort(flag<<14);
        //�`�F�b�N�T��
        ipHead.chksum=MoPacUtl::calcCheckSum((dword*)&ipHead,tbi->size[0]);
        
        //����NIC���g���đ��M!
        //ethDev[num].dev->write(ethDev[num].dev->linf,(size_t)tbi,(size_t)dstmac);
        //memcpy(ipHead.dstMac,tbi->data[1],tbi->size[1]);
        
        //�p�P�b�g�쐬
        transPacket = (byte *)malloc(sizeof(IP_HEADER) + total);
        memcpy(transPacket,(byte *)&ipHead,sizeof(ipHead));
        memcpy(transPacket + sizeof(ipHead),tbi->data[1],tbi->size[1]);
        
        insAbstractNic->frame_output(transPacket , (byte *)dstmac , sizeof(IP_HEADER) + total , ETHER_PROTO_IP);
        
        //�p�P�b�g�o�b�t�@���
        free(transPacket);
    }

/*
    else
    {
        //���M�v���p�P�b�g�T�C�Y��MTU�ȏ�Ȃ��  ������
        ipHead.len=swapWord(tbi->size[0]+max);
        ipHead.frag=swapWord(IP_HEAD_FRAG_ON);
        tbi->size[2]=max-tbi->size[1];
        ipHead.chksum=calcSum((uint*)&ipHead,tbi->size[0]);
        ethDev[num].dev->write(ethDev[num].dev->linf,(size_t)tbi,(size_t)dstmac);

        trans=max;                      // ���M�σT�C�Y
        tbi->data[2]+=max-tbi->size[1];
        tbi->size[1]=0;

        for(;;)
        {
            ipHead.chksum=0;

            if(total-trans<=max)
            {
                ipHead.len=swapWord(tbi->size[0]+total-trans);
                ipHead.frag=swapWord(trans);
                GET_ID(ipHead.id);
                ipHead.chksum=calcSum((uint*)&ipHead,tbi->size[0]);
                tbi->size[2]=total-trans;
                ethDev[num].dev->write(ethDev[num].dev->linf,(size_t)tbi,(size_t)dstmac);
                break;
            }
            else
            {
                ipHead.len=swapWord(tbi->size[0]+max);
                ipHead.frag=swapWord(trans|IP_HEAD_FRAG_ON);
                GET_ID(ipHead.id);
                ipHead.chksum=calcSum((uint*)&ipHead,tbi->size[0]);
                tbi->size[2]=max;
                ethDev[num].dev->write(ethDev[num].dev->linf,(size_t)tbi,(size_t)dstmac);
            }

            trans+=max;
            tbi->data[2]+=max;
        }
    }
*/

    return 0;
}


 
/*!
    \brief ipRouting
         IP���[�e�B���O ����
    \param  word ip [in] ���M��IP�A�h���X
    \param  dword dstip [in] �]����IP�A�h���X(���̃T�u�l�b�g�Ȃ烋�[�^�ƂȂ�)
    \return int ���� 

    \author Yamami
    \date   create:2004/10/30 update:2004/10/30
*/
int MoIp::ipRouting(dword ip,dword *transip)
{
    //int i;

    //����T�u�l�b�g�����`�F�b�N����B
    if((ip & G_MonesCon.getGl_mySubnet()) == (G_MonesCon.getGl_myIpAdr() & G_MonesCon.getGl_mySubnet()))
    {
        *transip=ip;
        return 0;
    }

    /* �f�t�H���g�Q�[�g�E�F�C�ցB */
    *transip=G_MonesCon.getGl_myGw();
    return 0;
}

/*!
    \file  MoArp.h
    \brief ARP�v���g�R�������N���X �w�b�_

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X Licnese

    \author  Yamami 
    \version $Revision$
    \date   create:2004/08/28 update:$Date$
*/
#ifndef _MONA_MOARP_
#define _MONA_MOARP_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"

using namespace MonAPI;

/*! 
 *  \struct ARP_HEADER
 *  \brief ARP�w�b�_�\����
 */
typedef struct{
    word hardType  __attribute__((packed));    //ʰ�޳������
    word protType  __attribute__((packed));    //���ĺ�����
    byte  hardAddrLen  __attribute__((packed)); //ʰ�޳�����ڽ��
    byte  protAddrLen  __attribute__((packed)); //���ĺٱ��ڽ��
    word opeCode  __attribute__((packed));     //���ڰ���
    byte  srcMac[6]  __attribute__((packed));   //���M��ʰ�޳�����ڽ
    dword   srcIp  __attribute__((packed));       //���M�����ĺٱ��ڽ
    byte  dstMac[6]  __attribute__((packed));   //���ޯ�ʰ�޳�����ڽ
    dword   dstIp  __attribute__((packed));       //���ޯ����ĺٱ��ڽ
}ARP_HEADER;



enum{
    /* Hard type. */
    HARD_TYPE_ETHER= 1,     /* Ethernet. */

    /* Protocol type. */
    PROT_TYPE_IP=0x0800,    /* IP. */

    /* Operation code. */
    OPE_CODE_ARP_REQ= 1,    // ARP�v��
    OPE_CODE_ARP_REP= 2,    // ARP����
    OPE_CODE_RARP_REQ=3,    // RARP�v��
    OPE_CODE_RARP_REP=4,    // RARP����
};


enum{
    ARP_CACHE_NUM=64,               /* ARP�L���b�V�����B */
};


/*!
    MoArp class
*/
class MoArp
{
    
  public:
    
    //�R���X�g���N�^
    MoArp();
    ~MoArp();
    void initArp(AbstractMonic*);

    //int getMac(int,uint,char*);
    int receiveArp(ARP_HEADER*);
    char* searchCache(dword );
    int getMac(dword ,char*);

  private:
    //ARP�������� ����
    void transArp(dword , byte*, word );
    void addArpCache(dword , char*);
    
    
    //ARP�L���b�V���p HashMap
    HashMap<char*>* ArpCache;

    //NIC�h���C�o
    AbstractMonic* insAbstractNic;

};

#endif

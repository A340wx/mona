/*!
    \file  MoIp.h
    \brief IP�v���g�R�������N���X �w�b�_

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X Licnese

    \author  Yamami 
    \version $Revision$
    \date   create:2004/09/20 update:$Date$
*/
#ifndef _MONA_MOIP_
#define _MONA_MOIP_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"


// Yamami ??���̐錾�����ł����H
/*! 
 *  \struct IP_HEADER
 *  \brief IP�w�b�_�\����
 */
typedef struct{
    byte  verhead;  /* �o�[�W�����A�w�b�_���B */
    byte  tos;      /* TOS. */
    word len;       /* �g�[�^�����B */
    word id;        /* ���ʔԍ��B */
    word frag;      /* �t���O�A�t���O�����g�I�t�Z�b�g�B */
    byte  ttl;      /* Time to Live. */
    byte  prot;     /* �v���g�R���ԍ��B */
    word chksum;    /* �w�b�_�`�F�b�N�T���B */
    dword srcip;        /* ���茳IP�B */
    dword dstip;        /* ����IP�B */
    char     data[0];
}IP_HEADER;


enum{
    IP_HEAD_VERSION=4<<4,

    IP_HEAD_FRAG_ON= 0x2000,    /* �t���O�����g�f�[�^����t���O�B */
    IP_HEAD_FRAG_NOT=0x4000,    /* �t���O�����g�s�t���O�B */
};

/*! 
 *  \struct TRANS_BUF_INFO
 *  \brief IP���M�o�b�t�@�\����
 */
typedef struct{
    char  *data[3];     /* ���M�t���[���A�h���X�B */
    int    size[3];     /* �f�[�^�t���[���T�C�Y�B */
    word type;        /* �t���[���^�C�v�B */
    dword  ipType;      /* IP�v���g�R���^�C�v�B */
}TRANS_BUF_INFO;


/*!
    MoIp class
*/
class MoIp
{
    
  public:
    
    //�R���X�g���N�^
    MoIp();
    ~MoIp();
    void initIp(AbstractMonic*);

    int receiveIp(IP_HEADER*);
    int transIp(TRANS_BUF_INFO*, dword , byte , int );

  private:
    int ipRouting(dword ,dword*);
    
    //NIC�h���C�o
    AbstractMonic* insAbstractNic;

};

#endif

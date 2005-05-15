/*!
    \file  MonesDefine.h
    \brief �e��O���[�o���萔�錾

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2004/08/28 update:$Date$
*/

#include <monapi/cmemoryinfo.h>

#ifndef _MONA_MONESDEFINE_
#define _MONA_MONESDEFINE_

/* Ethernet MAC�w�w�b�_�\�� */
#define SIZEOF_ETHERADDR    6

//DIX�d�l�t���[���̃t���[���^�C�v
#define ETHER_PROTO_IP      0x0800      // IP�v���g�R���t���[��
#define ETHER_PROTO_ARP     0x0806      // ARP�v���g�R���t���[��

#define etherhdr_dest_addr  0
#define etherhdr_src_addr   (etherhdr_dest_addr+SIZEOF_ETHERADDR)
#define etherhdr_type       (etherhdr_src_addr+SIZEOF_ETHERADDR)
#define SIZEOF_ETHERHDR     (etherhdr_type+2)


//IP�w�b�_�v���g�R��No
enum{
    IPPROTO_IP,         /* Internet protocol. */
    IPPROTO_IPV6,       /* Internet Protocol Version 6. */
    IPPROTO_ICMP=1,     /* Control message protocol. */
    IPPROTO_IGMP=2,
    IPPROTO_RAW,        /* Raw IP Packets Protocol. */
    IPPROTO_TCP=6,      /* Transmission control protocol. */
    IPPROTO_UDP=17,     /* User datagram protocol. */

    INADDR_ANY=      0,             /* IPv4 local host address. */
    INADDR_BROADCAST=0xffffffff,    /* IPv4 broadcast address. */
};


/* IP�w�b�_�\�� */
#define     SIZEOF_IPADDR       4

#define     iphdr_version   0               /* 1 */
#define     iphdr_service   (iphdr_version+1)       /* 1 */
#define     iphdr_len   (iphdr_service+1)       /* 2 */
#define     iphdr_ident (iphdr_len+2)           /* 2 */
#define     iphdr_frags (iphdr_ident+2)         /* 2 */
#define     iphdr_ttl   (iphdr_frags+2)         /* 1 */
#define     iphdr_protocol  (iphdr_ttl+1)           /* 1 */
#define     iphdr_chksum    (iphdr_protocol+1)      /* 2 */
#define     iphdr_src_addr  (iphdr_chksum+2)        /* 4 */
#define     iphdr_dest_addr (iphdr_src_addr+4)      /* 4 */
#define     SIZEOF_IPHDR    (iphdr_dest_addr+4)



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



//ICMP �^�C�v
//0 �G�R�[�����iecho reply�j 
//3 ���Đ�s�B�idestination unreachable�j 
//4 �\�[�X�E�N�G���`�isource quench�A���M���}���j 
//5 ���_�C���N�g�v���iredirect�A�o�H�ύX�v���j 
//8 �G�R�[�v���iecho request�j 
//11 ���Ԓ��߁itime exceeded�j 
//12 �p�����[�^�ُ�iparameter problem�j 
//13 �^�C���X�^���v�v���itimestamp request�j 
//14 �^�C���X�^���v�����itimestamp reply�j 
//15 ���v���iinformation request�j 
//16 ��񉞓��iinformation reply�j 
//17 �A�h���X�E�}�X�N�v���iaddress mask request�j 
//18 �A�h���X�E�}�X�N�����iaddress mask reply�j 
enum{
    ICMP_TYPE_ECHOREP=0,
    ICMP_TYPE_ECHOREQ=8,
};


/*! 
 *  \struct ICMP_HEADER
 *  \brief ICMP�w�b�_�\����
 */
typedef struct{
    unsigned char  type;        /* ICMP�^�C�v�B */
    unsigned char  code;        /* ICMP�R�[�h�B */
    unsigned short chksum;      /* �`�F�b�N�T���B */
    char           data[32];     /* �f�[�^�B */
}ICMP_HEADER;



/*! 
 *  \struct UDP_HEADER
 *  \brief UDP�w�b�_�\����
 */
 typedef struct{
    word srcport;
    word dstport;
    short len;
    word chksum;
    char   data[0];
}UDP_HEADER;




/*! 
 *  \struct TRANS_BUF_INFO
 *  \brief IP���M�o�b�t�@�\����
 */
struct TRANS_BUF_INFO{
    char  *data[3];     /* ���M�t���[���A�h���X�B */
    int    size[3];     /* �f�[�^�t���[���T�C�Y�B */
    word type;        /* �t���[���^�C�v�B */
    dword  ipType;      /* IP�v���g�R���^�C�v�B */
};


/*! 
 *  \struct MAC_REPLY_WAIT
 *  \brief ARP�v���҂��Ǘ� �\����
 */
struct MAC_REPLY_WAIT{
    dword ip;         //�v����IP�A�h���X
    int repFlg;       //Reply flag 0:�҂� 1:����
    int wait;         //�E�F�C�g�� 
    char mac[6];      //MAC�A�h���X�i�[
    dword  ipType;    /* IP�v���g�R���^�C�v�B */
    //TRANS_BUF_INFO* ipPacketBuf; //IP�p�P�b�g�o�b�t�@
    monapi_cmemoryinfo* ipPacketBuf01;  //IP�p�P�b�g�o�b�t�@01
    monapi_cmemoryinfo* ipPacketBuf02;  //IP�p�P�b�g�o�b�t�@02
};

/*! 
 *  \struct MONES_IP_REGIST
 *  \brief Mones�o�^���
 */
struct MONES_IP_REGIST{
    dword ip;         //�ʐM��IP
    word port;       //�ʐM��PORT
    dword tid;        //�X���b�hID
};


#endif

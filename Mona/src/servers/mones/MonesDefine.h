/*!
    \file  MonesDefine.h
    \brief �e��O���[�o���萔�錾

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X Licnese

    \author  Yamami 
    \version $Revision$
    \date   create:2004/08/28 update:$Date$
*/

#ifndef _MONA_MONESDEFINE_
#define _MONA_MONESDEFINE_


//DIX�d�l�t���[���̃t���[���^�C�v
#define     DIX_TYPE_IP     0x0800    // IP�v���g�R���t���[��
#define     DIX_TYPE_ARP    0x0806    // ARP�v���g�R���t���[��

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


#endif

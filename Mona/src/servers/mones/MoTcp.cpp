/*!
    \file   MoTcp.cpp
    \brief  TCP�v���g�R�������N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/10/11 update:$Date$
*/

/*! \class MoTcp
 *  \brief IP�v���g�R�������N���X
 */



#include "MoTcp.h"
#include "MonesConfig.h"
#include "MonesGlobal.h"

/*!
    \brief initialize
         MoTcp �R���X�g���N�^
    \author Yamami
    \date   create:2004/10/11 update:$Date$
*/
MoTcp::MoTcp()
{

}

/*!
    \brief initialize
         MoTcp initTcp
    \author Yamami
    \param  AbstractMonic *pminsNic [in] NIC�N���X�ւ̃|�C���^
    \date   create:2004/10/11 update:$Date$
*/
void MoTcp::initTcp(AbstractMonic *pminsNic ) 
{
    //NIC�N���X��ێ�
    insAbstractNic = pminsNic;
    return;
}


/*!
    \brief initialize
         MoTcp �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/10/11 update:$Date$
*/
MoTcp::~MoTcp() 
{

}


/*!
    \brief send_tcp
         TCP�f�[�^���o����
    \param  T_TSOCK *sock [in] �ʐM������w��TCP�\�P�b�g�\����
    \param  char flags [in] ����t���O
    \param  struct Packet *packet [in] �\�P�b�g
    \param  char *data [in] ���M�f�[�^
    \param  dword size [in] ���M�f�[�^�̃T�C�Y
    \return ����

    \author Yamami
    \date   create:2004/09/20 update:2004/09/20
*/
void send_tcp(T_TSOCK *sock, char flags, struct Packet *packet, char *data, dword size)
{

/*
    dword tsize;
    dword sum;
    char *ip_hdr;
    char *tcp_hdr;
    char *tcp_body;

    //�p�P�b�g�̃|�C���^���A�C�[�T�l�b�g�w�b�_���Ƃ���B
    packet->ptr = packet->buffer + SIZEOF_ETHERHDR;
    //�p�P�b�g�̃T�C�Y�́ATCP�w�b�_+�f�[�^�T�C�Y
    packet->size = SIZEOF_TCPHDR + size;
    //IP�w�b�_�ւ̃|�C���^�́A�p�P�b�g�̃|�C���^
    ip_hdr = packet->ptr;
    //TCP�w�b�_�̃|�C���^�́AIP�w�b�_����AIP�w�b�_�T�C�Y���v���X
    tcp_hdr = ip_hdr + SIZEOF_IPHDR;
    //TCP�{�f�B�ւ̃|�C���^�́ATCP�w�b�_����ATCP�w�b�_�T�C�Y��
    tcp_body = tcp_hdr + SIZEOF_TCPHDR;

    // TCP�f�[�^���̃Z�b�g
    memcpy(tcp_body, data, size);


    // TCP�w�b�_�̃Z�b�g
    packet_put_n(tcp_hdr, tcphdr_src_port, sock->myport);
    packet_put_n(tcp_hdr, tcphdr_dest_port, sock->youport);
    packet_put_nl(tcp_hdr, tcphdr_opt_mss, 0x020405b4); // kind = 2, len = 4, mss = 1460
    tcp_hdr[tcphdr_len] &= 0x0f;
    tcp_hdr[tcphdr_len] |= (5 + 1) << 4; // Unit is 32bit words

    tcp_hdr[tcphdr_flag] = flags & 0x3f;
    packet_put_n(tcp_hdr, tcphdr_chksum, 0);
    packet_put_n(tcp_hdr, tcphdr_urg, 0);

    packet_put_nl(tcp_hdr, tcphdr_ack, sock->ack);
    packet_put_nl(tcp_hdr, tcphdr_seq, sock->seq);

    // pseudo header & checksum
    packet_put_nl(tcp_hdr, pseudo_dest, node_ip_addr);
    packet_put_nl(tcp_hdr, pseudo_src, sock->ip);
    tcp_hdr[pseudo_zero]  = 0;
    tcp_hdr[pseudo_proto] = 6;
    tsize = size + SIZEOF_TCPHDR;
    if (size & 0x01) {  // size is odd
    //tsize++;
        tcp_hdr[tsize] = 0x00;
    }
    packet_put_n(tcp_hdr, pseudo_len, tsize);
    sum = calc_chksum(tcp_hdr + pseudo_src, tsize + 12);
    packet_put_n(tcp_hdr, tcphdr_chksum, sum);

    // IP�w�b�_�̃Z�b�g
    ip_hdr[iphdr_protocol] = IP_PROTO_TCP;
    packet_put_nl(ip_hdr, iphdr_src_addr, node_ip_addr);
    packet_put_nl(ip_hdr, iphdr_dest_addr, sock->ip);

    //IP�N���X�ő��M����
    ip_output(packet);

    //�V�[�P���X�ԍ�����
    if (flags & (TCP_FLAG_SYN | TCP_FLAG_FIN)) {
        sock->seq++;
    } else if (size > 0) {
        sock->seq += size;
    }
*/

}

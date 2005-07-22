/*!
    \file  MoTcp.h
    \brief TCP�v���g�R�������N���X �w�b�_

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2004/10/11 update:$Date$
*/
#ifndef _MONA_MOTCP_
#define _MONA_MOTCP_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"
#include <monesoc/Socket.h>





/* TCP�w */
#define tcphdr_src_port     0           /* 2 */
#define tcphdr_dest_port    (tcphdr_src_port+2) /* 2 */
#define tcphdr_seq      (tcphdr_dest_port+2)    /* 4 */
#define tcphdr_ack      (tcphdr_seq+4)      /* 4 */
#define tcphdr_len      (tcphdr_ack+4)      /* 1 */
#define tcphdr_flag     (tcphdr_len+1)      /* 1 */
#define tcphdr_win      (tcphdr_flag+1)     /* 2 */
#define tcphdr_chksum       (tcphdr_win+2)      /* 2 */
#define tcphdr_urg      (tcphdr_chksum+2)   /* 2 */
#define tcphdr_opt_mss      (tcphdr_urg+2)      /* 4 */
#define SIZEOF_TCPHDR       (tcphdr_opt_mss+4)




/* TCP header flag bit */
#define TCP_FLAG_FIN 0x01
#define TCP_FLAG_SYN 0x02
#define TCP_FLAG_RST 0x04
#define TCP_FLAG_PSH 0x08
#define TCP_FLAG_ACK 0x10
#define TCP_FLAG_URG 0x20



/*! 
 *  \struct Packet
 *  \brief Packet�\����
 */
struct Packet {
    char buffer[1518];
    unsigned int size;
    char *ptr;
    char flag;
};

/* flag bit for Packet.flag */
#define PKT_ARP_WAIT 0x01
#define PKT_IP_REQUEST 0x02
#define PKT_SYN_WAIT 0x10


/*!
    MoTcp class
*/
class MoTcp
{
    
  public:
    
    //�R���X�g���N�^
    MoTcp();
    ~MoTcp();
    void initTcp(AbstractMonic*);

    void send_tcp(Socket *sock, char flags, struct Packet *packet, char *data, dword size);
    
    
    int receiveTcp(IP_HEADER*);

  private:

    //NIC�h���C�o
    AbstractMonic* insAbstractNic;
    
    void saveRecv(IP_HEADER*, int );

};

#endif

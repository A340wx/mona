/*!
    \file  Socket.h
    \brief �Ȉ�Socket�N���X �w�b�_

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2005/07/15 update:$Date$
*/

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>
#include <monapi/messages.h>

#ifndef _MONA_SOCKET_
#define _MONA_SOCKET_


#define MAX_BUFF_SIZE    128    //�ő�o�b�t�@��

typedef struct
{
    dword Handle, Owner, Size;
} packet_cmemoryinfo;

/*!
    Socket class
*/
class Socket
{
    
  public:
    
    //�R���X�g���N�^
    Socket();
    ~Socket();
    
    byte    status;      //�J�ڏ��
    dword   ip;
    word    myport;  //���ȃ|�[�g
    word    youport; //����|�[�g
    dword   seq;    // ��������̃V�[�P���X�ԍ�
    dword   ack;    // ���肩��̃V�[�P���X�ԍ�
    dword   tid;    //�X���b�hID
    
    //HList<packet_cmemoryinfo*> *recvBuff;   //��M�o�b�t�@ �l�b�g��Mones �����A�v��
    //HList<packet_cmemoryinfo*> *sendBuff;   //���M�o�b�t�@ �A�v����Mones �����l�b�g
    
    //���L�������ł��Ƃ肷����ꕨ�Ȃ̂ŁA�Œ�m��
    packet_cmemoryinfo recvBuff[MAX_BUFF_SIZE];
    packet_cmemoryinfo sendBuff[MAX_BUFF_SIZE];
    
    int addBuffer(char *pac , int pacsize ,int rorsFlag);
    
    packet_cmemoryinfo getBuffer(int rorsFlag);

  private:
    int nowRecvBufCount;
    int nowSendBufCount;
    
};

#endif

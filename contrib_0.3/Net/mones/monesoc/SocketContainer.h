/*!
    \file  SocketContainer.h
    \brief SocketContainer�N���X �w�b�_

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
#include <monapi/cmemoryinfo.h>

#ifndef _MONA_SOCKETCONTAINER_
#define _MONA_SOCKETCONTAINER_


#define MAX_BUFF_SIZE    128    //�ő�o�b�t�@��

typedef struct
{
    dword Handle, Owner, Size;
} packet_cmemoryinfo;

/*!
    SocketContainer class
*/
class SocketContainer
{
    
  public:
    
    //�R���X�g���N�^
    SocketContainer();
    ~SocketContainer();
    
    byte    status;      //�J�ڏ��
    dword   ip;
    word    myport;  //���ȃ|�[�g
    word    youport; //����|�[�g
    dword   seq;    // ��������̃V�[�P���X�ԍ�
    dword   ack;    // ���肩��̃V�[�P���X�ԍ�
    dword   tid;    //�X���b�hID
    
    
    //���L�������ł��Ƃ肷����ꕨ�Ȃ̂ŁA�Œ�m��
    packet_cmemoryinfo recvBuff[MAX_BUFF_SIZE];
    packet_cmemoryinfo sendBuff[MAX_BUFF_SIZE];
    
    int addBuffer(char *pac , int pacsize ,int rorsFlag);
    
    packet_cmemoryinfo getBuffer(int rorsFlag);
    
    int createPacMonaMsg(MessageInfo *info , dword protno);

  private:
    int nowRecvBufCount;
    int nowSendBufCount;
    
};

#endif

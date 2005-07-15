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
#ifndef _MONA_SOCKET_
#define _MONA_SOCKET_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"




/*!
    Socket class
*/
class Socket
{
    
  public:
    
    //�R���X�g���N�^
    Socket();
    ~Socket();
    
    byte   status;
    dword       ip;
    word    myport;  //���ȃ|�[�g
    word    youport; //����|�[�g
    dword   seq;    // ��������̃V�[�P���X�ԍ�
    dword   ack;    // ���肩��̃V�[�P���X�ԍ�


  private:


};

#endif

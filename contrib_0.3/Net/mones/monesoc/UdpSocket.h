/*!
    \file  UdpSocket.h
    \brief UdpSocket�N���X �w�b�_

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2005/08/09 update:$Date$
*/

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>
#include <monapi/cmemoryinfo.h>
#include <monalibc/stdio.h>

#include <monesoc/SocketContainer.h>

#ifndef _MONA_UDPSOCKET
#define _MONA_UDPSOCKET



/*!
    UdpSocket class
*/
class UdpSocket
{
    
  public:
    
    //�R���X�g���N�^
    UdpSocket();
    ~UdpSocket();
    
    //bind
    int bind(word port);
    
    //recv
    int recv(char* buff ,dword len);

    //send
    int send(char* mesg, dword len, char* host, word port);

  private:
    word useport;       //�ÖٓI�Ɏg���|�[�g

};

#endif

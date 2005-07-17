/*!
    \file  SocketsManager.h
    \brief Socket�Q �Ǘ��N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2005/07/15 update:$Date$
*/
#ifndef _MONA_SOCKETSMANAGER_
#define _MONA_SOCKETSMANAGER_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"
#include "Socket.h"



/*!
    SocketsManager class
*/
class SocketsManager
{
    
  public:
    
    //�R���X�g���N�^
    SocketsManager();
    ~SocketsManager();
    

  private:
    //�R�l�N�V��������Socket�n�b�V��
    HashMap<Socket*>* conSocList;
    
    //���X������Socket�n�b�V��
    HashMap<Socket*>* lisSocList;

};

#endif

/*!
    \file  MoIp.h
    \brief IP�v���g�R�������N���X �w�b�_

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

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

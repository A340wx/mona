/*!
    \file  MoUdp.h
    \brief UDP�v���g�R�������N���X �w�b�_

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X Licnese

    \author  Yamami 
    \version $Revision$
    \date   create:2005/05/11 update:$Date$
*/
#ifndef _MONA_MOUDP_
#define _MONA_MOUDP_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"
#include "MoIp.h"


/*!
    MoUdp class
*/
class MoUdp
{
    
  public:
    
    //�R���X�g���N�^
    MoUdp();
    ~MoUdp();
    void initUdp(AbstractMonic*);

    int receiveUdp(IP_HEADER*);

  private:
    
    void transUdp(dword , byte , byte , UDP_HEADER*, int );
    void saveRecv(IP_HEADER*, int );
    //NIC�h���C�o
    AbstractMonic* insAbstractNic;

};

#endif

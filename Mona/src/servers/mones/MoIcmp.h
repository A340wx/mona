/*!
    \file  MoIcmp.h
    \brief ICMP�v���g�R�������N���X �w�b�_

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2004/09/20 update:$Date$
*/
#ifndef _MONA_MOICMP_
#define _MONA_MOICMP_

#include <sys/types.h>
#include <sys/HashMap.h>
#include <monapi.h>

#include "MoPacUtl.h"
#include "MonesDefine.h"
#include "AbstractMonic.h"
#include "MoIp.h"


/*!
    MoIcmp class
*/
class MoIcmp
{
    
  public:
    
    //�R���X�g���N�^
    MoIcmp();
    ~MoIcmp();
    void initIp(AbstractMonic*);

    int receiveIcmp(IP_HEADER*);

  private:
    
    void transIcmp(dword , byte , byte , ICMP_HEADER*, int );
    void saveRecv(IP_HEADER*, int );
    //NIC�h���C�o
    AbstractMonic* insAbstractNic;

};

#endif

/*!
    \file  MonesGlobal.h
    \brief �O���[�o�� �C���X�^���X�錾

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2004/09/04 update:$Date$
*/

#ifndef _MONES_GLOBAL_
#define _MONES_GLOBAL_

//MONES_GLOBAL_VALUE_DEFINED�}�N�����錾����Ă���ӏ��̂݁A�C���X�^���X��
//���́Aextern "C" �Ő錾
#ifdef MONES_GLOBAL_VALUE_DEFINED
#define GLOBAL /* */
#define GLOBAL_VAL(v) = (v)
#else
#define GLOBAL extern "C"
//#define GLOBAL extern 
#define GLOBAL_VAL(v) /* */
#endif


#include <sys/types.h>
#include "MonesConfig.h"
#include "MoEther.h"
#include "MoArp.h"
#include "MoIp.h"
#include "MoUdp.h"
#include "MoTcp.h"
#include "MoIcmp.h"
#include <monesoc/SocketsManager.h>

//GLOBAL VirtualConsole* g_console GLOBAL_VAL(0);      /*< pointer to console    */
//GLOBAL VirtualConsole* g_log     GLOBAL_VAL(0);

//MonesConfig���C���X�^���X��
GLOBAL MonesConfig G_MonesCon;
GLOBAL MoEther* g_MoEther;
GLOBAL MoArp* g_MoArp;
GLOBAL MoIp* g_MoIp;
GLOBAL MoUdp* g_MoUdp;
GLOBAL MoTcp* g_MoTcp;
GLOBAL MoIcmp* g_MoIcmp;
GLOBAL SocketsManager* g_SocketsManager;

//Mones�o�^���Ǘ��p List
GLOBAL HList<MONES_IP_REGIST*> *MonesRList;

#endif

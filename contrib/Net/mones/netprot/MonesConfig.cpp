/*!
    \file  MonesConfig.cpp
    \brief �l�b�g���[�N�ݒ�

    Copyright (c) 2004 Yamami
    WITHOUT ANY WARRANTY

    \author  Yamami
    \version $Revision$
    \date   create:2004/08/29 update:$Date$
*/

/*! \class MonesConfig
 *  \brief �l�b�g���[�N�ݒ�
 */



#include "MonesConfig.h"


/*!
    \brief MonesConfig �R���X�g���N�^

    \author Yamami
    \date   create:2004/08/29 update:$Date$
*/
MonesConfig::MonesConfig()
{
    

}


/*!
    \brief MonesConfig �f�X�N�g���N�^

    \author Yamami
    \date   create:2004/08/29 update:$Date$
*/
MonesConfig::~MonesConfig()
{
    
}


/*!
    \brief getGl_myIpAdr
        IP�A�h���X�Q�b�^�[

    \param  ����
    \return dword IP�A�h���X
    \author Yamami
    \date   create:2004/08/29 update:$Date$
*/
dword MonesConfig::getGl_myIpAdr( )
{
    
    dword retIp;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retIp = gl_myIpAdr;
    
    return retIp;
}


/*!
    \brief getGl_myIpAdr
        �T�u�l�b�g�}�X�N

    \param  ����
    \return dword �T�u�l�b�g�}�X�N
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
dword MonesConfig::getGl_mySubnet( )
{
    
    dword retSubnet;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retSubnet = gl_mySubnet;
    
    return retSubnet;
}


/*!
    \brief getGl_myGw
        GW

    \param  ����
    \return dword GW
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
dword MonesConfig::getGl_myGw( )
{
    
    dword retGw;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retGw = gl_myGw;
    
    return retGw;
}


/*!
    \brief getGl_myDns
        DNS

    \param  ����
    \return dword DNS
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
dword MonesConfig::getGl_myDns( )
{
    
    dword retDNS;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retDNS = gl_myDns;
    
    return retDNS;
}


/*!
    \brief getGl_myMTU
        MTU

    \param  ����
    \return dword MTU
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
dword MonesConfig::getGl_myMTU( )
{
    
    dword retMTU;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retMTU = gl_myMTU;
    
    return retMTU;
}

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
    \return uint32_t IP�A�h���X
    \author Yamami
    \date   create:2004/08/29 update:$Date$
*/
uint32_t MonesConfig::getGl_myIpAdr( )
{
    
    uint32_t retIp;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retIp = gl_myIpAdr;
    
    return retIp;
}


/*!
    \brief getGl_myIpAdr
        �T�u�l�b�g�}�X�N

    \param  ����
    \return uint32_t �T�u�l�b�g�}�X�N
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
uint32_t MonesConfig::getGl_mySubnet( )
{
    
    uint32_t retSubnet;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retSubnet = gl_mySubnet;
    
    return retSubnet;
}


/*!
    \brief getGl_myGw
        GW

    \param  ����
    \return uint32_t GW
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
uint32_t MonesConfig::getGl_myGw( )
{
    
    uint32_t retGw;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retGw = gl_myGw;
    
    return retGw;
}


/*!
    \brief getGl_myDns
        DNS

    \param  ����
    \return uint32_t DNS
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
uint32_t MonesConfig::getGl_myDns( )
{
    
    uint32_t retDNS;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retDNS = gl_myDns;
    
    return retDNS;
}


/*!
    \brief getGl_myMTU
        MTU

    \param  ����
    \return uint32_t MTU
    \author Yamami
    \date   create:2004/09/20 update:$Date$
*/
uint32_t MonesConfig::getGl_myMTU( )
{
    
    uint32_t retMTU;
    
    //�����o�̓��e�����̂܂܃��^�[��
    retMTU = gl_myMTU;
    
    return retMTU;
}

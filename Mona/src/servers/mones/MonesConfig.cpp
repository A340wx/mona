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


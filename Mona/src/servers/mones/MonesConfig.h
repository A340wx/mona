/*!
    \file  MonesConfig.h
    \brief �l�b�g���[�N�ݒ�

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X Licnese

    \author  Yamami 
    \version $Revision$
    \date   create:2004/08/28 update:$Date$
*/

#ifndef _MONA_MONESCONFIG_
#define _MONA_MONESCONFIG_

#include <sys/types.h>

/*!
    class MonesConfig
*/
class MonesConfig {


  private:
  
    //�l�b�g���[�N�R���t�B�O ���ʂ����ŃR���X�^���g�ݒ�
    //IP�A�h���X 
    //*****************************************
    //Mona��IP�A�h���X�ݒ�
    //IP�A�h���X long 2�o�C�g�����v4�o�C�g
    // ��:192(C0).168(A8).9(01).1(01) �� 0xC0A80101
    //*****************************************
    static const dword   gl_myIpAdr = 0xC0A80101;       //IP�A�h���X;
    
    
  public:
    MonesConfig();
    ~MonesConfig();
  
    //IP�A�h���X�Q�b�^�[
    dword getGl_myIpAdr();
    
    //Yamami!! DNS,�f�t�H���g�Q�[�g���A�ݒ�������̃N���X��
};

#endif

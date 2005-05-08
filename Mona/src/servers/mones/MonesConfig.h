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
    // TAP�l�b�g���[�N 192.168.0.2
    static const dword   gl_myIpAdr = 0xC0A80002;       //IP�A�h���X;
    
    //�T�u�l�b�g�}�X�N 255.255.255.0
    static const dword   gl_mySubnet = 0xFFFFFF00;

    //GW
    // 192.168.0.1 QEMU��TAP�Ȃ�ATAP-Win32 Adapter V8 �̃A�h���X��GW��
    static const dword   gl_myGw = 0xC0A80001;

    //DNS �ݒ肵�Ă��܂��g���Ȃ��B
    static const dword   gl_myDns = 0xC0A80001;
    
    //MTU  Yamami ����́ANIC���ƂɎ��ׂ��H�H
    static const int   gl_myMTU = 1500;
    
  public:
    MonesConfig();
    ~MonesConfig();
  
    //IP�A�h���X�Q�b�^�[
    dword getGl_myIpAdr();
    
    //�T�u�l�b�g�}�X�N�Q�b�^�[
    dword getGl_mySubnet();
    //GW�Q�b�^�[
    dword getGl_myGw();
    //DNS�A�h���X�Q�b�^�[
    dword getGl_myDns();

    //MTU�l �Q�b�^�[
    dword getGl_myMTU();

};

#endif

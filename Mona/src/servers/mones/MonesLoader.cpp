/*!
    \file   MonesLoader.cpp
    \brief  Mones NIC�h���C�o�C���X�^���X ���[�_�[

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/10/31 update:$Date$
*/

/*! \class MonesLoader
 *  \brief Mones NIC�h���C�o�C���X�^���X ���[�_�[
 */


#include <pci/Pci.h>

#include "MonesLoader.h"
#include "MonesConfig.h"
#include "MonesGlobal.h"
#include "AbstractMonic.h"
#include "Ne2000MoNic.h"

/*!
    \brief initialize
         MonesLoader �R���X�g���N�^
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
MonesLoader::MonesLoader()
{

}


/*!
    \brief initialize
         MonesLoader �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
MonesLoader::~MonesLoader() 
{

}


/*!
    \brief setup
         MonesLoader setup
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
void MonesLoader::setup() 
{
    //�������Ȃ��B

}


/*!
    \brief getNicInstance
         NIC�h���C�o�̃C���X�^���X�𓾂�B
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
AbstractMonic* MonesLoader::getNicInstance() 
{
    
    //TODO 2004/10/31 ����
    // PCI�f�o�C�X�������āA������� QEMU / ������Ȃ���� Bochs �Ɣ��f��
    // NE2000�h���C�o�����[�h����B
    // ���̑����ł́A���[�h�Ɏ��s
    
    int ret;
    PciInf *pciinfo;              //PCI���C�u����

    Ne2000MoNic *nicDriver;
    
    //PCI���C�u�����N���X�̃C���X�^���X��
    Pci* pcilib = new Pci();
    
    //TODO �ꎞ���̂��Ȃ̂ŁA�}�W�b�N�i���o�[��p����
    //QEMU��́ANE2000��T��
    pciinfo = pcilib->CheckPciExist(0x10EC,0x8029);
    
    if(pciinfo->Exist == 0){
        //�������
        //NE2000�̃��[�h
        nicDriver = new Ne2000MoNic();
        
        //QEMU�ݒ�
        nicDriver->setNicIRQ(9);
        nicDriver->setNicIOBASE(0xC100);
        
    }
    else{
        //������Ȃ����
        //NE2000�̃��[�h
        nicDriver = new Ne2000MoNic();
        
        //Bochs�ݒ�
        nicDriver->setNicIRQ(3);
        nicDriver->setNicIOBASE(0x240);
    
    }
    
    
    //NIC������
    ret = nicDriver->init();
    
    //if(ret != 0){
    //    //�������Ɏ��s�����ꍇ�ANULL�h���C�o��Ԃ��B
    //    nicDriver = 0;
    //    
    //}
    
    
    return nicDriver;
}


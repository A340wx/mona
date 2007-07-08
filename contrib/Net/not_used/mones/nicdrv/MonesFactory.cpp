/*!
    \file   MonesFactory.cpp
    \brief  Mones NIC�h���C�o�C���X�^���X ���[�_�[

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/10/31 update:$Date$
*/

/*! \class MonesFactory
 *  \brief Mones NIC�h���C�o�C���X�^���X ���[�_�[
 */


#include <pci/Pci.h>

#include "MonesFactory.h"
#include <nicdrv/AbstractMonic.h>
#include "ne2000/Ne2000MoNic.h"
#include "tulip/tulipMoNic.h"

/*!
    \brief initialize
         MonesFactory �R���X�g���N�^
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
MonesFactory::MonesFactory()
{

}


/*!
    \brief initialize
         MonesFactory �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
MonesFactory::~MonesFactory() 
{

}


/*!
    \brief setup
         MonesFactory setup
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
void MonesFactory::setup() 
{
    //�������Ȃ��B

}


/*!
    \brief getNicInstance
         NIC�h���C�o�̃C���X�^���X�𓾂�B
    \author Yamami
    \date   create:2004/10/31 update:$Date$
*/
AbstractMonic* MonesFactory::getNicInstance() 
{
    
    //TODO 2004/10/31 ����
    // PCI�f�o�C�X�������āA������� QEMU / ������Ȃ���� Bochs �Ɣ��f��
    // NE2000�h���C�o�����[�h����B
    // ���̑����ł́A���[�h�Ɏ��s
    
    int ret;
    //PciInf *pciinfo;              //PCI���C�u����

    PciInf RetPciInf; //�ԋp�p PciInf�\����
    
    AbstractMonic *nicDriver;
    
    //PCI���C�u�����N���X�̃C���X�^���X��
    Pci* pcilib = new Pci();
    
    //TODO �ꎞ���̂��Ȃ̂ŁA�}�W�b�N�i���o�[��p����
    //QEMU��́ANE2000��T��
    pcilib->CheckPciExist(0x10EC,0x8029,&RetPciInf);
    
    if(RetPciInf.Exist == 0){
        //�������
        //NE2000�̃��[�h
        nicDriver = new Ne2000MoNic();
        
        //QEMU�ݒ�
        //nicDriver->setNicIRQ(9);
        //nicDriver->setNicIOBASE(0xC100);
        nicDriver->setNicIRQ(RetPciInf.IrqLine);
        nicDriver->setNicIOBASE(RetPciInf.BaseAd -1);
        
    }
    
    //VirtualPC��́ADEC21140��T��
    pcilib->CheckPciExist(0x1011,0x0009,&RetPciInf);
    if(RetPciInf.Exist == 0){
        //�������
        //tulip�̃��[�h
        nicDriver = new tulipMoNic();
        
        //VirtualPC�ݒ�
        nicDriver->setNicIRQ(11);
        nicDriver->setNicIOBASE(0xEC00);
        
    }
    
//    else{
//        //������Ȃ����
//        //ISA NE2000�̃��[�h
//        nicDriver = new Ne2000MoNic();
//        
//        //Bochs�ݒ�
//        nicDriver->setNicIRQ(3);
//        nicDriver->setNicIOBASE(0x240);
//    
//    }
    
    
    //NIC������
    ret = nicDriver->init();
    
    //if(ret != 0){
    //    //�������Ɏ��s�����ꍇ�ANULL�h���C�o��Ԃ��B
    //    nicDriver = 0;
    //    
    //}
    
    delete pcilib;
    
    return nicDriver;
}


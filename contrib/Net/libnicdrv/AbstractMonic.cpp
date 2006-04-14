/*!
    \file  AbstractMonic.cpp
    \brief ����NIC�N���X

    Copyright (c) 2004 Yamami
    WITHOUT ANY WARRANTY

    \author  Yamami
    \version $Revision$
    \date   create:2004/09/04 update:$Date$
*/


/*! \class AbstractMonic
 *  \brief ����NIC�N���X
 */


//#include "AbstractMonic.h"
#include <AbstractMonic.h>

using namespace MonAPI;

/*!
    \brief AbstractMonic �R���X�g���N�^

    \author Yamami
    \date   create:2004/09/04 update:
*/
AbstractMonic::AbstractMonic()
{
    waitFrameBufList = new HList<WAIT_FRAME_BUF*>();
}


/*!
    \brief AbstractMonic �f�X�N�g���N�^

    \author Yamami
    \date   create:2004/09/04 update:
*/
AbstractMonic::~AbstractMonic()
{
    //��������
}


/*!
    \brief disable netRecv interrupt

    \author Yamami
    \date   create:2004/08/08 update:
*/
void AbstractMonic::disableNetWork() 
{

    byte IrqMask;
    int  nicIrqNo;
    
    IrqMask = 0x00;
    
    //�q�N���X�̃Q�b�^�[�ŁAIRQ�擾
    nicIrqNo = getNicIRQ();
    
    if(0 <= nicIrqNo && nicIrqNo <= 7){
        //IRQ�͈̔͂��A0�`7�ł����
        //PIC-0�}�X�^��IMR(0x21)�֊��荞�݃}�X�N
        IrqMask = 1 << (nicIrqNo - 0);
        outp8(0x21, (inp8(0x21) | IrqMask));
    }
    else if(8 <= nicIrqNo && nicIrqNo <= 15){
    
        //IRQ�͈̔͂��A8�`15�ł����
        //PIC-1�X���[�u��IMR(0xA1)�֊��荞�݃}�X�N
        IrqMask = 1 << (nicIrqNo - 8);
        outp8(0xA1, (inp8(0xA1) | IrqMask));
    
    }
    
}


/*!
    \brief enable netRecv interrupt

    \author Yamami
    \date   create:2004/08/08 update:
*/
void AbstractMonic::enableNetWork() 
{

    byte IrqMask;
    int  nicIrqNo;
    
    IrqMask = 0xFF;

    //�q�N���X�̃Q�b�^�[�ŁAIRQ�擾
    nicIrqNo = getNicIRQ();

    if(0 <= nicIrqNo && nicIrqNo <= 7){
        //IRQ�͈̔͂��A0�`7�ł����
        //PIC-0�}�X�^��IMR(0x21)�֊��荞�݃}�X�N
        IrqMask = IrqMask ^ (1 << (nicIrqNo - 0));  //XOR ���Y�r�b�g�̂�0�Ƃ���B
        outp8(0x21, (inp8(0x21) & IrqMask));
    }
    else if(8 <= nicIrqNo && nicIrqNo <= 15){
    
        //IRQ�̃J�X�P�[�h���}�X�N
        outp8(0x21, (inp8(0x21) & 0xFB)); /* IR2 cascade */
    
        //IRQ�͈̔͂��A8�`15�ł����
        //PIC-1�X���[�u��IMR(0xA1)�֊��荞�݃}�X�N
        IrqMask = IrqMask ^ (1 << (nicIrqNo - 8));  //XOR ���Y�r�b�g�̂�0�Ƃ���B
        outp8(0xA1, (inp8(0xA1) & IrqMask));
    }
    
}

/*!
    \brief �t���[����M���� 

    \author Yamami
    \date   create:2005/05/22 update:
*/
void AbstractMonic::frame_input_public() 
{

    //�t���[����M���� H/W �q�N���X�ֈϏ�
    //frame_buf[1500] �֊i�[����鎖������
    frame_input();
    
    
    //�����҂����X�g�֓o�^
    //�T�C�Y���̋��L���������m�ۂ��A�ۑ��B�n���h�������X�g�֓o�^
    //�܂��Amonapi_cmemoryinfo�\���̂�new
    monapi_cmemoryinfo* cmInfo = new monapi_cmemoryinfo();
    
    if (!monapi_cmemoryinfo_create(cmInfo, frame_len , 0)){
        monapi_cmemoryinfo_delete(cmInfo);
        //TODO �m�ۂł��Ȃ�������ǂ�����H
        return;
    }
    
    //���L���������}�b�v�AData�v�f�Ɋm�ۂ����o�C�g�񂪃Z�b�g�����B
    monapi_cmemoryinfo_map(cmInfo);
    
    //���L�������ցA�p�P�b�g�Z�b�g
    memcpy(cmInfo->Data , frame_buf, frame_len);
    
    //���X�g�֓o�^
    WAIT_FRAME_BUF *addWork = new WAIT_FRAME_BUF();
    addWork->cmHandle = cmInfo->Handle;
    addWork->cmSize = cmInfo->Size;
    
    waitFrameBufList->add(addWork);
    
    //�v���g�R���w�֏����v�����b�Z�[�W���M
    dword targetID = Message::lookupMainThread("MONES.EX5");
    if (targetID == 0xFFFFFFFF){
        //TODO �ł��Ȃ�������ǂ�����H
    }

    MessageInfo info;
    Message::create(&info, MSG_MONES_FRAME_REQ, 0, 0, 0, NULL);

    // send
    if (Message::send(targetID, &info)) {
        //TODO �ł��Ȃ�������ǂ�����H
    }
    

}

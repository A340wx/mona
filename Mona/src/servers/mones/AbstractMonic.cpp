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


#include "AbstractMonic.h"

/*!
    \brief AbstractMonic �R���X�g���N�^

    \author Yamami
    \date   create:2004/09/04 update:
*/
AbstractMonic::AbstractMonic()
{
    //��������
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
        outp8(0x21, inp8(0x21) | IrqMask);
    }
    else if(8 <= nicIrqNo && nicIrqNo <= 15){
    
        //IRQ�͈̔͂��A8�`15�ł����
        //PIC-1�X���[�u��IMR(0xA1)�֊��荞�݃}�X�N
        IrqMask = 1 << (nicIrqNo - 8);
        outp8(0xA1, inp8(0x21) | IrqMask);
    
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
printf("IrqMask = %x \n",IrqMask);
        outp8(0x21, inp8(0x21) & IrqMask);
    }
    else if(8 <= nicIrqNo && nicIrqNo <= 15){
    
        //IRQ�̃J�X�P�[�h���}�X�N
        outp8(0x21, (inp8(0x21) & 0xFB)); /* IR2 cascade */
    
        //IRQ�͈̔͂��A8�`15�ł����
        //PIC-1�X���[�u��IMR(0xA1)�֊��荞�݃}�X�N
        IrqMask = IrqMask ^ (1 << (nicIrqNo - 8));  //XOR ���Y�r�b�g�̂�0�Ƃ���B
printf("IrqMask Set = %x \n",IrqMask);
        outp8(0xA1, inp8(0xA1) & IrqMask);
    }
    
    IrqMask=inp8( 0xA1 );
    
//Yamami!!! �킴�ƃo�O    
//outp8(0x21, inp8(0x21) | 0x04);

printf("0xA1 IN After = %x \n",IrqMask);
    
}

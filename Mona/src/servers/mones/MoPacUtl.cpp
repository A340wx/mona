/*!
    \file   MoPacUtl.cpp
    \brief  Mona �p�P�b�g���[�e�B���e�B�N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/08/18 update:$Date$
*/

/*! \class MoPacUtl
 *  \brief Mona �p�P�b�g���[�e�B���e�B�N���X
 */



#include "MoPacUtl.h"


/*!
    \brief initialize
         MoPacUtl �R���X�g���N�^
    \author Yamami
    \date   create:2004/08/12 update:
*/
MoPacUtl::MoPacUtl()
{

}

/*!
    \brief initialize
         MoEther init
    \author Yamami
    \date   create:2004/08/12 update:
*/



/*!
    \brief initialize
         MoPacUtl �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/08/12 update:
*/
MoPacUtl::~MoPacUtl() 
{

}


/*!
    \brief packet_get_4byte
         4�o�C�g�p�P�b�g�擾
         �l�b�g���[�N�G���f�B�A���ϊ�
    \param  byte *buf [in] �Ώۃo�b�t�@
    \param  int offset [in] �ΏۃI�t�Z�b�g
    \return dword �擾�l
    
    \author Yamami
    \date   create:2004/08/18 update:
*/
dword MoPacUtl::packet_get_4byte(byte *buf, int offset)
{
    dword a, b, c;

    a = (dword)buf[offset++] << 24;
    b = (dword)buf[offset++] << 16;
    c = (dword)buf[offset++] << 8;

    return a | b | c | buf[offset];
}

/*!
    \brief packet_get_2byte
         2�o�C�g�p�P�b�g�擾
         �l�b�g���[�N�G���f�B�A���ϊ�
    \param  byte *buf [in] �Ώۃo�b�t�@
    \param  int offset [in] �ΏۃI�t�Z�b�g
    \return word �擾�l
    
    \author Yamami
    \date   create:2004/08/18 update:
*/
word MoPacUtl::packet_get_2byte(byte *buf, dword offset)
{
    word a;

    a = buf[offset++] << 8;
    
    return a | buf[offset];
}


/*!
    \brief packet_put_4byte
         4�o�C�g�p�P�b�g�ݒ�
         �l�b�g���[�N�G���f�B�A���ϊ�
    \param  byte *buf [in] �Ώۃo�b�t�@
    \param  int offset [in] �ΏۃI�t�Z�b�g
    \param  idword [in] �ݒ�l
    \return void ����
    
    \author Yamami
    \date   create:2004/08/18 update:
*/
void MoPacUtl::packet_put_4byte(byte* buf, int offset, dword val)
{
    buf += offset;
    *buf++ = (val >> 24) & 0xff;
    *buf++ = (val >> 16) & 0xff;
    *buf++ = (val >>  8) & 0xff;
    *buf = val & 0xff;
}

/*!
    \brief packet_put_2byte
         2�o�C�g�p�P�b�g�ݒ�
         �l�b�g���[�N�G���f�B�A���ϊ�
    \param  byte *buf [in] �Ώۃo�b�t�@
    \param  int offset [in] �ΏۃI�t�Z�b�g
    \param  iword [in] �ݒ�l
    \return void ����
    
    \author Yamami
    \date   create:2004/08/18 update:
*/
void MoPacUtl::packet_put_2byte(byte* buf, int offset, word val)
{
    buf += offset;
    *buf++ = (val >> 8) & 0xff;
    *buf = val & 0xff;
}



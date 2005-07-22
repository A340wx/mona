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



/*!
    \brief calcCheckSum
         �`�F�b�N�T���֐�
    \param  dword *data [in] �`�F�b�N�Ώ�
    \param  int size [in] �`�F�b�N�ΏۃT�C�Y
    \return word 
    
    \author Yamami
    \date   create:2004/09/20 update:
*/
word MoPacUtl::calcCheckSum(dword *data,int size)
{
    union{
        unsigned long long u64;
        dword            u32[2];
        word             u16[4];
    }sum;

    dword tmp;


    sum.u64=0;
    for(;(dword)size>=sizeof(dword);size-=sizeof(dword))
        sum.u64+=*data++;
    if(size>0)sum.u64+=*data&((1<<(size*8))-1);

    tmp=sum.u32[1];
    sum.u32[1]=0;
    sum.u64+=tmp;
    tmp=sum.u32[1];
    sum.u32[1]=0;
    sum.u32[0]+=tmp;

    tmp=sum.u16[1];
    sum.u16[1]=0;
    sum.u32[0]+=tmp;
    tmp=sum.u16[1];
    sum.u16[1]=0;
    sum.u16[0]+=tmp;

    return ~sum.u16[0];
}



/*!
    \brief calcCheckSumDummyHead
         TCP/UDP�p�B�_�~�[�w�b�_���� �`�F�b�N�T���֐�
    \param  dword *dmhead [in] �_�~�[�w�b�_ �`�F�b�N�T���Ώ�
    \param  dword *data [in] �`�F�b�N�Ώۃf�[�^
    \param  int dmsize [in] �_�~�[�w�b�_�ΏۃT�C�Y
    \param  int size [in] �`�F�b�N�ΏۃT�C�Y
    \return word 
    
    \author Yamami
    \date   create:2005/07/17 update:
*/
word MoPacUtl::calcCheckSumDummyHead(dword *dmhead,dword *data,int dmsize,int size)
{
    union{
        unsigned long long u64;
        dword               u32[2];
        word             u16[4];
    }sum;
    
    dword tmp;


    sum.u64=0;
    for(;dmsize>=sizeof(dword);dmsize-=sizeof(dword))
        sum.u64+=*dmhead++;
    for(;size>=sizeof(dword);size-=sizeof(dword))
        sum.u64+=*data++;
    if(size>0)sum.u64+=*data&((1<<(size*8))-1);

    tmp=sum.u32[1];
    sum.u32[1]=0;
    sum.u64+=tmp;
    tmp=sum.u32[1];
    sum.u32[1]=0;
    sum.u32[0]+=tmp;

    tmp=sum.u16[1];
    sum.u16[1]=0;
    sum.u32[0]+=tmp;
    tmp=sum.u16[1];
    sum.u16[1]=0;
    sum.u16[0]+=tmp;

    return ~sum.u16[0];
}


/*!
    \brief createPacMsg
         �p�P�b�g�i�[���b�Z�[�W�쐬
    \param  MessageInfo *info [OUT] �쐬���b�Z�[�W
    \param  Socket *soc [in] �ʒm�\�P�b�g
    
    \return int ���� 
    
    \author Yamami
    \date   create:2005/05/22 update:
*/
int MoPacUtl::createPacMsg(MessageInfo *info, Socket *soc )
{

    //���L��������Socket�i�[
    //�܂��Amonapi_cmemoryinfo�\���̂�new
    monapi_cmemoryinfo* cmInfo = new monapi_cmemoryinfo();
    
    if (!monapi_cmemoryinfo_create(cmInfo, sizeof(Socket) + 1, 0))
    {
        monapi_cmemoryinfo_delete(cmInfo);
        return 1;
    }
    
    //���L���������}�b�v�AData�v�f�Ɋm�ۂ����o�C�g�񂪃Z�b�g�����B
    //monapi_cmemoryinfo_map(cmInfo);
    
    //���L�������ցASocket�i�[ 
    //TODO �P����memcpy�ł����̂��H
    memcpy(cmInfo->Data , soc, sizeof(Socket));
    
logprintf("sizeof(Socket) = %d \n",sizeof(Socket));

packet_cmemoryinfo pcm;
pcm = soc->recvBuff[0];
logprintf("createPacMsg pcm.Handle=%d pcm.Owner=%d pcm.Size=%d\n",pcm.Handle , pcm.Owner ,pcm.Size);    

pcm = ((Socket*)cmInfo->Data)->recvBuff[0];
logprintf("Cast!!! pcm.Handle=%d pcm.Owner=%d pcm.Size=%d\n",pcm.Handle , pcm.Owner ,pcm.Size);        


    info->length = sizeof(Socket);
    info->arg1 = 1;
    info->arg2 = cmInfo->Handle;
    info->arg3 = cmInfo->Size;
    
    return 0;
  

}

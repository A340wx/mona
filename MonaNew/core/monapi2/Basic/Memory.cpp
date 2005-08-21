/**
	@file	Memory.cpp
	@brief	�������ǂݍ��݁E�������������݁E����������

	�������ǂݍ��݁E�������������݁E����������

	License=Mona License
    \version $Revision$
    \date	$Date$
*/

#include "Switch.h"
#include "Memory.h"
#include "Math.h"

using namespace monapi2;

/*
�����������B

for�̏�����
	for(uint n=0;n<count;n++)
�Ə����Ƃ���
	for(uint n=count;n>0;n--)
�Ə����Ƃ��͌�҂̕������[�v���Ƃ�count�̒l���Ăяo���K�v���Ȃ��̂ő���������
��r�e�X�g�������ʂ͈Ⴂ�͂Ȃ������B

�R���p�C���̍œK�������łǂ������ő��Ȍ`�ɒ������̂��B
�������͋C�ɂ��Ȃ��ł悳�������B
*/


///@author junjunn @date update:2005/08/20
void MemoryFn::copy(void* pTo,const void* cpFrom, uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
//�܂��]���o�C�g����4�Ŋ����ď��Ə�]���v�Z���A4�o�C�g�]����1�o�C�g�]���ɂ킯��B
	int i4ByteCount,i1ByteCount;
	MathFn::divide(nCount,4,&i4ByteCount,&i1ByteCount);

#ifdef _COMPILER_VISUALC

//4�o�C�g�]��
	__asm
	{
		mov edi,pTo			//���W�X�^�Z�b�g
		mov esi,cpFrom
		mov ecx,i4ByteCount
		cld					//�������]���w��
		rep movsd			//4�o�C�g�]������
	}

//1�o�C�g�]��
	__asm
	{
		mov ecx,i1ByteCount	//���̃��W�X�^�l��4�o�C�g�]���̎��ɃZ�b�g���������痬�p
		rep movsb			//1�o�C�g�]��
	}
#else
//4�o�C�g�]������
    asm volatile("movl %0, %%edi \n"
                 "movl %1, %%esi \n"
                 "movl %2, %%ecx \n"
                 "cld            \n"
                 "rep movsd      \n"
                 :
                 : "m"(pTo), "m"(cpFrom), "m"(i4ByteCount)
                 : "edi", "esi", "ecx");

//1�o�C�g�]������
    asm volatile("movl %0, %%ecx \n"
                 "rep movsb      \n"
                 :
                 : "m"(i1ByteCount)
                 : "ecx");
#endif
}

///@author junjunn @date update:2005/08/20
void MemoryFn::swap(void* pBuffer1,void* pBuffer2,uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
	int i4ByteCount,i1ByteCount;
	MathFn::divide(nCount,4,&i4ByteCount,&i1ByteCount);

//4�o�C�g�]������
	uint32* pdwBuffer1=(uint32*)pBuffer1;
	uint32* pdwBuffer2=(uint32*)pBuffer2;
	for(uint n=0;n<(uint)i4ByteCount;n++)
	{
		int iTemp = *pdwBuffer1;
		*pdwBuffer1++ = *pdwBuffer2;
		*pdwBuffer2++ = iTemp;
	}

//1�o�C�g�]������
	uint8* pcBuffer1=(uint8*)pdwBuffer1;
	uint8* pcBuffer2=(uint8*)pdwBuffer2;
	for(n=0;n<(uint)i1ByteCount;n++)
	{
		char cTemp = *pcBuffer1;
		*pcBuffer1++ = *pcBuffer2;
		*pcBuffer2++ = cTemp;
	}
}

///@author junjunn @date update:2005/08/20
void MemoryFn::copySafe(void* pTo, const void* cpFrom,uint nCount)
{
//���ʂ�copy�ł͍������
	if (pTo>cpFrom && pTo<(uint8*)cpFrom+nCount)
	{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
		int i4ByteCount,i1ByteCount;
		MathFn::divide(nCount,4,&i4ByteCount,&i1ByteCount);

//���Ε�������R�s�[
//1�o�C�g�]������
		uint8* pcTo		=(uint8*)pTo	+ nCount;
		uint8* cpcFrom	=(uint8*)cpFrom	+ nCount;
		for(uint n=0;n<(uint)i1ByteCount;n++)
		{
			*--pcTo = *--cpcFrom;
		}

//4�o�C�g�]������
		uint32* pdwTo		=(uint32*)pcTo;
		uint32* cpdwFrom	=(uint32*)cpcFrom;
		for(n=0;n<(uint)i4ByteCount;n++)
		{
			*--pdwTo = *--cpdwFrom;
		}
	}
	else
	{
		copy(pTo,cpFrom,nCount);
	}
}

///@author junjunn @date update:2005/08/20
int MemoryFn::compare(const void* cpBuffer1,const void* cpBuffer2,uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g��r���g���B
	int i4ByteCount,i1ByteCount;
	MathFn::divide(nCount,4,&i4ByteCount,&i1ByteCount);

	uint32* cpdwBuffer1=(uint32*)cpBuffer1;
	uint32* cpdwBuffer2=(uint32*)cpBuffer2;
	for (uint n=0;n<(uint)i4ByteCount;n++)
	{
		if (*cpdwBuffer1!=*cpdwBuffer2)
		{
			uint8* cpcBuffer1=(uint8*)cpdwBuffer1;
			uint8* cpcBuffer2=(uint8*)cpdwBuffer2;
			for(n=0;n<4;n++)
			{
				if (*cpcBuffer1!=*cpcBuffer2)	return (cpcBuffer1-(uint8*)cpBuffer1);

				cpcBuffer1++;
				cpcBuffer2++;
			}
		}

		cpdwBuffer1++;
		cpdwBuffer2++;
	}

	uint8* cpcBuffer1=(uint8*)cpdwBuffer1;
	uint8* cpcBuffer2=(uint8*)cpdwBuffer2;
	for(n=0;n<(uint)i1ByteCount;n++)
	{
		if (*cpcBuffer1!=*cpcBuffer2)	return (cpcBuffer1-(uint8*)cpBuffer1);

		cpcBuffer1++;
		cpcBuffer2++;
	}

	return 0;
}

///@author junjunn @date update:2005/08/20
void MemoryFn::set(void* pTo,int iValue,uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
	int i4ByteCount,i1ByteCount;
	MathFn::divide(nCount,4,&i4ByteCount,&i1ByteCount);

//4�o�C�g�]������
	uint32* pdwTo=(uint32*)pTo;
	int iValue4 = iValue + (iValue<<8) + (iValue<<16) + (iValue<<24);
	for(uint n=0;n<(uint)i4ByteCount;n++)
	{
		*pdwTo++ = iValue4;
	}

//1�o�C�g�]������
	uint8* pcTo=(uint8*)pdwTo;
	for(n=0;n<(uint)i1ByteCount;n++)
	{
		*pcTo++ = (uint8)iValue;
	}
}

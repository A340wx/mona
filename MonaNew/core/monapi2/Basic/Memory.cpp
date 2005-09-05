/**
	@file	Memory.cpp
	@brief	�������ǂݍ��݁E�������������݁E����������

	�������ǂݍ��݁E�������������݁E����������

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Memory.h"
#include "Math.h"

namespace monapi2	{

/*
�E����������1

	for�̏�����
		for(uint n=0;n<nCount;n++)
	�Ə����Ƃ���
		for(uint n=nCount;n>0;n--)
	�Ə����Ƃ��͌�҂̕������[�v���Ƃ�nCount�̒l���Ăяo���K�v���Ȃ��̂ő���������
	��r�e�X�g�������ʂ͈Ⴂ�͂Ȃ������B

	�R���p�C���̍œK�������Ŏ��s���ɂ͂ǂ������ő��Ȍ`�ɒ������̂��B
	�������͋C�ɂ��Ȃ��ł悳�������B


�E����������2

	�����ł�nCount�̘A������������
		divide(nCount,4,&i4ByteCount,&i1ByteCount);
		for(uint n=0;n<(uint)i4ByteCount;n++)		{*pdwTo++ = iValue4;}
	�Ȋ����ł���Ă��邪�ʂ̏������Ƃ���
		for (;nCount>=4;nCount-=4)					{*pdwTo++ = iValue4;}
	�Ƃ��ɂ�����ǂ��Ȃ邩�B

	��҂̕���divide���ĂԎ�Ԃ��Ȃ��R�[�h�ʂ������ăX�}�[�g�Ɍ����邪���ۂ͒x���Ȃ�B
	�O�҂̏��������ƃ��[�v�̒���++�̉\�Ȍ���̃V���v���ȃ��[�v�ɂȂ�̂ɔ��
	��҂̓��[�v�J�E���^�̑���-=4�̌v�Z�������Ă��ꂪ�y�i���e�B�ɂȂ�悤���B

	
���̑��ɂ�������������MemoryFn::set�ɂ��傱���傱�����Ă܂��B
*/


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void MemoryFn::copy(void* pTo,const void* cpFrom, uint nCount)
{
//@memo ������������4�o�C�g���E�΍􂪕K�v�����B

//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
//�܂��]���o�C�g����4�Ŋ����ď��Ə�]���v�Z���A4�o�C�g�]����1�o�C�g�]���ɂ킯��B
	int i4ByteCount,i1ByteCount;
	divide(nCount,4,&i4ByteCount,&i1ByteCount);

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

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void MemoryFn::swap(void* pBuffer1,void* pBuffer2,uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
	int i4ByteCount,i1ByteCount;
	divide(nCount,4,&i4ByteCount,&i1ByteCount);

//4�o�C�g�]������
	uint32* pdwBuffer1=(uint32*)pBuffer1;
	uint32* pdwBuffer2=(uint32*)pBuffer2;
	uint n;
	for(n=0;n<(uint)i4ByteCount;n++)
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

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void MemoryFn::copySafe(void* pTo, const void* cpFrom,uint nCount)
{
//���ʂ�copy�ł͍������
	if (pTo>cpFrom && pTo<(uint8*)cpFrom+nCount)
	{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
		int i4ByteCount,i1ByteCount;
		divide(nCount,4,&i4ByteCount,&i1ByteCount);

//���Ε�������R�s�[
//1�o�C�g�]������
		uint8* pcTo		=(uint8*)pTo	+ nCount;
		uint8* cpcFrom	=(uint8*)cpFrom	+ nCount;
		uint n;
		for(n=0;n<(uint)i1ByteCount;n++)
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

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int MemoryFn::findDiff(const void* cpBuffer1,const void* cpBuffer2,uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g��r���g���B
	int i4ByteCount,i1ByteCount;
	divide(nCount,4,&i4ByteCount,&i1ByteCount);

	uint32* cpdwBuffer1=(uint32*)cpBuffer1;
	uint32* cpdwBuffer2=(uint32*)cpBuffer2;
	uint n;
	for (n=0;n<(uint)i4ByteCount;n++)
	{
//�Ⴂ����������1�o�C�g��r�ɐ؂�ւ��B
		if (*cpdwBuffer1!=*cpdwBuffer2)
		{
			uint8* cpcBuffer1=(uint8*)cpdwBuffer1;
			uint8* cpcBuffer2=(uint8*)cpdwBuffer2;
			for (;;)	//�K������4�o�C�g���Ɏ~�܂�̂ŕK�v�Ȃ��B
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

	return -1;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void MemoryFn::set(void* pTo,int iValue,uint nCount)
{
//�X�s�[�h���グ�邽�߂�4�o�C�g�]�����g���B
	uint32* pdwTo=(uint32*)pTo;
	int iValue4 = iValue + (iValue<<8) + (iValue<<16) + (iValue<<24);


//�X�s�[�h�����̂��߂ɓ�̈Ⴄ�������Ŏ��������݂Ă݂�B

//�P�[�X1�Bdivide�͎g��Ȃ���-=4���[�v���g���B�x���B10000000��̃��[�v��35.0�b���������B
#if 0
	for (;nCount>=4;nCount-=4)
	{
		*pdwTo++ = iValue4;
	}

/*
��L��for�̒���VC�ɂ��œK����A�Z���u��

00401971 	mov	ebx,[ebp+00000010h]	//ebx = n2
00401974 	cmp	ebx,04h				//if (n2>4)
00401977 	jc	00401992h			//if (n2>4) goto 401992

00401979 	push	esi
0040197A 	mov	esi,ebx
0040197C 	shr	esi,02h
0040197F 	mov	ecx,esi
00401981 	mov	eax,edx
00401983 	repz
00401984 	stosd
00401985 	mov	eax,[ebp+00000008h]
00401988 	lea	edi,[eax+esi*4]

0040198B 	sub	ebx,04h
0040198E 	dec	esi
0040198F 	jnz	0040198Bh
00401991 	pop	esi

00401997 	test	ebx,ebx
00401999 	jbe	004019BAh
0040199B 	mov	al,[ebp+0000000Ch]
0040199E 	mov	ecx,ebx
004019A0 	mov	bl,al
004019A2 	mov	edx,ecx
004019A4 	mov	bh,bl
004019A6 	mov	eax,ebx
004019A8 	shl	eax,10h
004019AB 	mov	ax,bx
004019AE 	shr	ecx,02h
004019B1 	repz
004019B2 	stosd
004019B3 	mov	ecx,edx
004019B5 	and	ecx,03h
004019B8 	repz
004019B9 	stosb
�`return
*/
	uint n;
	int i1ByteCount =nCount;

//�P�[�X2�Bdivide�ŕ�����++���[�v���g���B�����B10000000��̃��[�v��7.5�b���������B
#else
	int i4ByteCount,i1ByteCount;
	divide(nCount,4,&i4ByteCount,&i1ByteCount);

	uint n;
	for(n=0;n<(uint)i4ByteCount;n++)
	{
		*pdwTo++ = iValue4;
	}

/*
��L��for�̒���VC�ɂ��œK����A�Z���u��

00401988 	mov	edx,[ebp+0000000Ch]		:.
0040198B 	test	edx,edx				:.
0040198D 	jbe	0040199Bh				:if (n2!=0)	goto 40199B

0040198F 	mov	ecx,edx					:ecx=n2;
00401991 	mov	eax,esi					:eax=
00401993 	repz
00401994 	stosd
00401995 	mov	eax,[ebp+00000008h]
00401998 	lea	edi,[eax+edx*4]

004019A0 	mov	ecx,[ebp+00000010h]
004019A3 	test	ecx,ecx
004019A5 	jbe	004019C1h
004019A7 	mov	al,bl
004019A9 	mov	bh,bl
004019AB 	mov	eax,ebx
004019AD 	mov	edx,ecx
004019AF 	shl	eax,10h
004019B2 	mov	ax,bx
004019B5 	shr	ecx,02h
004019B8 	repz
004019B9 	stosd
004019BA 	mov	ecx,edx
004019BC 	and	ecx,03h
004019BF 	repz
004019C0 	stosb
�`return
*/
#endif


//1�o�C�g�]������
	uint8* pcTo=(uint8*)pdwTo;
	for(n=0;n<(uint)i1ByteCount;n++)
	{
		*pcTo++ = (uint8)iValue;
	}
/*
������
	uint anMask1[4] ={0x00000000,0x000000FF,0x0000FFFF,0x00FFFFFF};
	uint anMask2[4] ={0xFFFFFFFF,0xFFFFFF00,0xFFFF0000,0xFF000000};
	*pdwTo &= anMask2[i1ByteCount];
	*pdwTo |= 0x12345678 & anMask1[i1ByteCount];
�̂悤�ɏ����Ώ��Ȃ��čςނƎv����
�����񂹂񂱂ꂾ�ƈꎞ�I�ɂƂ͌���dword�Ńo�b�t�@�̊_�����z����
read�Awrite���Ă��ĕی�ᔽ���炢�����Ȃ̂Ŏ~�߂�B
*/
}


}		//namespace monapi2

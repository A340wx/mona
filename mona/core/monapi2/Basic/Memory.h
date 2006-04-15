/**
	@file	Memory.h
	@brief	�������ǂݍ��݁E�������������݁E����������

	�������ǂݍ��݁E�������������݁E����������

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_MEMORY_H
#define _MONAPI2_BASIC_MEMORY_H

#include "switch.h"
#include "Type.h"

namespace monapi2	{

#ifndef SAFE_DELETE
//delete������ɊԈ���Ďg���Ȃ��悤�����B
	#define SAFE_DELETE(p)	{delete p;p=NULL;}
#endif

/**
	@brief	����������BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class MemoryFn
{
public:
	static uint copy(void* pTo,const void* cpFrom,uint nCount);
	static void swap(void* pBuffer1,void* pBuffer2,uint nCount);
	static void copySafe(void* pTo, const void* cpFrom,uint nCount);
	static int findDiff(const void* cpBuffer1,const void* cpBuffer2,uint nCount);
	static void set(void* pto,int iValue,uint nCount);
	static bool isEqual(const void* cpBuffer1,const void* cpBuffer2,uint nCount)
		{return (findDiff(cpBuffer1,cpBuffer2,nCount)==-1);}
};

}	//namespace monapi2


#endif

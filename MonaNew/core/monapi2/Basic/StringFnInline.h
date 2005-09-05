/**
	@file	StringInline.h
	@brief	String.h�̃C�����C���֐��̓W�J

	String.h�̃C�����C���֐��̓W�J

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_STRINGFNINLINE_H
#define _MONAPI2_BASIC_STRINGFNINLINE_H

#include "StringFn.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool StringFn::isEqual(pcchar1 cszP,pcchar1 cszQ,int iCompareCount)
{
//�ŏ���1�����������ׂĂ������Ⴆ��compare�֐����Ăяo���O�ɏI��点���B
	if (cszP[0]!=cszQ[0])	return false;

	return (findDiff(cszP,cszQ,iCompareCount)==-1);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool StringFn::isEqualNoCase(pcchar1 cszP,pcchar1 cszQ,int iCompareCount)
{
	return (findDiffNoCase(cszP,cszQ,iCompareCount)==-1);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool StringFn::isEmpty(pcchar1 cszSource)
{
	return isEqual(cszSource,"");
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 StringFn::findEnd(pcchar1 pAt)
{
	return (pchar1)(pAt+getLength(pAt));
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void StringFn::empty(pchar1 szSource)
{
	szSource[0]='\0';
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::join(pchar1 szOut,pcchar1 cszIn,int iCopyCount)
{
	szOut = findEnd(szOut);
	return copy(szOut,cszIn,iCopyCount);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::remove(pchar1 szSrc,pcchar1 cszRemove)
{
	return replace(szSrc,cszRemove,"");
}

}	//namespace monapi2

#endif

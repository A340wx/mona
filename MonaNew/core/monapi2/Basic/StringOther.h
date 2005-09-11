/**
	@file	StringFn.h
	@brief	������֘A

	������֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_STRINGOTHER_H
#define _MONAPI2_BASIC_STRINGOTHER_H

#include "Switch.h"
#include "Type.h"
#include "CollectionArray.h"

namespace monapi2	{

/**
	@brief	��������g�[�N��������ŋ�؂��ĕ��������o���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class StringDivide : protected StringArray
{
//���\�b�h
public:
///@name ����
//@{
	StringDivide()										{}							///<�R���X�g���N�^
	StringDivide(cpchar1 cszSource,cpchar1 cszToken)	{set(cszSource,cszToken);};	///<�R���X�g���N�^�BSet(cszStart,cszToken)�ɂȂ�B
	void set(cpchar1 cszSource,cpchar1 cszToken);			///<cszStart��cszToken�ŋ�؂�
//@}


	cpchar1	getAt(int iIndex)	const {return getStringArray()->getAt(iIndex);}	///<iIndex�̕������Ԃ�
	int		getCount()			const {return getStringArray()->getCount();}	///<�S�̗̂v�f����Ԃ�

	StringArray* getStringArray()	const {return ((StringArray*)this);}
};

}	//namespace monapi2

#endif

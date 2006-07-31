/**
	@file	StringFn.cpp
	@brief	������֘A

	������֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "StringFn.h"
#include "StringOther.h"

namespace monapi2
{

//StringDivide////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
cpchar1	StringDivide::getAt(uint iIndex)	const
{
	if (iIndex>=m_nCount)	return NULL;

	return m_apData[iIndex].getString();
}

//StringDivide////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/11/20	junjunn �쐬
*/
String*	StringDivide::getStringAt(uint iIndex)	const
{
	if (iIndex>=m_nCount)	return NULL;

	return &m_apData[iIndex];
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void StringDivide::set(cpchar1 cszStart,cpchar1 cszToken)
{
	getStringArray()->removeAll();

	int iLengthToken = StringFn::getLength(cszToken);

//�Ō�̋�؂�
	cpchar1 pLastAppear	= cszStart;
//���̋�؂�
	cpchar1 p			= cszStart;

//�������Č��������������u���B
	String strWord;
	while (p = StringFn::find(p,cszToken))
	{
		strWord.copy(pLastAppear,p-pLastAppear);

		add(strWord);

		p+=iLengthToken;
		pLastAppear=p;
	}

//�Ō�̍���
	add(pLastAppear);
}

}		//namespace monapi2

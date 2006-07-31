/**
	@file	CollectionMap.cpp
	@brief	�R���N�V���� �}�b�v

	�R���N�V���� �}�b�v

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "CollectionMap.h"

namespace monapi2
{

//�e���v���[�g���g���Ă���ƂȂ���.cpp���ƃ����N�G���[�ɂȕ�������̂�
//�������TemplateInline.h�ɓ����Ă���B

//MapBase///////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint getHash1(cpchar1 cszKey,uint nHashTableSize)
{
	uint nHash=0;

	for (cpchar1 p = cszKey;*p;p++)
	{
		nHash = (nHash * 256 + *p) % nHashTableSize;
	}

	return nHash;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint getHash1(int iKey,uint nHashTableSize)
{
	return iKey % nHashTableSize;
}


//mapposition//////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
mapposition::mapposition()
{
	m_iListArrayIndex = 0;
	m_iListIndex = -1;
}

}

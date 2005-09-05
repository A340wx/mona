/**
	@file	CollectionList.cpp
	@brief	�R���N�V���� ���X�g

	�R���N�V���� ���X�g

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "CollectionList.h"
#include "StringFn.h"

namespace monapi2
{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int compareByPString(const void *p, const void *q)
{
	pcchar1 p2=((String*)p)->getString();
	pcchar1 q2=((String*)q)->getString();
	return StringFn::compare(p2,q2);
}

}

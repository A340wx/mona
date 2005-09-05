/**
	@file	Bit.h
	@brief	�r�b�g����

	�r�b�g����

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_BIT_H
#define _MONAPI2_BASIC_BIT_H

#include "switch.h"
#include "Type.h"

namespace monapi2	{

/**
	@brief int�^�̕ϐ��Ƀr�b�g�P�ʂœ��o�͂���Bstatic�N���X
	@date	2005/08/20	junjunn �쐬
*/
class BitFn
{
public:
	static bool get(int iTarget,int iBitIndex);				///<iTarget��iBit�Ԗڂ̃r�b�g��bool��Ԃ��B
	static void set(int *piTarget,int iBitIndex,bool bOn);	///<*piTarget��iBit�Ԗڂ̃r�b�g��bOn���Z�b�g����B

	static const uint m_acnBitMask[32];
};

}	//namespace monapi2

#endif

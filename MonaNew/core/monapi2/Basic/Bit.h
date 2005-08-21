/**
	@file	Memory.h
	@brief	�������ǂݍ��݁E�������������݁E����������

	�������ǂݍ��݁E�������������݁E����������

	License=Mona License
    \version $Revision$
    \date	$Date$
*/
#ifndef _MONAPI2_BASIC_BIT_H
#define _MONAPI2_BASIC_BIT_H

namespace monapi2	{

///int�^�̕ϐ��Ƀr�b�g�P�ʂœ��o�͂���Bstatic�N���X
class BitFn
{
public:
	static bool get(int iTarget,int iBitIndex);				///<iTarget��iBit�Ԗڂ̃r�b�g��bool��Ԃ��B
	static void set(int *piTarget,int iBitIndex,bool bOn);	///<*piTarget��iBit�Ԗڂ̃r�b�g��bOn���Z�b�g����B

	static const uint m_acnBitMask[32];
};

}	//namespace monapi2

#endif

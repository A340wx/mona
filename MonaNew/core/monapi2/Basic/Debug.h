/**
	@file	Debug.h
	@brief	�f�o�b�O

	�f�o�b�O

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_DEBUG_H
#define _MONAPI2_BASIC_DEBUG_H

#include "switch.h"
#include "Type.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
#define STOP {int _z=0;_z++;}

#ifndef ASSERT
	#define ASSERT(X)
#endif

#ifndef TRACE
	#define TRACE(X)
#endif

}	//namespace monapi2

#endif

/**
	@file	switch.h
	@brief	�R���p�C���̃I�v�V�����X�C�b�`

	�R���p�C���̃I�v�V�����X�C�b�`

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_SWITCH_H
#define _MONAPI2_BASIC_SWITCH_H

namespace monapi2	{

/**
	@date	2005/08/20	junjunn �쐬
*/

//�R���p�C���̑I���B
//�A�Z���u���̋L�q�@���Ⴄ���ߏꍇ�������Ă�B
//�I���F_COMPILER_VISUALC�A����#else

#ifdef _COMPILER_VISUALC
	#pragma warning(disable : 4127)	///<���������萔�ł��B
	#pragma warning(disable : 4514)	///<�Q�Ƃ���Ă��Ȃ���ײ݊֐��͍폜����܂����B
	#pragma warning(disable : 4706)	///<�������̔�r�l�́A����̌��ʂɂȂ��Ă��܂��B 
	#pragma warning(disable : 4710)	///<not inlined
	#pragma warning(disable : 4725) ///<Pentium �����قɂ���ẮA���߂��s���m�ɂȂ�܂��B
	#pragma warning(disable : 4786) ///<���ޯ�ޏ��Ŏ��ʎq�� 255 �����ɐ؂�̂Ă��܂����B
#endif	//#ifdef _COMPILER_VISUALC

}	//namespace monapi2

#endif

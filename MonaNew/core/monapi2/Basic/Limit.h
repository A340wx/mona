/**
	@file	Limit.h
	@brief	int��float�Ȃǂ̍ŏ��E�ő�̑傫���Ȃǌ^�̏��B

	int��float�Ȃǂ̍ŏ��E�ő�̑傫���Ȃǌ^�̏��B

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_LIMIT_H
#define _MONAPI2_BASIC_LIMIT_H

/*
�c�_�F#define���g���ׂ���enum���g���ׂ���const int,float���g���ׂ����B

�I�u�W�F�N�g�w���I�ɂ�const�ł���ׂ��ł��B
#define��enum�͒P���ȕ�����̃R�s�[�Ȃ̂Ń\�[�X�̊e�n�ɐ����̃R�s�[���܂��U�炵�܂��B

�Ⴆ��
>	#define PI 3.1415;
>	float f1=PI;
>	float f2=PI;
�Ƃ����Ƃ��͎��ۂɓW�J�����Ƃ���

>	float f1=3.1415;
>	float f2=3.1415;
�ƂȂ�\�[�X����"3.1415"��2�񌻂ꂻ��͂��݂��Ɋ֌W�̂Ȃ������̐����̃R�s�[�ł��B
�{����i1=i2=A�ƌ����}���͎���ꂽ�܂��ܐ����I�Ɉ�v���Ă��邾���ł��B

���̓_const���g��
>	const float PI = 3.1415;
>	float f1=PI;
>	float f2=PI;
�Ƃ����ꍇ�͓W�J���Ă�

>	float f1=PI;
>	float f2=PI;
const A�̐��l�����̏�ŃR���p�C�����₢���킹f1,f2�ɑ�����Ă��܂��B
����Ă������PI�̑��݂�const float PI��ӏ���1�̕����ϐ�PI��\���Ă���
�I�u�W�F�N�g�I�ɐ������\�}�ł��B


�Ӗ����킩��ɂ���������char*�ɒu�������Ă݂�Ƃ킩�邩������܂���E�E�E

>	#define PI "3.1415"
>	const char* A=PI;
>	const char* B=PI;
�Ƃ����ꍇA!=B�ł��B�Ȃ��Ȃ�W�J��ɂ�
>	const char* A="3.1415";
>	const char* B="3.1415";
�ƂȂ肻�ꂼ���"3.1415"�͕ʂ̃A�h���X�ɕʁX�ɍ��ꂽ������f�[�^������ł��B

������const���g����
>	const char* PI = "3.1415";
>	const char* A=PI;
>	const char* B=PI;
�Ƃ����ꍇA==B�ł��B�Ȃ��Ȃ�A��B������const char* PI�ւ̃A�h���X���w������ł��B

����ăI�u�W�F�N�g�w���I�ɂ�#define���g������const���������l�����ł��B


�X�s�[�h�I�ɂ͐������ߍ��݂�#define��萔���₢���킹��const�̕������Ԃ�������̂ŕs���ł����B
*/

namespace monapi2
{
/**
	@brief	�萔�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/

//�����n
///char�̃r�b�g��
	const int _CHAR_BIT = 8;

///signed char�̍ő�ƍŏ��l
	const signed char _SCHAR_MIN = -127;
	const signed char _SCHAR_MAX =	127;

///unsigned char�̍ő�l
	const unsigned char _UCHAR_MAX = 255;

///�f�t�H���g��char�̍ŏ��ƍő�l(�R���p�C���I�v�V������singed��unsigned���؂�ւ���ꂽ�Ƃ��Ɂj
	const char _CHAR_MIN = _SCHAR_MIN;
	const char _CHAR_MAX = _SCHAR_MAX;

///signed int�̍ő�ƍŏ��l
	const int _INT_MIN =-2147483647;
	const int _INT_MAX = 2147483647;

///unsigned int�̍ő�l
	const unsigned int _UINT_MAX= 4294967295U;

///signed long�̍ő�ƍŏ��l
	const long _LONG_MIN	= -2147483647;
	const long _LONG_MAX	= 2147483647;
///unsigned long�̍ő�l
	const unsigned long _ULONG_MAX= 4294967295U;


//���������_�^
//�؂�グ�E�؂�̂āE�l�̌ܓ��̊ۂߒP�ʁB���̐��̔{���ň�ԋ߂�int�Ɋۂ߂���B
	const int _FLOAT_ROUNDS		= 1;
//�s�������_�^�̓����\���Ɏg�p����Ă����Bfloat f=FLOAT_RADIX^n�ƌ����`�œ����ł͋L������Ă���B
	const int _FLOAT_RADIX		= 2;

	const int _FLOAT_MANT_DIG	= 24;
	const int _DOUBLE_MANT_DIG	= 53;
	const int _LDOUBLE_MANT_DIG = 53;
	
	const int _FLOAT_DIG	= 6;
	const int _DOUBLE_DIG	= 15;
	const int _LDOUBLE_DIG	= 15;
//}//

	const float _FLOAT_EPSILON	= 1.192092896e-07F;
	const float _DOUBLE_EPSILON	= 2.2204460492503131e-016;
	const float _LDOUBLE_EPSILON= 2.2204460492503131e-016;

	const int _FLOAT_MIN_EXP	= -125;
	const int _DOUBLE_MIN_EXP	= -1021;
	const int _LDOUBLE_MIN_EXP	= -1021;

	const int _FLOAT_MAX_EXP	= 128;
	const int _DOUBLE_MAX_EXP	= 1024;
	const int _LDOUBLE_MAX_EXP	= 1024;

	const int _FLOAT_MIN_10_EXP		= -37;
	const int _DOUBLE_MIN_10_EXP	= -307;
	const int _LDOUBLE_MIN_10_EXP	= -307;

	const int _FLOAT_MAX_10_EXP		= 38;
	const int _DOUBLE_MAX_10_EXP	= 308;
	const int _LDOUBLE_MAX_10_EXP	= 308;

	const float _FLOAT_MIN			= 1.175494351e-38F;
	const double _DOUBLE_MIN		= 2.2250738585072014e-308;
	const long double _LDOUBLE_MIN	= 2.2250738585072014e-308;

	const float _FLOAT_MAX			= 3.402823466e+38F;
	const double _DOUBLE_MAX		= 1.7976931348623158e+308;
	const long double _LDOUBLE_MAX	= 1.7976931348623158e+308;

}	//namespace monapi2

#endif

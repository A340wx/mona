/**
	@file	Color.h
	@brief	�F������

	�F������

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_MULTIMEDIA_COLOR_H
#define _MONAPI2_MULTIMEDIA_COLOR_H

#include "../Basic/Switch.h"
#include "../Basic/Type.h"

namespace monapi2	{

typedef dword colort;
const colort COLOR_OPAQUE = 0xFF000000;			///<�^����

inline byte getRValue(colort color)	{return (byte)((color & 0x00FF0000) >> 16);}
inline byte getGValue(colort color)	{return (byte)((color & 0x0000FF00) >> 8);}
inline byte getBValue(colort color)	{return (byte)((color & 0x000000FF));}
inline colort makeColor(byte r,byte g,byte b)	{return ((r<<16) + (g<<8) + (b));}


/**
�F�l�𑀍삷��N���X

	@date	2005/08/20	junjunn �쐬
*/
class Color
{
//���\�b�h
public:
///@name �R���X�g���N�^
//@{
	Color()						{clear();}			///<�R���X�g���N�^
	Color(byte r,byte g,byte b)	{set(r,g,b);}		///<�R���X�g���N�^
	Color(colort color)			{set(color);}		///<�R���X�g���N�^
//@}

///@name �擾
//@{
	byte getR() const {return (byte)r;}
	byte getG() const {return (byte)g;}
	byte getB() const {return (byte)b;}
	colort getColort() const;		///<return RGB(r,g,b);
//@}

///@name ���Z
//@{
	void set(byte r,byte g,byte b);			///<�Z�b�g
	void set(colort color);					///<�Z�b�g
	void scale(float f);					///<�X�P�[�����O
	void scale(float f1,float f2,float f3);	///<�X�P�[�����O
	void add(byte r,byte g,byte b);			///<����
	void add(colort color);					///<����
	void subtract(byte r,byte g,byte b);	///<����
	void subtract(colort color);			///<����
	void clear()	{set(0,0,0);}			///<�N���A
	void normalize();						///<Scale��Add�̌�ɐ�����0�`0xFF�͈̔͂Ƀg���~���O����
//@}


///�����o
public:
	int r;		///<�ԁB�{����BYTE�������Z���Ă���r���ɃI�[�o�[�t���[���o�Ȃ��悤��int�ɂ���
	int g;		///<��
	int b;		///<��
};

}		// namespace monapi2

#endif

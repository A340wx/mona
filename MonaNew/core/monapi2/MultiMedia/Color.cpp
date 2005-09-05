/**
	@file	Color.cpp
	@brief	�F������

	�F������

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Color.h"
#include "../Basic/Math.h"

namespace monapi2	{

//Color/////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::scale(float f)
{
	scale(f,f,f);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::scale(float f1,float f2,float f3)
{
	r = (int)(f1 * r);
	g = (int)(f2 * g);
	b = (int)(f3 * b);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::add(byte _r,byte _g,byte _b)
{
	r += _r;
	g += _g;
	b += _b;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::add(colort color)
{
	add(getRValue(color),getGValue(color),getBValue(color));
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::subtract(byte _r,byte _g,byte _b)
{
	r -= _r;
	g -= _g;
	b -= _b;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::subtract(colort color)
{
	subtract(getRValue(color),getGValue(color),getBValue(color));
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::set(byte _r,byte _g,byte _b)
{
	r = _r;
	g = _g;
	b = _b;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::set(colort color)
{
	r = getRValue(color);
	g = getGValue(color);
	b = getBValue(color);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Color::normalize()
{
	putBetween(&r,0,0xFF);
	putBetween(&g,0,0xFF);
	putBetween(&b,0,0xFF);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
colort Color::getColort() const
{
	return makeColor((byte)r,(byte)g,(byte)b);
}

}	//namespace monapi2

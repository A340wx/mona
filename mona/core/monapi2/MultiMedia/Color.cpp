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
void Color::add(int _r,int _g,int _b)
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
void Color::subtract(int _r,int _g,int _b)
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
void Color::set(uint8_t _r,uint8_t _g,uint8_t _b)
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
	@date	2005/09/29	junjunn �쐬
*/
void Color::set(color16t color16)
{
	r = getRValue(color16);
	g = getGValue(color16);
	b = getBValue(color16);
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
	return makeColor((uint8_t)r,(uint8_t)g,(uint8_t)b);
}

colort monapi2::scaleColor(colort color,float fScale,bool bNormalize)
{
	if (fScale==1)	return color;

	Color oColor(color);
	oColor.scale(fScale);
	if (bNormalize)		oColor.normalize();
	return oColor.getColort();
}

}	//namespace monapi2

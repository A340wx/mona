/**
	@file	Point.cpp
	@brief	(x,y)�̓񎟌����W

	(x,y)�̓񎟌����W

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Point.h"
#include "Size.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Point::add(const class Size* cpSize) const
{
	Point point(x+cpSize->m_iWidth,y+cpSize->m_iHeight);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Point::operator +(const Size& crefSize) const
{
	Point point(x+crefSize.m_iWidth,y+crefSize.m_iHeight);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Point::subtract(const class Size* cpSize) const
{
	Point point(x-cpSize->m_iWidth,y-cpSize->m_iHeight);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Point::operator -(const Size& crefSize) const
{
	Point point(x-crefSize.m_iWidth,y-crefSize.m_iHeight);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::move(const class Size* cpSize)
{
	move(cpSize->getWidth(),cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::operator +=(const Size& crefSize)
{
	move(&crefSize);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::moveMinus(const class Size* cpSize)
{
	move(-cpSize->getWidth(),-cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::operator -=(const class Size& crefSize)
{
	moveMinus(&crefSize);
}


}		//namespace monapi2

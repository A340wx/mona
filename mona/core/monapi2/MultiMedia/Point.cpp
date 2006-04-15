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
Point Point::add(const Size* cpSize) const
{
	Point point(x+cpSize->m_iWidth,y+cpSize->m_iHeight);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Point::add(const Point* cpPoint) const
{
	Point point(x+cpPoint->getX(),y+cpPoint->getY());
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
Point Point::subtract(const Size* cpSize) const
{
	Point point(x-cpSize->m_iWidth,y-cpSize->m_iHeight);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/09/20	junjunn �쐬
*/
Size Point::subtract(const Point* cpPoint) const
{
	Size size(x-cpPoint->x,y-cpPoint->y);
	return size;
}

Size Point::operator -(const Point& crefPoint)const
{
	return subtract(&crefPoint);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::move(const Size* cpSize)
{
	move(cpSize->getWidth(),cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::move(const Point* cpPoint)
{
	move(cpPoint->getX(),cpPoint->getY());
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
void Point::moveMinus(const Size* cpSize)
{
	move(-cpSize->getWidth(),-cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Point::operator -=(const Size& crefSize)
{
	moveMinus(&crefSize);
}


}		//namespace monapi2

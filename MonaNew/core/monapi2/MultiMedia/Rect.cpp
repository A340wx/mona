/**
	@file	Rect.cpp
	@brief	�񎟏�ł̎l�p�`

	�񎟏�ł̎l�p�`

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "../Basic/Math.h"
#include "Rect.h"
#include "Size.h"
#include "Point.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Size Rect::getSize() const
{
	Size size(getWidth(),getHeight());
	return size;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Rect::getLeftTopPoint() const
{
	Point point(getLeft(),getTop());
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Rect::getRightBottomPoint() const
{
	Point point(getRight(),getBottom());
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Point Rect::getCenterPoint() const
{
	Point point((getLeft()+getRight())/2,(getTop()+getBottom())/2);
	return point;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool Rect::isEqual(const class Point* cpPointLeftTop,const class Size* cpSize) const
{
	return isEqual(cpPointLeftTop->getX(),cpPointLeftTop->getY(),cpPointLeftTop->getX()+cpSize->getWidth(),cpPointLeftTop->getY()+cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool Rect::isEqual(const Point* cpPointLeftTop,const Point* cpPointRightBottom) const
{
	return isEqual(cpPointLeftTop->getX(),cpPointLeftTop->getY(),cpPointRightBottom->getX(),cpPointRightBottom->getY());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool Rect::isPointInside(int x,int y) const
{
	return (getLeft()<=x && x<getRight() && getTop()<=y && y<getBottom());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool Rect::isPointInside(const Point* cppoint) const
{
	return isPointInside(cppoint->getX(),cppoint->getY());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Rect::moveBy(const Size* cpSize)
{
	moveBy(cpSize->getWidth(),cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/09/20	junjunn �쐬
*/
void Rect::moveBy(const Point* cpPoint)
{
	moveBy(cpPoint->getX(),cpPoint->getY());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/09/20	junjunn �쐬
*/
void Rect::moveTo(const Point* cpPoint)
{
	moveTo(cpPoint->getX(),cpPoint->getY());
}


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Rect::normalize()
{
	if (m_iLeft>m_iRight) swap(&m_iLeft,&m_iRight);
	if (m_iTop>m_iBottom) swap(&m_iTop,&m_iBottom);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Rect::set(const Point* cpPointLeftTop,const Size* cpSize)
{
	set(cpPointLeftTop->getX(),cpPointLeftTop->getY(),cpSize->getWidth(),cpSize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Rect::set(const Point* cpPointLeftTop,const Point* cpPointRightBottom)
{
	set(cpPointLeftTop->getX(),cpPointLeftTop->getY(),
		cpPointRightBottom->getX()-cpPointLeftTop->getX(),cpPointRightBottom->getY()-cpPointLeftTop->getY());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Rect::inflate(const Size* cpsize)
{
	inflate(cpsize->getWidth(),cpsize->getHeight());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Rect Rect::getIntersect(const Rect* cprect1,const Rect* cprect2)
{
	Rect rectReturn;
	const Rect* cprectS,*cprectL;	//small��large

//X��
	if (cprect1->getLeft() <= cprect2->getLeft())
	{
		cprectS	= cprect1;
		cprectL	= cprect2;
	}
	else
	{
		cprectS	= cprect2;
		cprectL	= cprect1;
	}

//�����Ȃ��̂�0��Ԃ��B
	if (cprectL->getLeft() >= cprectS->getRight())	return Rect(0,0,0,0);

	rectReturn.m_iLeft = cprectL->getLeft();
	rectReturn.m_iRight = getMin(cprectS->getRight(),cprectL->getRight());

//Y��
	if (cprect1->getTop() <= cprect2->getTop())
	{
		cprectS	= cprect1;
		cprectL	= cprect2;
	}
	else
	{
		cprectS	= cprect2;
		cprectL	= cprect1;
	}

//�����Ȃ��̂�0��Ԃ��B
	if (cprectL->getTop() >= cprectS->getBottom())	return Rect(0,0,0,0);

	rectReturn.m_iTop = cprectL->getTop();
	rectReturn.m_iBottom = getMin(cprectS->getBottom(),cprectL->getBottom());

	return rectReturn;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Rect Rect::getMinimumInclude(const Rect* cprect1,const Rect* cprect2)
{
	Rect rectReturn;

	rectReturn.m_iLeft	= getMin(cprect1->getLeft(),cprect2->getLeft());
	rectReturn.m_iRight = getMax(cprect1->getRight(),cprect2->getRight());
	rectReturn.m_iTop	= getMin(cprect1->getTop(),cprect2->getTop());
	rectReturn.m_iBottom= getMax(cprect1->getBottom(),cprect2->getBottom());

	return rectReturn;
}


}		//namespace monapi2

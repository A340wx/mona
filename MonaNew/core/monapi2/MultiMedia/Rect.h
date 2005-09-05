/**
	@file	Rect.h
	@brief	�񎟏�ł̎l�p�`

	�񎟏�ł̎l�p�`

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_MULTIMEDIA_RECT_H
#define _MONAPI2_MULTIMEDIA_RECT_H

#include "../Basic/Switch.h"
#include "../Basic/Type.h"

namespace monapi2	{

/**
	@brief	�񎟌���ł̎l�p�`�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class Rect
{
public:
	Rect()											{set(0,0,0,0);}
	Rect(int iLeft,int iTop,int iRight,int iBottom)	{set(iLeft,iTop,iRight,iBottom);}
	Rect(const class Point* cpPointLeftTop,const class Size* cpSize)	{set(cpPointLeftTop,cpSize);}
	Rect(const Point* cpPointLeftTop,const Point* cpPointRightBottom)	{set(cpPointLeftTop,cpPointRightBottom);}
	Rect(const Rect* cpRect)						{set(cpRect);}
	~Rect()											{}	//�Ӗ��Ȃ����ǒ�`���Ă����������R���p�C���ɕ��匾���Ȃ��̂ŁB

//�擾
	int getLeft() const								{return m_iLeft;}
	int getTop() const								{return m_iTop;}
	int getBottom() const							{return m_iBottom;}
	int getRight() const							{return m_iRight;}
	int getWidth() const							{return m_iRight-m_iLeft;}
	int getHeight() const							{return m_iBottom-m_iTop;}
	Size getSize() const;
	int getArea() const								{return getWidth()*getHeight();}
	Point getLeftTopPoint() const;
	Point getRightBottomPoint() const;
	Point getCenterPoint() const;
	bool isEmpty() const							{return (getWidth()==0 || getHeight()==0);}
	bool isNormal() const							{return (m_iLeft<=m_iRight && m_iTop<=m_iBottom);}
	bool isEqual(int iLeft,int iTop,int iRight,int iBottom)	const {return (m_iLeft==iLeft && m_iTop==iTop && m_iRight==iRight && m_iBottom==iBottom);}
	bool isEqual(const class Point* cpPointLeftTop,const class Size* cpSize) const;
	bool isEqual(const Point* cpPointLeftTop,const Point* cpPointRightBottom) const;
	bool isEqual(const Rect* cpRect) const		{return isEqual(cpRect->m_iLeft,cpRect->m_iTop,cpRect->m_iRight,cpRect->m_iBottom);}
	bool operator ==(const Rect& crefRect) const	{return isEqual(&crefRect);}
	bool operator !=(const Rect& crefRect) const 	{return ! isEqual(&crefRect);}

	bool isPointInside(int x,int y) const;
	bool isPointInside(const Point* cppoint) const;
	static Rect getIntersect(const Rect* cprect1,const Rect* cprect2);
	static Rect getMinimumInclude(const Rect* cprect1,const Rect* cprect2);

//���� 
	void set(int iLeft,int iTop,int iRight,int iBottom)	{m_iLeft=iLeft;m_iTop=iTop;m_iRight=iRight;m_iBottom=iBottom;}
	void set(const class Point* cpPointLeftTop,const class Size* cpSize);
	void set(const Point* cpPointLeftTop,const Point* cpPointRightBottom);
	void set(const Rect* cpRect)				{set(cpRect->m_iLeft,cpRect->m_iTop,cpRect->m_iRight,cpRect->m_iBottom);}
	void operator =(const Rect& crefRect)		{set(&crefRect);}

	void inflate(int xInflate,int yInflate)		{m_iLeft-=xInflate;m_iRight+=xInflate;m_iTop-=yInflate;m_iBottom+=yInflate;}
	void inflate(const Size* cpsize);
	void inflate(int iLeft,int iTop,int iRight,int iBottom)	{m_iTop-=iTop;m_iBottom+=iBottom;m_iLeft-=iLeft;m_iRight+=iRight;}
	void inflate(const Rect* cprect)				{inflate(cprect->m_iLeft,cprect->m_iTop,cprect->m_iRight,cprect->m_iBottom);}

	void move(int x,int y)						{m_iLeft+=x;m_iTop+=y;m_iRight+=x;m_iBottom+=y;}
	void move(const class Size* cpSize);
	void normalize();

public:
	int m_iLeft;
	int m_iTop;
	int m_iRight;
	int m_iBottom;
};

	
}	//namespace monapi2

#endif

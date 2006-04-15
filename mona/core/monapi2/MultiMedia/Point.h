/**
	@file	Point.h
	@brief	(x,y)�̓񎟌����W

	(x,y)�̓񎟌����W

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_MULTIMEDIA_POINT_H
#define _MONAPI2_MULTIMEDIA_POINT_H

#include "../Basic/Switch.h"
#include "../Basic/Type.h"

namespace monapi2	{

/**
	@brief	(x,y)�̓񎟌����W�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class Point
{
public:
	Point()											{set(0,0);}
	Point(int _x,int _y)							{set(_x,_y);}
	Point(const Point* cpPoint)						{set(cpPoint);}

//�擾
	int getX()								const	{return x;}
	int getY()								const	{return y;}
	bool isEqual(int _x,int _y)				const	{return (x==_x && y==_y);}
	bool isEqual(const Point* cpPoint)		const	{return isEqual(cpPoint->x,cpPoint->y);}
	bool operator ==(const Point& crefPoint)const	{return isEqual(&crefPoint);}
	bool operator !=(const Point& crefPoint)const 	{return ! isEqual(&crefPoint);}
	Point add(int _x,int _y)				const	{Point point(x+_x,y+_y);return point;}
	Point add(const class Size* cpSize)		const;
	Point add(const Point* cpPoint)	const;
	Point operator +(const Size& crefSize)	const;
	Point subtract(int _x,int _y)			const	{Point point(x-_x,y-_y);return point;}
	Point subtract(const Size* cpSize)		const;
	Size  subtract(const Point* cpPoint)	const;
	Point operator -(const Size& crefSize)	const	{return subtract(&crefSize);}
	Size  operator -(const Point& crefPoint)const;
	Point subtractRelative(const Point* cppointBase)const {return this->subtract(cppointBase->x,cppointBase->y);}
	Point addRelative(const Point* cppointBase)		const {return this->add(cppointBase->x,cppointBase->y);}

//���� 
	void set(int _x,int _y)						{x=_x;y=_y;}
	void set(const Point* cpPoint)				{set(cpPoint->x,cpPoint->y);}
	void operator =(const Point& crefPoint)		{set(&crefPoint);}
	void move(int _x,int _y)					{x+=_x;y+=_y;}
	void move(const Size* cpSize);
	void move(const Point* cpPoint);
	void operator +=(const Size& crefSize);
	void moveMinus(int _x,int _y)				{move(-_x,-_y);}
	void moveMinus(const Size* cpSize);
	void operator -=(const Size& crefSize);

//set�Ɠ����B�����@�\�Ŗ��O���Ⴄ�A���C�A�X�֐������͖̂{���͂悭�Ȃ��񂾂�Point���p������
//�N���X������Ă�������Point�̋@�\�𗘗p�������Ƃ���set()���Ɖ����Z�b�g���Ă邩
//�Ӗ����킩��Ȃ��Ȃ�̂�Point��set���Ă���񂾂Ɩ��m�ɂ��������ɂ͂��������g���ƕ֗����ƁB
	void setPoint(int _x,int _y)				{set(_x,_y);}
	void setPoint(const Point* cpPoint)			{set(cpPoint);}

public:
	int x;
	int y;
};

	
}	//namespace monapi2

#endif

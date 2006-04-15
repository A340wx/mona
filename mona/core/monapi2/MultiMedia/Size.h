/**
	@file	Size.h
	@brief	���ƍ����̓񎟌��T�C�Y

	���ƍ����̓񎟌��T�C�Y

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_MULTIMEDIA_SIZE_H
#define _MONAPI2_MULTIMEDIA_SIZE_H

#include "../Basic/Switch.h"
#include "../Basic/Type.h"

namespace monapi2	{

/**
	@brief	���ƍ����̓񎟌��T�C�Y�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class Size
{
public:
	Size()											{set(0,0);}
	Size(int iWidth,int iHeight)					{set(iWidth,iHeight);}
	Size(const Size* cpSize)						{set(cpSize);}

//�擾
	int getWidth() const							{return m_iWidth;}
	int getHeight() const							{return m_iHeight;}
	bool isEqual(int iWidth,int iHeight) const		{return (m_iWidth==iWidth && m_iHeight==iHeight);}
	bool isEqual(const Size* cpSize) const			{return isEqual(cpSize->m_iWidth,cpSize->m_iHeight);}
	bool operator ==(const Size& crefSize) const	{return isEqual(crefSize.m_iWidth,crefSize.m_iHeight);}
	bool operator !=(const Size& crefSize) const 	{return ! isEqual(&crefSize);}
	Size add(int iWidth,int iHeight) const			{Size Size(m_iWidth+iWidth,m_iHeight+iHeight);return Size;}
	Size add(const class Size* cpSize) const		{Size Size(m_iWidth+cpSize->m_iWidth,m_iHeight+cpSize->m_iHeight);return Size;}
	Size operator +(const Size& crefSize) const		{Size Size(m_iWidth+crefSize.m_iWidth,m_iHeight+crefSize.m_iHeight);return Size;}
	Size subtract(int iWidth,int iHeight) const		{Size Size(m_iWidth-iWidth,m_iHeight-iHeight);return Size;}
	Size subtract(const class Size* cpSize) const	{Size Size(m_iWidth-cpSize->m_iWidth,m_iHeight-cpSize->m_iHeight);return Size;}
	Size operator -(const Size& crefSize) const		{Size Size(m_iWidth-crefSize.m_iWidth,m_iHeight-crefSize.m_iHeight);return Size;}

//���� 
	void set(int iWidth,int iHeight)				{m_iWidth=iWidth;m_iHeight=iHeight;}
	void set(const Size* cpSize)					{set(cpSize->m_iWidth,cpSize->m_iHeight);}
	void operator =(const Size& crefSize)			{set(crefSize.m_iWidth,crefSize.m_iHeight);}
	void addSelf(int iWidth,int iHeight)			{m_iWidth+=iWidth;m_iHeight+=iHeight;}
	void addSelf(const class Size* cpSize)			{addSelf(cpSize->getWidth(),cpSize->getHeight());}
	void operator +=(const Size& crefSize)			{addSelf(&crefSize);}
	void subtractSelf(int iWidth,int iHeight)		{addSelf(-iWidth,-iHeight);}
	void subtractSelf(const class Size* cpSize)		{addSelf(-cpSize->getWidth(),-cpSize->getHeight());}
	void operator -=(const class Size& crefSize)	{subtractSelf(&crefSize);}

//set�̃A���C�A�X�B�\�[�X����Size��set���Ă�ƈӖ����n�b�L�������������Ɏg���Ƃ킩��₷�����͂��������g���B
	void setSize(int iWidth,int iHeight)			{set(iWidth,iHeight);}
	void setSize(const Size* cpSize)				{set(cpSize);}

public:
	int m_iWidth;
	int m_iHeight;
};

	
}	//namespace monapi2

#endif

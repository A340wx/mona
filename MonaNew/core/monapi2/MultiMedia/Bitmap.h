/**
	@file	Bitmap.h
	@brief	�r�b�g�}�b�v�̎�舵���E����B
	
	�r�b�g�}�b�v�̎�舵���E����B

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_MULTIMEDIA_BITMAP_H
#define _MONAPI2_MULTIMEDIA_BITMAP_H

#include "../Basic/Switch.h"
#include "../Basic/Type.h"
#include "../Basic/Buffer.h"
#include "../Basic/String.h"
#include "Size.h"
#include "Color.h"

namespace monapi2	{

/**
�r�b�g�}�b�v���������߂̃N���X�B24�r�b�g����B.
�t�@�C���Ȃǂ���̓ǂݏ����ƃs�N�Z���P�ʂł̐F���삪�\�B

	@date	2005/08/20	junjunn �쐬

@bug Y���]�̏ꍇ��getPixel(x,y)�����Ȃǂ����Ή��E�E�E
*/
class Bitmap
{
//���\�b�h
public:
///@name ����
//@{
	Bitmap()				{init();}				///<��̓��e�ō쐬
	Bitmap(cpchar1 cszPath,bool bReverseY=false)	{init();read(cszPath,bReverseY);}	///<cszPath�̃t�@�C���ō쐬
	Bitmap(int iWidth,int iHeight)	{createCanvas(iWidth,iHeight);}	///<�傫�����w�肵�č쐬�B
//@}

///@name �擾
//@{
	int getWidth()	const {return m_oSize.getWidth();}				///<��
	int getHeight()	const {return m_oSize.getHeight();}				///<����
	int getLineDataSize() const {return m_iLineSize;}				///<��s�̃f�[�^��
	const Size* getSize() const {return &m_oSize;}
//@}

///@name �r�b�g�}�b�v����
//@{
	byte* createCanvas(int iWidth,int iHeight);		///<�o�b�t�@�ɃT�C�Y�����܂邾���̗e�ʂ��m�ہB
	byte* createCanvas(const class Size* cpSize);	///<�o�b�t�@�ɃT�C�Y�����܂邾���̗e�ʂ��m�ہB
	void copy(const Bitmap* cpBitmap);				///<cpBitmap���R�s�[
	void clear();									///<���݂̓��e����������
//@}

///@name �s�N�Z������
//@{
	byte* getPixelBuffer();										///<�f�[�^�o�b�t�@�̎n�_�̈ʒu��Ԃ��B
	byte* getPixelBuffer(int x,int y);							///<(x,y)�̃s�N�Z���̃f�[�^�o�b�t�@�̈ʒu��Ԃ��B
	const byte* getPixelBufferConst() const;					///<�f�[�^�o�b�t�@�̎n�_�̈ʒu��Ԃ��Bconst�ŁB
	const byte* getPixelBufferConst(int x,int y) const;			///<(x,y)�̃s�N�Z���̃f�[�^�ʒu��Ԃ��Bconst�ŁB
	colort getPixel(int x,int y) const;							///<(x,y)�̃s�N�Z���̐F�ʒu��Ԃ�
//	class Color* getPixel(int x,int y,Color* pColorMan) const;	///<(x,y)�̈ʒu�ɂ���F�f�[�^���擾
//	void setPixel(int x,int y,const Color* pColorMan);			///<(x,y)�̈ʒu�ɐF�f�[�^���Z�b�g�B24�r�b�g�p�B
	void setPixel(int x,int y,colort rgb);						///<(x,y)�̈ʒu�ɐF�f�[�^���Z�b�g�Bcolort�����B
//@}

///@name �y�C���g����
//@{
	void fill(colort color);
//@}

///@name �t�@�C������
//@{
	bool read(cpchar1 szPath,bool bReverseY=false);		///<szPath�̃t�@�C���ō쐬
	void write(cpchar1 cszPath)	const;				///<.bmp���f�B�X�N�ɏ����o��
//@}




protected:
	void init();									///<������
	byte* getNewBuffer(int iWidth,int iHeight);		///<�����̃T�C�Y�̃o�b�t�@���m��
	void setLineBits();								///<m_iLineSize���Z�b�g
	bool isValid()const	{return	(m_oSize.getWidth()!=0);}		///<�������o�b�t�@�����݂��Ă��邩


//�����o
public:
	Size	m_oSize;
	int		m_iLineSize;	///<1�s�̃f�[�^�T�C�Y�BBMP�̕���4�̔{���łȂ���΂Ȃ�Ȃ������̂���m_iWidth��4�̔{������Ȃ��������Ɏ��ۂ̃o�C�g���Ƃ͐H���Ⴄ�B
	Buffer	m_bufferData;	///<�f�[�^�{��

	bool	m_bYReverse;	///<Y���]�����Ă��邩�B

//junjunn 2005/09/22�BBitmap�����L��������ɍ��Ƃ����ňꏏ�ɍ����String��
//�Q�ƃJ�E���g�V�X�e���̊֌W�Ń��������j�]���鎖�ɋC�Â����̂ň�[��~�E�E�E
//	String	m_strPath;		///<�����̃p�X�B
};




//�֐�////////

/**
BMP�̈�s�̃o�C�g����Ԃ��BBMP��4�o�C�g���ɂ��K�v�B

	@date	2005/08/20	junjunn �쐬
*/
int getBMPLineSize(int iWidth);

}		// namespace monapi2

#endif

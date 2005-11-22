/**
	@file	Bitmap.cpp
	@brief		�r�b�g�}�b�v�̎�舵���E����B

	�r�b�g�}�b�v�̎�舵���E����B

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Bitmap.h"
#include "../Basic/File.h"
#include "../Basic/Debug.h"
#include "../Basic/Memory.h"

namespace monapi2	{

#define ASSERT_PIXEL(x,y)	ASSERT(x>=0 && x<m_iWidth && y>=0 && y<m_iHeight);

	
	

//.bmp�t�@�C���̋K�i�B�Â��K�i�̂��ߍ�����g���ĂȂ������o��S�����ɗ����Ȃ������o������
//�����ł͂�����.bmp�`���ɓK���͂��Ȃ��B�g��Ȃ������o�͑S����������B
//�ߋ��݊��ׂ̈̃t�@�C�����o�͂Ɏg�������B

/**
�r�b�g�}�b�v�ɂ��Ă̏��B

	@date	2005/08/20	junjunn �쐬
*/
class BitmapInfoHeader
{
public:
	void set(const byte* p)
	{
		m_iWidth	=*(dword*)(p+0x04);
		m_iHeight	=*(dword*)(p+0x08);
		m_wBitFormat=*(word*) (p+0x0E);
	}


public:
//	dword	m_dwSizeStructure;		///<���̍\���̂̃T�C�Y�B����Ӗ��o�[�W�������Ɏg����B
	int		m_iWidth;				///<���Buint����Ȃ���int�Ȃ̂̓}�C�i�X�l���Ə㉺���]��BMP�𐶐�����Ӗ��Ƃ��l������B
	int		m_iHeight;				///<�����B
//	word	m_wPlanes;				///<�s�g�p�B���1�B
	word	m_wBitFormat;			///<���r�b�g�t�H�[�}�b�g���B1,4,8,16,24,32�Ȃǂ�����B
//	dword	m_dwCompression;		///<���k���@�B���ʂ͕s�g�p�B
//	dword	m_dwSize;				///<�C���[�W�̃T�C�Y�B���k�����Ă���Ƃ��̉𓀌�̑傫���Ɏg�������ʂ͕s�g�p�B
//	long	m_lXPelsPerMeter;		///<�����𑜓x�B���ʂ͕s�g�p�B
//	long	m_lYPelsPerMeter;		///<�����𑜓x�B���ʂ͕s�g�p�B
//	dword	m_dwClrUsed;			///<���ۂɎg���Ă���F���B���ʂ͕s�g�p�B
//	dword	m_dwClrImportant;		///<�d�v�ȐF���B���ʂ͕s�g�p�B
}; 

//�F�w��B������p���b�g�Ɏg���B
/**
	@date	2005/08/20	junjunn �쐬
*/
struct RGBQuad
{
	byte	r; 
	byte	g; 
	byte	b;
	byte	m_byReserved; 
}; 

//�r�b�g�}�b�v���+�p���b�g�f�[�^�B24�r�b�g�Ȃ�p���b�g���Ȃ��̂Ńp���b�g�f�[�^���͖����B
/**
	@date	2005/08/20	junjunn �쐬
*/
struct BitmapInfo
{
	BitmapInfoHeader	m_BitmapInfoHeader;
	RGBQuad*			m_RGBQuad;	//�r�b�g�}�b�v�̐F�r�b�g���ɉ����ĕK�v�ȕ��������I�Ɋm�ۂ���B
};

//�r�b�g�}�b�v�t�@�C���w�b�_�[�B
/**
	@date	2005/08/20	junjunn �쐬
*/
struct BitmapFileHeader
{
public:
	void set(const byte* p)	
	{
		m_dwSize		=*(dword*)(p+0x02);
		m_dwOffsetToData=*(dword*)(p+0x0A);
	}
	int getDataSize()	{return m_dwSize-m_dwOffsetToData;};		//�f�[�^�{�̂̑傫���B

public:
//	word	m_wType;			///<�t�@�C���^�C�v���ʁB���"BM"�B
	dword	m_dwSize;			///<�t�@�C���̑傫���B
//	word	m_wReserved1;		///<�s�g�p�B
//	word	m_wReserved2;		///<�s�g�p�B
	dword	m_dwOffsetToData;	///<�t�@�C���擪����f�[�^�{�̂܂ł̃r�b�g���B
}; 


//Bitmap/////////////////
/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::init()
{
	m_iWidth	= 0;
	m_iHeight	= 0;

	m_strPath.empty();
	m_bufferData.clear();

	m_strPath = "Bitmap.bmp";
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::clear()
{
	init();
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
byte* Bitmap::getCanvas(int iWidth,int iHeight)
{
	return getNewBuffer(iWidth,iHeight);
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
byte* Bitmap::getNewBuffer(int iWidth,int iHeight)
{
	clear();

	m_iWidth	= iWidth;
	m_iHeight	= iHeight;
	setLineBits();

	return m_bufferData.extendBuffer(m_iLineSize * iHeight);
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::setLineBits()
{
	m_iLineSize = getBMPLineSize(m_iWidth);
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::copy(const Bitmap* cpBitmap)
{
	if (! cpBitmap->isValid())	return;

	clear();

	m_iWidth	= cpBitmap->m_iWidth;
	m_iHeight	= cpBitmap->m_iHeight;
	m_bufferData.copy(&cpBitmap->m_bufferData);
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
byte* Bitmap::getPixelBuffer(int x,int y)
{
//�擪��\�������B
	if (x<0)	return m_bufferData.getBuffer();

	int iOffset = (m_iHeight - y - 1)*m_iLineSize + x*3;
	return m_bufferData.getBuffer() + iOffset;
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
colort Bitmap::getPixel(int x,int y)
{
	const byte* cpBaseByte = getPixelBufferConst(x,y);
	return makeColor(cpBaseByte[0],cpBaseByte[1],cpBaseByte[2]);
}


/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::setPixel(int x,int y,colort color)
{
	ASSERT_PIXEL(x,y);

	byte* pBaseByte = getPixelBuffer(x,y);

	pBaseByte[0] = getBValue(color);
	pBaseByte[1] = getGValue(color);
	pBaseByte[2] = getRValue(color);
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::fill(colort color)
{
	byte* p = getPixelBuffer(-1,0);
//dword�]���ł͍Ō�̈�����̓o�b�t�@�̊O�ɏo�Ă��܂��̂ŁB
	for (int i=0;i<(m_iWidth*m_iHeight)-1;i++)
	{
		*(dword*)p = color;
		p+=3;
	}

	setPixel(m_iWidth-1,m_iHeight-1,color);
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool Bitmap::read(cpchar1 cszPath)
{
	File file;
	if (! file.open(cszPath))		return false;

//BMP�t�@�C���w�b�_�̓ǂݍ���
	int iRead=0;
	BitmapFileHeader bitmapFileHeader;
	BitmapInfoHeader bitmapInfoHeader;

	byte abyBuffer[100];
	iRead+=file.read(abyBuffer,iRead,14);
	bitmapFileHeader.set(abyBuffer);

	iRead+=file.read(abyBuffer,iRead,40);
	bitmapInfoHeader.set(abyBuffer);

//�����_�ł�24�r�b�g�ȊO�͑Ή����ĂȂ��B
	if (bitmapInfoHeader.m_wBitFormat != 24)		return false;
	ASSERT(m_iWidth>0 && m_iHeight>0);


//�������B�ݒ�B
	m_strPath = cszPath;
	byte* pBuffer = getCanvas(bitmapInfoHeader.m_iWidth,bitmapInfoHeader.m_iHeight);

	file.read(pBuffer,bitmapFileHeader.m_dwOffsetToData,m_bufferData.getSize());

	return true;
}

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Bitmap::write(cpchar1 cszPath) const
{
	ASSERT(m_iBitCount==8 || m_iBitCount==24);

const int iBMP_HEADER_SIZE = 0x36;

//54�o�C�g
	byte abyHeader[] = {
0x42,0x4D,				//00:�t�@�C���̎���ID
0x36,0x10,0x0E,0x00,	//02:�T�C�Y�B��B640*480*24 = E10000�B����Ƀw�b�_�[�������� 
0x00,0x00,				//06:�Œ�B0��
0x00,0x00,				//08:�Œ�B0��
0x36,0x00,0x00,0x00,	//0A:�摜�f�[�^�{�̂ւ̃I�t�Z�b�g

0x28,0x00,0x00,0x00,	//0E:�Œ�B�w�b�_�[�T�C�Y
0x80,0x02,0x00,0x00,	//12:m_nWidth.			��
0xE0,0x01,0x00,0x00,	//16:biHeight.			����
0x01,0x00,				//1A:biPlanes.			�Œ�B�J���[�v���[��
0x18,0x00,				//1C:m_wBitFormat.		�J���[�r�b�g
0x00,0x00,0x00,0x00,	//1E:biCompression.		�Œ�B���k�X�L�[��(0=�Ȃ��j
0x00,0x10,0x0E,0x00,	//22:biSizeImage.		�摜�̃T�C�Y�i���k���̂݁j
0x13,0x0B,0x00,0x00,	//26:biXPelsPerMeter.	�Œ�B�����𑜓x
0x13,0x0B,0x00,0x00,	//2A:biYPelsPerMeter.	�Œ�B�����𑜓x
0x00,0x00,0x00,0x00,	//2E:biClrUsed.			�Œ�B�F��
0x00,0x00,0x00,0x00};	//32:biClrImportant.	�Œ�B�K�v�ȐF���i���݂͎g�p����ĂȂ�)


	int* piSize		= (int*) (abyHeader + 2);
	int* piMainDataOffset = (int*) (abyHeader + 10);
	int* piWidth	= (int*) (abyHeader + 18);
	int* piHeight	= (int*) (abyHeader + 22);
	int* piBitCount	= (int*) (abyHeader + 28);

	int iSize=0;
	int iMainDataOffset=0;

	iSize = m_iLineSize * m_iHeight + iBMP_HEADER_SIZE;
	iMainDataOffset = iBMP_HEADER_SIZE;

	*piSize = iSize;
	*piMainDataOffset = iMainDataOffset;
	*piWidth			= m_iWidth;
	*piHeight			= m_iHeight;
	*piBitCount			= 24;

	File file(cszPath,true);
	int iWrite=0;
	iWrite += file.write(abyHeader,iWrite,sizeof(abyHeader));
	iWrite += file.write(m_bufferData.getData(),iWrite,m_bufferData.getSize());
}


//���̑��֐�////////////////
/**
	@date	2005/08/20	junjunn �쐬
*/
int	getBMPLineSize(int iWidth)
{
	int iLineBits = 3 * iWidth;

	int iExcess = iLineBits % 4;
	if (iExcess != 0)
	{
		iLineBits += (4-iExcess);
	}

	return iLineBits;
}


}	// namespace monapi2

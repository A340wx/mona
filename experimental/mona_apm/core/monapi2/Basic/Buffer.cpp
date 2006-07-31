/**
	@file	Buffer.cpp
	@brief	�ėp�o�b�t�@

	�ėp�o�b�t�@

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Buffer.h"
#include "Memory.h"

namespace monapi2	{

//Buffer/////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Buffer::Buffer()						
{
	m_pBuffer	= NULL;
	clear();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Buffer::Buffer(int iInitialSize)
{
	m_pBuffer	=	NULL;
	extendBuffer(iInitialSize);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
Buffer::~Buffer()
{
	clear();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Buffer::clear()
{
	SAFE_DELETE(m_pBuffer);
//	m_iLength	= 0;
	m_iSize		= 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
byte* Buffer::extendBuffer(int iNewSize,bool bKeepOriginalData)
{
//�����i�[�ł���̈悪����Ȃ�Ċm�ۂ͂��Ȃ��Ō��݂̓��e���N���A�B
	if (m_iSize>=iNewSize)
	{
//		m_iLength=0;
		return m_pBuffer;
	}

	byte* pNewBuffer = new byte[iNewSize];
	m_iSize = iNewSize;
//	m_iLength = iNewSize;

	if (bKeepOriginalData)
	{
		MemoryFn::copy(pNewBuffer,m_pBuffer,getSize());
	}
	else
	{
//		m_iLength=0;
	}

	delete m_pBuffer;
	m_pBuffer	= pNewBuffer;

	return m_pBuffer;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Buffer::copy(const byte* cpSource,int iLength)
{
	extendBuffer(iLength);

//	m_iLength	= iLength;
	MemoryFn::copy(m_pBuffer,cpSource,iLength);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Buffer::copy(const Buffer* pbuf)	
{
	copy(pbuf->m_pBuffer,pbuf->getSize());
}


}		//namespace monapi2

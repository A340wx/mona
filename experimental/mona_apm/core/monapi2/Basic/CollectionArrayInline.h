/**
	@file	CollectionArrayInline.h
	@brief	�R���N�V���� ���I�z��

	�R���N�V���� ���I�z��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_COLLECTIONARRAYINLINE_H
#define _MONAPI2_BASIC_COLLECTIONARRAYINLINE_H

#include "Search.h"
#include "Math.h"

namespace monapi2	{

//Array//////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
Array<TYPE>::Array(uint nItitialSize)
{
	init(nItitialSize);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void Array<TYPE>::init(uint nItitialSize)
{
	m_nCount		= 0;
	m_nSize			= nItitialSize;
	m_apData		= NULL;

	getNewSize(nItitialSize);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
Array<TYPE>::~Array()
{
	removeAll();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void Array<TYPE>::deleteOldBuffer(TYPE* pBuffer,uint )	//�����͎��̌p���N���X�Ŏg���B�����ł̓_�~�[�B
{
	delete[] pBuffer;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
TYPE Array<TYPE>::getAt(uint n) const
{
	if (n>=m_nCount)	return 0;

	return m_apData[n];
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void Array<TYPE>::add(TYPE t)
{
	TYPE* pOldBuffer = extendBuffer(m_nCount+1);

//�o�b�t�@�̕ϓ����������B
	if (pOldBuffer)
	{
//�O�̗v�f���ړ��B
		for (uint n=0;n<m_nCount;n++)
		{
			m_apData[n] = pOldBuffer[n];
		}
//�f�[�^�폜�ł͂Ȃ��ړ��Ȃ̂ŃT�C�Y�w���0�ɂ��Ă���B
		deleteOldBuffer(pOldBuffer,0);
	}

	m_apData[m_nCount] = t;
	m_nCount++;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
TYPE* Array<TYPE>::extendBuffer(uint nSize)
{
//�v���ȏ�̗̈�����łɎ����Ă���̂ŉ������Ȃ��ł����B
	if (nSize <= m_nSize)	return NULL;

	uint nNewSize = m_nSize;
	if (nNewSize == 0)	nNewSize =1;

//�傫���͔{�X��
	while (nNewSize < nSize)
		nNewSize*=2;

//�o�b�t�@���m�ہB
	return getNewSize(nNewSize);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
bool Array<TYPE>::setAt(uint nIndex,TYPE tValue)
{
	if (nIndex>=getCount())	return false;

	m_nCount=getMax(m_nCount,nIndex);
	m_apData[nIndex] = tValue;
	return true;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
bool Array<TYPE>::insertAt(uint nIndex,uint nCount)
{
	if (nIndex>=getCount())	return false;

	uint nOldCount = m_nCount;
	m_nCount+=nCount;

//	uint nOldSize = getSize();
//�o�b�t�@�̊g�������݂�B(�\���ɂ������ꍇ�͉����N����Ȃ��B)
	TYPE* pOldBuffer = extendBuffer(m_nCount);

	uint n;
//�o�b�t�@�̕ϓ����������B
	if (pOldBuffer)
	{
//�}���C���f�b�N�X�O�̗v�f�B
		for (n=0;n<nIndex;n++)
		{
			m_apData[n] = pOldBuffer[n];
		}
	}

//�}���C���f�b�N�X��̗v�f���ړ��B
	for (n=nIndex+nCount;n<nOldCount+nCount;n++)
	{
		m_apData[n] = pOldBuffer[n-nCount];
	}

//�}�����ꂽ�ꏊ�͋�ɂ��Ă����B�i�O�̃f�[�^���c���Ă�delete�����ƃ}�Y���B�j
	for (n=nIndex;n<nIndex+nCount;n++)
	{
		m_apData[n] = 0;
	}

	if (pOldBuffer)
	{
//deleteOldBuffer���g����ArrayAD�̏ꍇ�ɒ~���Ă����|�C���^���j�󂳂��̂ł��������������B
		delete[] pOldBuffer;
//		deleteOldBuffer(pOldBuffer,nOldSize);
	}

	return true;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void Array<TYPE>::setSize(uint nSize)
{
	uint nOldCount = getCount();
	TYPE* pOldBuffer = getNewSize(nSize);
	m_nCount=nSize;

//�o�b�t�@�̕ϓ����������B
	if (pOldBuffer)
	{
//�O�̗v�f���ړ��B
		for (uint n=0;n<nOldCount;n++)
		{
			m_apData[n] = pOldBuffer[n];
		}
//�폜�ł͂Ȃ��ړ��Ȃ̂ŃT�C�Y��0�B
		deleteOldBuffer(pOldBuffer,0);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
TYPE* Array<TYPE>::getNewSize(uint nSize)
{
	if (nSize==0)	return NULL;

//�o�b�t�@���m�ہB
	TYPE* apNewData = new TYPE[nSize];
	for (uint n=0;n<nSize;n++)
	{
		apNewData[n]=0;
	}
	m_nSize = nSize;

	TYPE* pOldBuffer = m_apData;
	m_apData = apNewData;
	return pOldBuffer;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void Array<TYPE>::sort(FnCompare pFnCompare)
{
	quicksort(m_apData,m_nCount,sizeof(TYPE),pFnCompare);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
bool Array<TYPE>::removeAt(uint nIndex,uint nCount)
{
	if (nIndex+nCount>=getCount())	return false;

//�C���f�b�N�X��̗v�f���ړ��B
	for (uint n=nIndex+nCount;n<getCount();n++)
	{
		m_apData[n-nCount] = m_apData[n];
	}

	m_nCount-=nCount;

	return true;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void Array<TYPE>::removeAll()
{
//Size�͊m�ۂ��Ă����Ă��o�b�t�@������Ƃ͌���Ȃ��̂ł�����getSize�ł͂Ȃ�getCount�Ő������B
	deleteOldBuffer(m_apData,getCount());

	init(0);
}


//ArrayAD///////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
ArrayAD<TYPE>::~ArrayAD()
{
	Array<TYPE>::removeAll();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
void ArrayAD<TYPE>::deleteOldBuffer(TYPE* pBuffer,uint nSize)
{
	for (uint n=0;n<nSize;n++)
		delete pBuffer[n];
	delete pBuffer;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
bool ArrayAD<TYPE>::setAt(uint nIndex,TYPE tValue)
{
	if (nIndex>=Array<TYPE>::getCount())	return false;

	Array<TYPE>::m_nCount = getMax(Array<TYPE>::m_nCount,nIndex);
	delete Array<TYPE>::m_apData[nIndex];
	Array<TYPE>::m_apData[nIndex] = tValue;
	return true;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
bool ArrayAD<TYPE>::removeAt(uint nIndex,uint nCount)
{
	if (nIndex+nCount>=Array<TYPE>::getCount())	return false;

//�͈͂��폜
	for (uint n=nIndex;n<nIndex + nCount;n++)
	{
		delete Array<TYPE>::m_apData[n];
	}

	return Array<TYPE>::removeAt(nIndex,nCount);
}


} //namespace monapi2

#endif

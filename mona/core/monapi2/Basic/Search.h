/**
	@file	Search.h
	@brief	�\�[�g�E�T��

	�\�[�g�E�T��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_SEARCH_H
#define _MONAPI2_BASIC_SEARCH_H

#include "switch.h"
#include "Type.h"
#include "Memory.h"

namespace monapi2	{

//public:///////////////
/**
	@brief	�N�C�b�N�\�[�g�B
	@date	2005/08/20	junjunn �쐬
*/
void quicksort(void* pavArray,uint iArrayMemberCount,uint nArrayMemberWidth,int (__cdecl *pFnCompare)(const void *p,const void *q));





//protected:////////////////////////

//define���Ă��QuickSort�̃X�s�[�h�𑪂郂�[�h
//#define _PERFORMANCETEST

typedef int (__cdecl *FnQSortCompare)(const void *p,const void *q);

/**
	@brief	quicksort�̃��[�`���������B
	@date	2005/08/20	junjunn �쐬
*/
class CQuickSort
{
public:
///iStart�Ԗڂ���iStart+iCount�Ԗڂ܂ł̋�Ԃ��\�[�g
	void Sort(void* pavArray,int iStart,int iCount,uint nArrayMemberWidth,FnQSortCompare pfnCompare);


protected:
///�߂�l��iReturn�Ƃ���ƁA
///��������s����������m_pavArray�͈ȉ��̓�̐����𖞂����悤�ɓ�������Ă���B
///�Em_pavArray[iStart]�`m_pavArray[iReturn-1]�̗v�f�͑S��m_pav[iReturn]���<=�B
///�Em_pavArray[iReturn+1]�`m_pavArray[iStart+iCount-1]�̗v�f�͑S��m_pav[iReturn]���>=�B
	inline int Partition(int iStart,int iCount);

///iLeft�AiMiddle�AiRight��3���\�[�g����B�\�[�g�������Ȃ�s�{�b�g��������̂Ɏg���B
	inline void sortTriplet(int iLeft,int iMiddle,int iRight);

///iIndex���A�h���X�ɕϊ�
	void* getElementAddress(int iIndex)		{return (char*)m_pavArray + iIndex*m_nArrayMemberWidth;}
///pvTo�̃A�h���X��pvFrom�̒l������B
	void set(void* pvTo,void* pvFrom)		{MemoryFn::copy(pvTo,pvFrom,m_nArrayMemberWidth);}

//��r
	int compare(void* p,void* q)			{return m_pfnCompare(p,q);}
///��������K�v�����邩�B
	bool isSwapRequired(void* p,void* q)	{return (compare(p,q)>0);}

///i1��i2�̈ʒu�̒l������ւ���B
	inline void swap(int i1,int i2);

///�\�[�g����Ă��邩���؁B
	bool isSorted();


/* ������
///�v�f�������Ȃ��Ƃ���QuickSort�����ʂ̃\�[�g�@���g���������I�[�o�[�w�b�h�̊֌W�ő����Ȃ�B
///���̂��߂̏��\�[�g�B
	inline void SmallSort(int iStart,int iCount);
///SmallSort�̃T�u���[�`��
	inline void InsertionSort(int iStart,int iCount);
*/

protected:
	int m_iStart;					///<�\�[�g�̃X�^�[�g�ʒu
	int m_iCount;					///<�\�[�g�̃J�E���g
	void* m_pavArray;				///<�\�[�g���ׂ��z��
	uint m_nArrayMemberWidth;		///<�\�[�g���ׂ��z��̃����o�̃r�b�g��
	FnQSortCompare m_pfnCompare;	///<��r�֐�

	char* m_pSwapBuffer;			///<Swap()���̈ꎞ�Ҕ�̈�Ɏg���BSwap()�̒��Ŗ���new���Ċm�ۂ���̂����������̂ŁB


public:
#ifdef _PERFORMANCETEST
	uint m_nTimeTaken;				///<�\�[�g�ɂ�����������
#endif
};

//qsort�̑��x���e�X�g����
#ifdef _PERFORMANCETEST
	void TestQSort();
#endif


///Int�̔�r
int compareByInt(const void *p,const void *q);
///char�ł̕������r
int compareByString(const void *p,const void *q);

}	//namespace monapi2

#endif

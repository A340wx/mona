/**
	@file	CollectionList.h
	@brief	�R���N�V���� ���X�g

	�R���N�V���� ���X�g

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_COLLECTIONLIST_H
#define _MONAPI2_BASIC_COLLECTIONLIST_H

#include "switch.h"
#include "Type.h"
#include "String.h"

namespace monapi2	{

//�\�[�g�Ŏg����r�֐���typedef���Ă����B
typedef int (__cdecl *FnCompare)(const void *p,const void *q);

///<StringList::sort()�ȂǂŎg���B
int compareByPString(const void *p, const void *q);

///���X�g�̏���Ɏg���B
typedef void* position;


/**
	@brief	List�̓����Ŏg�p����B�l�ƁA���ƑO�̗v�f�ւ̃|�C���^�����B���ꎩ�̂̓��[�U�[�͎g��Ȃ��B�B
			Monapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE>
class CListElement
{
public:
	CListElement();					///<�R���X�g���N�^

public:
	TYPE m_tValue;					///<�l
	CListElement<TYPE>* m_pPrev;	///<���̗v�f�ւ̃|�C���^
	CListElement<TYPE>* m_pNext;	///<�O�̗v�f�ւ̃|�C���^
};

//
/**
	@brief	�f�X�g���N�^��m_tValue��delete����^�C�v��CListElement�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE>
class CListElementAD:public CListElement<TYPE>
{
public:
	~CListElementAD()	{delete CListElement<TYPE>::m_tValue;}	///<�f�X�g���N�^
};

/*
class List��class ListAD�̃x�[�X�N���X�B

���X�g�̃p�����[�^�[�ɂ͓��ނ�����܂��B
��߂�int,float,class*�Ȃǂǂ̌^���쐬���邩�̃^�C�v��
������͎���delete���I���ɂ��邩�I�t�ɂ��邩�̃t���O�B

template <class TYPE,class ELEMENT>
��TYPE���O�҂�ELEMENT����҂��w�肵�Ă��܂��B
TYPE�ɂ�int,float,class*�Ȃǂ̔C�ӂ̌^��ݒ�\�B
ELEMENT�ɂ͎���delete�Ȃ��Ȃ�CListElement<TYPE>�A����delete����Ȃ�CListElementAD<TYPE>��
������I���\�B

������x�[�X�Ƀp�����[�^�[�ȈՔł�List<TYPE>��ListAD<TYPE>���g�ݗ��Ă��A
�����Ă������x�[�X��List<int>�Ȃǂ̎��ۂ̃C���X�^���X�����s���܂��B

	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
class ListBase
{
public:
	ListBase();								///<�R���X�g���N�^
	virtual ~ListBase();					///<�f�X�g���N�^

//�擾
	position getHeadPosition() const;		///<�擪�ʒu�𓾂�B
	position getTailPosition() const;		///<�I���ʒu�𓾂�B
	TYPE getNext(position* ppos) const;		///<���񂵁A���̈ʒu��TYPE�𓾂�B
	TYPE getPrev(position* ppos) const;		///<���񂵁A�O�̈ʒu��TYPE�𓾂�B
	uint getCount() const;					///<�v�f����Ԃ��B
	bool isEmpty()	const {return (getCount()==0);}
	TYPE getAt(position pos) const;			///<pos�̈ʒu��TYPE�𓾂�B
	position find(TYPE tFind) const;		///<tFind�̒l���������o�̈ʒu��position�œ���B

//����
	void addTail(TYPE t);					///<������t�𑫂��B
	void addHead(TYPE t);					///<�擪��t�𑫂��B
	void insertAfter(position pos,TYPE t);	///<pos�̌��t�𑫂��B
	void insertBefore(position pos,TYPE t);	///<pos�̑O��t�𑫂��B
	virtual void setAt(position pos,TYPE t);///<pos�̈ʒu��t���Z�b�g�B
	virtual void removeAt(position pos);	///<pos�̈ʒu�̗v�f�������B
	virtual void removeAll();				///<�S�ď����ă��X�g������������B

///nIndex�Ԗڂ̗v�f�����X�g�̑O�A�܂��͌��ɓ������B
///@bToHead true�Ȃ瓪�����ɁAfalse�Ȃ疖�������ɓ������B
///@return ���������v�f�̐V�����ʒu
	int moveNextPrev(uint nIndex,bool bToHead);


//����
	position getPositionFromIndex(uint nIndex) const;	///<nIndex�̈ʒu��position�œ���B�i0=�擪�j


///�ړ��E���ёւ�
//�\�[�g�͏�ɏ��������~�����~�����ꍇ��pFnCompare���t�ɂ��邩�A��������t�ɃA�N�Z�X����΂����E�E�E
	void sort(FnCompare pFnCompare);

protected:
	void init();					///<������

//removeAt�̃��X�g�\�������B
//����Ɏ��s�ł����ꍇ��pos�̎w���v�f���Ԃ��Ă���B���s�����ꍇ��NULL�B
	ELEMENT* removeAt_reconstructList(position pos);			///<pos�̈ʒu�̗v�f�������B

///���S�̂��߂̃R�s�[�R���X�g���N�^��`�B
///�q�[�v�|�C���^���j�]����̂�protected�ŃA�N�Z�X�ł��Ȃ��悤�ɂ��ăR�s�[�͋֎~�B
	ListBase(ListBase&)		{};

/**
�\�[�g�֘A�B����ɂ͑}���\�[�g���g���B

�܂��͏����̐����ĂȂ��v�f��������B
@param posStart �������X�^�[�g����ꏊ�B
@return �߂�l�͓���ւ����K�v��position
*/
	position sort_FindUnordered(position posStart) const;

///@param pos�̗v�f�𐳂����ʒu�܂ł����čs���B
///@return ���̌������X�^�[�g����ꏊ(���񂳂�Ă鎖���ۏ؂���Ă��ԑO�̏ꏊ)
	position sort_BringToOrderedPos(position pos);

///m_pFnCompare�ƏƂ炵���킹�ď��Ԃ����������ǂ���
	bool isRightOrder(TYPE* p,TYPE* q)	const{return (m_pFnCompare(p,q) <= 0);}

#ifdef _DEBUG
	void assertSort() const;	///<�f�o�b�O�p��sort()�Ő��������ׂ�ꂽ�����؁B
#endif


protected:
	ELEMENT*	m_pHead;			///<�擪�v�f
	ELEMENT*	m_pTail;			///<�����v�f
	uint		m_nCount;			///<�v�f���B�{�����X�g�\���ɂ͂Ȃ��T�O�����T�[�r�X�Ƃ���getCount()���p�ӂ��Ă����ƕ֗��Ȏ�������B
	FnCompare	m_pFnCompare;		///<��r�֐����o���Ă����B
};


/**
	@brief	���X�g�N���X�Bint�Ƃ�float�Ƃ��̒P���Ȍ^�A���͂��łɂ���class*�Ȃǂ��Ȃ��������Ɉ����B
			Monapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
//���Ȃ݂ɐ錾��"TYPE> >"�Ɣ��p�X�y�[�X���󂢂Ă���̂̓}�N���̓W�J���ɕs�s��������̂�
//�Ȃ������������Ȃ���Visual C++�R���p�C���Œʂ�Ȃ��E�E�E
template <class TYPE>
class List	: public ListBase<TYPE, CListElement<TYPE> >	{};

/**
	@brief	�����o��new�ō���đ����Ă䂭���X�g�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE>
class ListAD: public ListBase<TYPE, CListElementAD<TYPE> >	{};


/**
	@brief	��������������X�g�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
//���g��ListBase<String>�Bclass String�Œ�`���Ă���I/O��������̓��o�͂�S���ʓ|���Ă����̂�
//���X�g���ł͎��͉������Ȃ��ł����B
class StringList : public List<String>
{
public:
///�f�t�H���g�̃\�[�g���@
	void sort(FnCompare pFnCompare=compareByPString)	{List<String>::sort(pFnCompare);}
};



/**
	@brief	FILO�ȃX�^�b�N�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
class Stack	: 	public List<TYPE>	//�����I�ɂ̓��X�g�Ƃ��Ď����B
{
public:
	void push(TYPE t)	{addTail(t);}
	TYPE pop();
};

/**
	@brief	FIFO�ȃL���[�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
class Queue	: 	public List<TYPE>	//�����I�ɂ̓��X�g�Ƃ��Ď����B
{
public:
	void push(TYPE t)	{addTail(t);}
	TYPE pop();
};


}	//namespace monapi2

//////////////////////////////////////////////////////////////////////
//�e���v���[�g��.cpp�ɏ����Ă͔F������Ȃ���������̂�.h�ɓ���Ă�
#include "CollectionListInline.h"

#endif

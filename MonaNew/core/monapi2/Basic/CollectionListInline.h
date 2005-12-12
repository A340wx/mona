/**
	@file	CollectionListInline.h
	@brief	�R���N�V���� ���X�g

	�R���N�V���� ���X�g

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_COLLECTIONLISTINLINE_H
#define _MONAPI2_BASIC_COLLECTIONLISTINLINE_H

#include "Debug.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE>
CListElement<TYPE>::CListElement()
{
//	m_tValue=0;
	m_pNext=NULL;
	m_pPrev=NULL;
}


//ListBase////////////////////////
/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
ListBase<TYPE,ELEMENT>::ListBase()
{
	init();
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
ListBase<TYPE,ELEMENT>::~ListBase()
{
	removeAll();
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::init()
{
	m_pHead	= NULL;
	m_pTail	= NULL;
	m_nCount			= 0;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
position ListBase<TYPE,ELEMENT>::getHeadPosition() const
{
	return (position)m_pHead;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
position ListBase<TYPE,ELEMENT>::getTailPosition() const
{
	return (position)m_pTail;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
uint ListBase<TYPE,ELEMENT>::getCount() const
{
	return m_nCount;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
TYPE ListBase<TYPE,ELEMENT>::getNext(position* ppos) const
{
	if (! ppos)		return 0;
	ELEMENT* pCurrent = *(ELEMENT**)ppos;

	*ppos = pCurrent->m_pNext;
	return (TYPE)pCurrent->m_tValue;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
TYPE ListBase<TYPE,ELEMENT>::getPrev(position* ppos) const
{
	if (! ppos)		return 0;
	ELEMENT* pCurrent = *(ELEMENT**)ppos;

	*ppos = pCurrent->m_pPrev;
	return (TYPE)pCurrent->m_tValue;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
TYPE ListBase<TYPE,ELEMENT>::getAt(position pos) const
{
	if (! pos)	return 0;

	ELEMENT* pListElement = (ELEMENT*)pos;
	return (TYPE)(pListElement->m_tValue);
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
position ListBase<TYPE,ELEMENT>::find(TYPE tFind) const
{
	position pos = getHeadPosition();
	while (pos)
	{
		position posCur = pos;
		TYPE t = getNext(&pos);
		if (t==tFind) return posCur;
	}

	return NULL;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::addTail(TYPE t)
{
	ELEMENT* pCur = new ELEMENT;
	pCur->m_tValue = t;

	pCur->m_pPrev = m_pTail;

//����
	if (! m_pHead)
	{
		m_pHead = pCur;
		m_pTail = pCur;
	}
	else
	{
		m_pTail->m_pNext = pCur;
		m_pTail = pCur;
	}

	m_nCount++;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::addHead(TYPE t)
{
	ELEMENT* pCur = new ELEMENT;
	pCur->m_tValue = t;

	pCur->m_pNext = m_pHead;

//����
	if (! m_pHead)
	{
		m_pHead = pCur;
		m_pTail = pCur;
	}
	else
	{
		m_pHead->m_pPrev = pCur;
		m_pHead = pCur;
	}

	m_nCount++;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::insertAfter(position pos,TYPE t)
{
	if (! pos)	return;

	ELEMENT* pCur = new ELEMENT;
	pCur->m_tValue = t;

	ELEMENT* pPrev	= (ELEMENT*)pos;
	ELEMENT* pNext	= (ELEMENT*)pPrev->m_pNext;

	pPrev->m_pNext	= pCur;
	if (pNext)	pNext->m_pPrev = pCur;
	pCur->m_pPrev	= pPrev;
	pCur->m_pNext	= pNext;

	if (! pNext)	m_pTail = pCur;

	m_nCount++;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::insertBefore(position pos,TYPE t)
{
	if (! pos)	return;

	ELEMENT* pCur = new ELEMENT;
	pCur->m_tValue = t;

	ELEMENT* pNext	= (ELEMENT*)pos;
	ELEMENT* pPrev	= (ELEMENT*)pNext->m_pPrev;

	if (pPrev)	pPrev->m_pNext	= pCur;
	pNext->m_pPrev	= pCur;
	pCur->m_pPrev	= pPrev;
	pCur->m_pNext	= pNext;

	if (! pPrev)	m_pHead = pCur;

	m_nCount++;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
position ListBase<TYPE,ELEMENT>::getPositionFromIndex(uint nIndex) const
{
	position pos = getHeadPosition();

	uint n=0;
	while (pos)
	{
		if (n >= nIndex)	break;
		getNext(&pos);
		n++;
	}

	return pos;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::setAt(position pos,TYPE t)
{
	if (!pos)	return;

//�Ȃ��((ELEMENT*)pos)->m_tValue = t;�Ƃ������ʂɒu�������Ȃ����ƌ�����ListAD�̍ۂɂ͑O��
//�f�[�^��delete����K�v������̂ŁB���̏������Ȃ�List��ListAD�����ʉ��ł���B
	insertAfter(pos,t);
	removeAt(pos);
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::removeAt(position pos)
{
	ELEMENT* pCur = removeAt_reconstructList(pos);
	if (pCur)
	{
		delete pCur;
	}
}
	
/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
ELEMENT* ListBase<TYPE,ELEMENT>::removeAt_reconstructList(position pos)
{
	if (! pos)			return NULL;

	ELEMENT* pCur = (ELEMENT*)pos;
	ELEMENT* pNext= (ELEMENT*)pCur->m_pNext;
	ELEMENT* pPrev= (ELEMENT*)pCur->m_pPrev;

	if (pNext)	{pNext->m_pPrev = pCur->m_pPrev;}
	if (pPrev)	{pPrev->m_pNext = pCur->m_pNext;}
	if (pCur ==	m_pTail)	{m_pTail = pPrev;}
	if (pCur ==	m_pHead)	{m_pHead = pNext;}
	m_nCount--;

	return pCur;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template <class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::removeAll()
{
	position posHead;

	while (posHead = getHeadPosition())
	{
		removeAt(posHead);
	}

	init();
}


/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
int ListBase<TYPE,ELEMENT>::moveNextPrev(uint nIndex,bool bNext)
{
	position pos = getPositionFromIndex(nIndex);
	if (! pos)		{return nIndex;}

	TYPE tSource;
	position posOld = pos;

	int iInc;
	if (bNext)
	{
		if (nIndex>=m_nCount)	return nIndex;
		tSource = getNext(&pos);
		iInc=1;
	}
	else
	{
		if (nIndex==0)			return nIndex;
		tSource = getPrev(&pos);
		iInc=-1;
	}
	if (pos==NULL)	{return nIndex;}

	TYPE tDestin	= getAt(pos);
	setAt(pos		,tSource);
	setAt(posOld	,tDestin);

	return nIndex+iInc;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::sort(FnCompare pFnCompare)
{
	m_pFnCompare=pFnCompare;

	position posHinge = getHeadPosition();
	while ((posHinge=sort_FindUnordered(posHinge))!=NULL)	//true�Ȃ�posHinge�͐������ꏊ�ɂ��Ȃ��̂ł��̂��ƕ��בւ���
	{
//		char szState[100];char* pWrite = szState;position pos = getHeadPosition();while (pos)	{pWrite+=StringFn::format(pWrite,"%d,",getNext(&pos));}

		posHinge=sort_BringToOrderedPos(posHinge);			//posHinge�����Ԃ��������ʒu�ɕ��ёւ��B
		posHinge = getHeadPosition();						//�擪����܂�����

//		pWrite = szState;pos = getHeadPosition();while (pos){pWrite+=StringFn::format(pWrite,"%d,",getNext(&pos));}
	}

#ifdef _DEBUG
	assertSort();
#endif
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
position ListBase<TYPE,ELEMENT>::sort_FindUnordered(position posStart) const
{
//�x�_
	while(posStart)
	{
		TYPE t1 = getNext(&posStart);
		if (posStart==NULL) return NULL;	//��ׂ�Ώۂ��Ȃ��̂ŋA��

//��r�_
		position pos2=posStart;
		while (pos2)
		{
			position posBookmark=pos2;
			TYPE t2 = getNext(&pos2);

			if (! isRightOrder(&t1,&t2))		return posBookmark;
		}
	}

	return NULL;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
position ListBase<TYPE,ELEMENT>::sort_BringToOrderedPos(position pos)
{
	position posOrig=pos;

//���Ɉړ����I���W�i���̏��
	TYPE t1=getPrev(&pos);
	position posReturn=pos;

	while (pos)
	{
		position posBookmark = pos;
		TYPE t2 = getPrev(&pos);	//�O�ɏ����Ă䂭

		if (! isRightOrder(&t1,&t2))	//���������Ԃł������O�ɓ���������
		{
			if (posBookmark==NULL)		{addHead(t1);}
			else						{insertAfter(posBookmark,t1);}

			removeAt(posOrig);	//�Â��̂���菜��
			return posReturn;
		}
	}

//�擪�ɗ���
	addHead(t1);
	removeAt(posOrig);	//�Â��̂���菜��
	return posReturn;
}

#ifdef _DEBUG
/**
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE,class ELEMENT>
void ListBase<TYPE,ELEMENT>::assertSort() const
{
	if (getCount()<2)	return;

	position pos = getHeadPosition();
	TYPE t1 = getNext(&pos);

	while(pos)
	{
		TYPE t2 = getNext(&pos);

//		ASSERT(isRightOrder(&t1,&t2));

		t1=t2;
	}
}
#endif


//Stack////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
TYPE Stack<TYPE>::pop()
{
	position posTail = List<TYPE>::getTailPosition();
	if (posTail==NULL)	return 0;
	TYPE tReturn = List<TYPE>::getAt(posTail);
	List<TYPE>::removeAt(posTail);

	return tReturn;
}

//Queue////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
TYPE Queue<TYPE>::pop()
{
	position posHead = List<TYPE>::getHeadPosition();
	if (posHead==NULL)	return 0;
	TYPE tReturn = List<TYPE>::getAt(posHead);
	List<TYPE>::removeAt(posHead);

	return tReturn;
}

}	//namespace monapi2
#endif

/**
	@file	CollectionMapInline.h
	@brief	�R���N�V���� �}�b�v

	�R���N�V���� �}�b�v

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_COLLECTIONMAPINLINE_H
#define _MONAPI2_BASIC_COLLECTIONMAPINLINE_H

#include "Memory.h"

namespace monapi2	{

//MapBase//////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template <class KEYTYPE,class VALUETYPE>
void MapBase<KEYTYPE,VALUETYPE>::initHashTable(uint nSize)
{
//	ASSERT(nSize % 10!=0);	//�O�̂��߂����Ƒf����I�񂾂��ȒP�Ȍ��؁E�E�E
	m_nHashTableSize = nSize;
}

//MapUncollidable///////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapUncollidable<KEYTYPE,VALUETYPE>::init()
{
	m_apListPKVP=NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
MapUncollidable<KEYTYPE,VALUETYPE>::~MapUncollidable()
{
	removeAll();
}


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapUncollidable<KEYTYPE,VALUETYPE>::initHashTable(uint nSize)
{
	MapBase<KEYTYPE,VALUETYPE>::initHashTable(nSize);

	m_apListPKVP = new ListADPSKVPair*[nSize];
	for (uint n=0;n<nSize;n++)
	{
		m_apListPKVP[n] = new ListADPSKVPair;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
SKVPairBase<KEYTYPE,VALUETYPE>*
 MapUncollidable<KEYTYPE,VALUETYPE>::lookup_Internal(uint nHash,KEYTYPE tKey) const
{
	ListADPSKVPair* pListAD;
	monapi2::position pos;
	if (lookup_Internal(nHash,tKey,&pListAD,&pos))
	{
		return pListAD->getAt(pos);
	}

	return NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
bool MapUncollidable<KEYTYPE,VALUETYPE>::lookup_Internal(uint nHash,KEYTYPE tKey,ListADPSKVPair** ppListOut,monapi2::position* pPosOut) const
{
//����n�b�V���l�ɂȂ����v�f���W�߂����X�g
	ListADPSKVPair* pList = m_apListPKVP[nHash];

//���X�g�̑傫����0�Ȃ猩����͂����Ȃ��̂ŋp���B
	if (pList->getCount() == 0)	return false;

//���X�g�����񂵂Ċe�v�f��tKey�Ƃ̒��ڔ�r�B
	monapi2::position pos = pList->getHeadPosition();
	while (pos)
	{
		monapi2::position pCurPos = pos;
		SKVPair* pKVP = pList->getNext(&pos);
		if (pKVP->m_tKey == tKey)
		{
			*ppListOut = pList;
			*pPosOut = pCurPos;
			return true;
		}
	}
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapUncollidable<KEYTYPE,VALUETYPE>::removeAll()
{
	if (MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize==0)	return;

	for (uint n=0;n<MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize;n++)
	{
		ListADPSKVPair* pList = m_apListPKVP[n];
		delete pList;
	}

	delete m_apListPKVP;

	MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize=0;
	m_apListPKVP=NULL;
	MapBase<KEYTYPE,VALUETYPE>::m_nCount=0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapUncollidable<KEYTYPE,VALUETYPE>::setAt(KEYTYPE tKey,const VALUETYPE tValue)
{
	MapBase<KEYTYPE,VALUETYPE>::m_nCount++;

	uint nHash = getHash(tKey);

	SKVPair* pKVP = lookup_Internal(nHash,tKey);
	if (pKVP)
	{
		pKVP->m_tValue = tValue;
	}
	else
	{
		SKVPair* pKVP	= new SKVPair;
		pKVP->m_tKey	= tKey;
		pKVP->m_tValue	= tValue;

		m_apListPKVP[nHash]->addTail(pKVP);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
bool MapUncollidable<KEYTYPE,VALUETYPE>::lookup(KEYTYPE tKey,VALUETYPE* ptOut) const
{
	uint nHash = getHash(tKey);

//�L�[�ɑΉ�����l��T���B
	SKVPair* pKVP = lookup_Internal(nHash,tKey);

//��������
	if (pKVP)
	{
		*ptOut = pKVP->m_tValue;
		return true;
	}
//������Ȃ�����
	else
	{
		return false;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
bool MapUncollidable<KEYTYPE,VALUETYPE>::removeAt(KEYTYPE tKey)
{
	uint nHash = getHash(tKey);

	ListADPSKVPair* pListAD;
	monapi2::position pos;
	if (lookup_Internal(nHash,tKey,&pListAD,&pos))
	{
		pListAD->removeAt(pos);
		MapBase<KEYTYPE,VALUETYPE>::m_nCount--;
		return true;
	}

	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
mapposition MapUncollidable<KEYTYPE,VALUETYPE>::getStartPosition() const
{
	mapposition pos;

	findNextPosition(&pos);
	return pos;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapUncollidable<KEYTYPE,VALUETYPE>::getNext(mapposition* ppos,KEYTYPE* ptKey,VALUETYPE* ptValue) const
{
	ListADPSKVPair* pList = m_apListPKVP[ppos->m_iListArrayIndex];
	position pos = pList->getPositionFromIndex(ppos->m_iListIndex);
	SKVPair* pKVPair = pList->getAt(pos);
	*ptKey	= pKVPair->m_tKey;
	*ptValue= pKVPair->m_tValue;

	findNextPosition(ppos);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapUncollidable<KEYTYPE,VALUETYPE>::findNextPosition(mapposition* ppos) const
{
	(ppos->m_iListIndex)++;

	for (;ppos->m_iListArrayIndex < (int)MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize;(ppos->m_iListArrayIndex)++)
	{
		ListADPSKVPair* pList = m_apListPKVP[ppos->m_iListArrayIndex];

		if (ppos->m_iListIndex >= (int)pList->getCount())
		{
			ppos->m_iListIndex=0;
			continue;
		}
		else
		{
			return;
		}
	}

	ppos->setInvalid();
}

//MapCollidable///////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapCollidable<KEYTYPE,VALUETYPE>::init()
{
	m_apKVP=NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
MapCollidable<KEYTYPE,VALUETYPE>::~MapCollidable()
{
	removeAll();
}


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapCollidable<KEYTYPE,VALUETYPE>::initHashTable(uint nSize)
{
	MapBase<KEYTYPE,VALUETYPE>::initHashTable(nSize);

	ASSERT(m_apKVP==NULL);

	m_apKVP = new SKVPair*[nSize];
	for (uint n=0;n<nSize;n++)
	{
		m_apKVP[n] = NULL;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapCollidable<KEYTYPE,VALUETYPE>::removeAll()
{
	if (MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize==0)	return;

	for (uint n=0;n<MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize;n++)
	{
		SKVPair* pKVP = m_apKVP[n];
		if (pKVP)		delete pKVP;
	}

	delete m_apKVP;

	MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize=0;
	m_apKVP=NULL;
	MapBase<KEYTYPE,VALUETYPE>::m_nCount=0;
}


//CStringMapSingle///////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapCollidable<KEYTYPE,VALUETYPE>::setAt(KEYTYPE tKey,VALUETYPE tValue)
{
	MapBase<KEYTYPE,VALUETYPE>::m_nCount++;

	uint nHash = getHash(tKey);

	SKVPair* pKVP = lookup_Internal(nHash);
	if (pKVP)
	{
		pKVP->m_tKey	= tKey;
		pKVP->m_tValue	= tValue;
	}
	else
	{
		SKVPair* pKVP = new SKVPair;
		pKVP->m_tKey	= tKey;
		pKVP->m_tValue	= tValue;

		m_apKVP[nHash] = pKVP;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
bool MapCollidable<KEYTYPE,VALUETYPE>::lookup(KEYTYPE tKey,VALUETYPE* ptOut) const
{
	uint nHash = getHash(tKey);

//�L�[�ɑΉ�����l��T���B
	SKVPair* pKVP = lookup_Internal(nHash);

//�����������A�n�b�V�������悪��v���邾���ł܂��L�[����v�Ƃ͌���Ȃ��B
	if (pKVP)
	{
//�L�[��������
		if (pKVP->m_tKey==tKey)
		{
			*ptOut = pKVP->m_tValue;
			return true;
		}
//�L�[�������Ă�B
		else
		{
			return false;
		}
	}
//������Ȃ�����
	else
	{
		return false;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
bool MapCollidable<KEYTYPE,VALUETYPE>::removeAt(KEYTYPE tKey)
{
	uint nHash = getHash(tKey);
	SAFE_DELETE(m_apKVP[nHash]);
	MapBase<KEYTYPE,VALUETYPE>::m_nCount--;
	return true;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
mapposition MapCollidable<KEYTYPE,VALUETYPE>::getStartPosition() const
{
	mapposition pos;
	findNextPosition(&pos);
	return pos;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapCollidable<KEYTYPE,VALUETYPE>::getNext(mapposition* ppos,KEYTYPE* ptKey,VALUETYPE* ptValue) const
{
	SKVPair* pKVPair = m_apKVP[ppos->m_iListArrayIndex];
	*ptKey	= pKVPair->m_tKey;
	*ptValue= pKVPair->m_tValue;

	findNextPosition(ppos);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
void MapCollidable<KEYTYPE,VALUETYPE>::findNextPosition(mapposition* ppos) const
{
	(ppos->m_iListArrayIndex)++;

	for (;ppos->m_iListArrayIndex < (int)MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize;(ppos->m_iListArrayIndex)++)
	{
		if (m_apKVP[ppos->m_iListArrayIndex])
		{
			return;
		}
	}

	ppos->setInvalid();
}

}	//namespace monapi2

#endif

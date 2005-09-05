/**
	@file	CollectionMap.h
	@brief	�R���N�V���� �}�b�v

	�R���N�V���� �}�b�v

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_COLLECTIONMAP_H
#define _MONAPI2_BASIC_COLLECTIONMAP_H

#include "switch.h"
#include "Type.h"
#include "String.h"

#include "CollectionList.h"

namespace monapi2	{

//�}�b�v�n///////////////
/**
�n�b�V���֐�

�����������炱��������\�����n�b�V���\���֐���N������邩���m��Ȃ��̂�
�����ł͕W���𐧒肷��悤�Ȏ��͂��Ȃ���getHash1�ƃo���G�[�V��������ꂻ���Ȗ��O�����鎖�ɂ����B

	@date	2005/08/20	junjunn �쐬
*/
uint getHash1(pcchar1 cszKey,uint nHashTableSize);
uint getHash1(int iKey,uint nHashTableSize);

/**
�}�b�v�n�Ɏg�p����n�b�V���e�[�u���̑傫���B
	@date	2005/08/20	junjunn �쐬
*/
enum EPrimeNumber
{
	PRIME_ORDER_10			= 11,			///<��10
	PRIME_ORDER_12			= 13,
	PRIME_ORDER_14			= 17,
	PRIME_ORDER_17			= 17,
	PRIME_ORDER_20			= 23,
	PRIME_ORDER_24			= 29,
	PRIME_ORDER_29			= 31,
	PRIME_ORDER_35			= 37,
	PRIME_ORDER_42			= 43,
	PRIME_ORDER_51			= 53,
	PRIME_ORDER_61			= 67,
	PRIME_ORDER_74			= 79,
	PRIME_ORDER_89			= 97,

	PRIME_ORDER_100			= 101,			///<��100
	PRIME_ORDER_120			= 127,
	PRIME_ORDER_144			= 149,
	PRIME_ORDER_172			= 173,
	PRIME_ORDER_207			= 211,
	PRIME_ORDER_248			= 251,
	PRIME_ORDER_298			= 307,
	PRIME_ORDER_358			= 359,
	PRIME_ORDER_429			= 431,
	PRIME_ORDER_515			= 521,
	PRIME_ORDER_619			= 631,
	PRIME_ORDER_743			= 751,
	PRIME_ORDER_891			= 907,

	PRIME_ORDER_1000		= 1009,			///<��1K
	PRIME_ORDER_1200		= 1201,
	PRIME_ORDER_1440		= 1447,
	PRIME_ORDER_1728		= 1733,
	PRIME_ORDER_2073		= 2081,
	PRIME_ORDER_2488		= 2503,
	PRIME_ORDER_2985		= 2999,
	PRIME_ORDER_3583		= 3593,
	PRIME_ORDER_4299		= 4327,
	PRIME_ORDER_5159		= 5167,
	PRIME_ORDER_6191		= 6197,
	PRIME_ORDER_7430		= 7433,
	PRIME_ORDER_8916		= 8923,

	PRIME_ORDER_10000		= 10007,			///<��10K
	PRIME_ORDER_12000		= 12007,
	PRIME_ORDER_14400		= 14447,
	PRIME_ORDER_17280		= 17291,
	PRIME_ORDER_20736		= 20743,
	PRIME_ORDER_24883		= 24889,
	PRIME_ORDER_29859		= 29863,
	PRIME_ORDER_35831		= 35837,
	PRIME_ORDER_42998		= 43003,
	PRIME_ORDER_51597		= 51599,
	PRIME_ORDER_61917		= 61927,
	PRIME_ORDER_74300		= 74311,
	PRIME_ORDER_89161		= 89189,

	PRIME_ORDER_100000		= 100003,			///<��100K
	PRIME_ORDER_120000		= 120011,
	PRIME_ORDER_144000		= 144013,
	PRIME_ORDER_172800		= 172801,
	PRIME_ORDER_207360		= 207367,
	PRIME_ORDER_248832		= 248839,
	PRIME_ORDER_298598		= 298601,
	PRIME_ORDER_358318		= 358327,
	PRIME_ORDER_429981		= 429991,
	PRIME_ORDER_515978		= 515993,
	PRIME_ORDER_619173		= 619181,
	PRIME_ORDER_743008		= 743027,
	PRIME_ORDER_891610		= 891617,

	PRIME_ORDER_1000000		= 1000003,			///<��1M
	PRIME_ORDER_1200000		= 1200007,
	PRIME_ORDER_1440000		= 1440011,
	PRIME_ORDER_1728000		= 1728017,
	PRIME_ORDER_2073600		= 2073601,
	PRIME_ORDER_2488320		= 2488327,
	PRIME_ORDER_2985984		= 2985991,
	PRIME_ORDER_3583180		= 3583187,
	PRIME_ORDER_4299816		= 4299821,
	PRIME_ORDER_5159780		= 5159813,
	PRIME_ORDER_6191736		= 6191737,
	PRIME_ORDER_7430083		= 7430107,
	PRIME_ORDER_8916100		= 8916107,

	PRIME_ORDER_10000000	= 10000019,			///<��10M
	PRIME_ORDER_12000000	= 12000017,
	PRIME_ORDER_14400000	= 14400011,
	PRIME_ORDER_17280000	= 17280013,
	PRIME_ORDER_20736000	= 20736017,
	PRIME_ORDER_24883200	= 24883207,
	PRIME_ORDER_29859840	= 29859877,
	PRIME_ORDER_35831808	= 35831833,
	PRIME_ORDER_42998169	= 42998173,
	PRIME_ORDER_51597803	= 51597817,
	PRIME_ORDER_61917364	= 61917367,
	PRIME_ORDER_74300837	= 74300839,
	PRIME_ORDER_89161004	= 89161013,

//	PRIME_ORDER_100000000	= 100000007,	///<��100M	�i����ȑ�ʂɃ�������H���A�v���P�[�V�����͐݌v�����������Ԉ���ĂȂ����E�E�E�j
//	PRIME_ORDER_1000000000	= 1000000007,	///<��1G�@

//����ȏ��UINT_MAX��4294967296�𒴂���̂Ŏg���@��Ȃ����ƁB
};

/**
	@brief	�}�b�v�̒��Ŏg���B�L�[�ƒl�̃y�A���B���ꎩ�͎̂g��Ȃ��B
	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
struct SKVPairBase
{
	KEYTYPE		m_tKey;
	VALUETYPE	m_tValue;
};

/**
Map�n�̏���Ɏg���ʒu���B
list�n��position�Ƃ͑S�R�Ⴂ�C���f�b�N�X�x�[�X�������ւ̂��ߓ����悤�ȕ��@��
�g����悤�ɏ������׍H������B

	@date	2005/08/20	junjunn �쐬
*/
class mapposition
{
public:
	mapposition();	///<�R���X�g���N�^

/**
while (mapposition)�ŌĂяo�����L������B
�|�C���^�x�[�X��position�ƃC���f�b�N�X�x�[�X��mapposition�𓯂��`�ɂ��Ă��܂��Ȃ��
���ŃR�\�R�\���Ď��炩������Ȃ����E�E�E���ꐫ�ƌ��邩�C���`�L�ƌ��邩�B
*/
	operator int()	{return m_iListArrayIndex>=0;}

///�����Ȓl�Ƃ��ăZ�b�g����B
	void setInvalid()	{m_iListArrayIndex=-1;}


public:
	int m_iListArrayIndex;		///<���X�g�z��̃C���f�b�N�X
	int m_iListIndex;			///���X�g�̒��̃C���f�b�N�X�B
};


/*
�}�b�v�̃N���X�}

StringMap<int>�@�@�@�@�@�@StringMapCollidable<int>						//�l�^�̎��̉�

StringMap<VALUETYPE>�@�@�@StringMapCollidable<VALUETYPE>				//�L�[�^�ƃn�b�V���֐��E�Ăяo���E�������݂Ȃǎ����BUncollibable�}�b�v�̓f�t�H�̃}�b�v�`���Ƃ��Ė������ɂȂ�B
�@�@|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@|
�@�@|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@|�@�@�@�L�[�^�̎��̉�
�@�@|�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@|
MapUncollidable<KEYTYPE,VALUETYPE>�@MapCollidable<KEYTYPE,VALUETYPE>	//�n�b�V���e�[�u���̎���
 �@�@ �_�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�^
  �@�@�@�_�@�@�@�@�@�@�@�@�@�@�@�@�@�@�^�@�@�@�@	�p��
  �@�@�@�@�_�@�@�@�@�@�@�@�@�@�@�@�@�^
�@�@�@�@�@�@�@�@�@�@MapBase												//�n�b�V���e�[�u���̗v�f������
*/

/**
�}�b�v�̊�b�N���X�B�n�b�V���̉����܂������ĂȂ��̂ł܂��
�����ł��Ȃ����}�b�v�̌n�}�I�ɑS�}�b�v�n�̈�ԉ��ɂ��ꂪ���݂���B

	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
class MapBase
{
	typedef SKVPairBase<KEYTYPE,VALUETYPE> SKVPair;

public:
	uint getCount()	{return m_nCount;}
	virtual bool lookup(KEYTYPE tKey,VALUETYPE* ptOut) const = 0;
	virtual mapposition getStartPosition() const = 0;
	virtual void getNext(mapposition* ppos,KEYTYPE* ptKey,VALUETYPE* ptValue) const = 0;
	virtual uint getHash(KEYTYPE tKey)	const =0;
	virtual void findNextPosition(mapposition* ppos) const = 0;
	virtual void initHashTable(uint nSize) = 0;
	virtual void setAt(KEYTYPE tKey,VALUETYPE tValue)=0;
	virtual bool removeAt(KEYTYPE tKey) = 0;
	virtual void removeAll() = 0;

protected:
	MapBase()		{m_nCount=0;}		///<���܂����E�E�E�Bprotected�ɂ��ăA�N�Z�X�֎~�B


protected:
	uint m_nHashTableSize;	///<�n�b�V���e�[�u���̑傫��
	uint m_nCount;			///<���݂̗v�f���B
};



/**
�}�b�v�B�L�[�͏Փˉ\�B
�������Ƀ}�b�v���ꂽ�Փ˃L�[�̓��X�g�ŊǗ�����Ă���B

	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
class MapUncollidable : public MapBase<KEYTYPE,VALUETYPE>
{
	typedef SKVPairBase<KEYTYPE,VALUETYPE> SKVPair;
	typedef ListAD<SKVPair*> ListADPSKVPair;

public:
///�R���X�g���N�^�B
	MapUncollidable()						{init();}
	MapUncollidable(uint nHashTableSize)	{init();initHashTable(nHashTableSize);}
///������
	void init();

///�f�X�g���N�^�B
	virtual ~MapUncollidable();

///�n�b�V���e�[�u���̏������B�g���O�ɐ�΂Ɏ��s����K�v������B
///@param nSize �n�b�V���e�[�u���̃T�C�Y�B�ő�v�f�����20���ȏ�傫���f����I�Ԃ̂��ő�Ɍ����悭�Ȃ�B
	void initHashTable(uint nPrimeNumber);

///�L�[�ŒT���B
///�q�b�g�����ꍇ�͖߂�l��true���Ԃ�ptOut�ɒl�������Ă���B
///�q�b�g���Ȃ������ꍇ��false���Ԃ�ptOut�ɂ͉�������Ȃ��B
	bool lookup(KEYTYPE tKey,VALUETYPE* ptOut) const;

///�L�[���Z�b�g����B
///���ȏ㓯���L�[��setAt()�����s�����ꍇ�͊Y������l��setAt()�����V����t�Œu����������B
	void setAt(KEYTYPE tKey,VALUETYPE tValue);

///�L�[�ō폜�B
	bool removeAt(KEYTYPE tKey);
///�S���폜�B
	void removeAll();

///�T���B�X�^�[�g�𓾂�B
	mapposition getStartPosition() const;
///�T���Bppos�̎��̈ʒu�ƌ��݂̒l�𓾂�B
	void getNext(mapposition* ppos,KEYTYPE* ptKey,VALUETYPE* ptValue) const;

protected:
///uint nHash��KEYTYPE tKey�������Ă��̗v�f�����郊�X�g�Ƃ��̈ʒu��T���B
	bool lookup_Internal(uint nHash,KEYTYPE tKey,ListADPSKVPair** ppListOut,monapi2::position* pPosOut) const;
///uint nHash��KEYTYPE tKey�������Ă��̗v�f�̃A�h���X��T���B
	SKVPair* lookup_Internal(uint nHash,KEYTYPE tKey) const;

///�n�b�V���֐�
	uint getHash(KEYTYPE tKey)	const {return monapi2::getHash1(tKey,MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize);}

///�T���Bppos�̎��̈ʒu��T���B
	void findNextPosition(mapposition* ppos) const;


protected:
//�����o
///�����ɂ͕����A���@���g�p���Ă���B
///�i�܂��n�b�V���Ŕz��ɑ傫���U��킯�āA�����z��ɔ�΂��ꂽ�d��������̓��X�g�ő�������T��)
	ListADPSKVPair** m_apListPKVP;	//���X�g�̃A�h���X�̔z��ւ̃A�h���X�B
};

/**
	@brief	����������MapUncollidable�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class VALUETYPE>
class StringMap : public MapUncollidable<String,VALUETYPE>
{
public:
	StringMap()	{}
	StringMap(uint nHashTableSize):MapUncollidable<String,VALUETYPE>(nHashTableSize)	{}
	virtual ~StringMap(){}
};

/**
	@brief	int�����MapUncollidable
	@date	2005/08/20	junjunn �쐬
*/
template<class VALUETYPE>
class IntMap : public MapUncollidable<int,VALUETYPE>
{
public:
	IntMap()	{}
	IntMap(uint nHashTableSize):MapUncollidable<int,VALUETYPE>(nHashTableSize)	{}
	virtual ~IntMap()	{}
};


/*
�}�b�v�B�L�[�͏Փ˕s�B
�������Ƀ}�b�v���ꂽ�L�[�͌��̃G���R�[�h�����񂪈���Ă��Ă��ォ�痈���l�ŏ㏑�������B
Monapi2���t�@�����X���Q�ƁB

	@date	2005/08/20	junjunn �쐬
*/
template<class KEYTYPE,class VALUETYPE>
class MapCollidable : public MapBase<KEYTYPE,VALUETYPE>
{
	typedef SKVPairBase<KEYTYPE,VALUETYPE> SKVPair;

public:
	MapCollidable()						{init();};		///<�R���X�g���N�^
	MapCollidable(uint nHashTableSize)	{init();initHashTable(nHashTableSize);}		///<�R���X�g���N�^
	virtual ~MapCollidable();						///<�f�X�g���N�^
///������
	void init();

///�n�b�V���e�[�u���̏������B�g���O�ɐ�΂Ɏ��s����K�v������B
///@param nSize �n�b�V���e�[�u���̃T�C�Y�B�ő�v�f�����20���ȏ�傫���f����I�Ԃ̂��ő�Ɍ����悭�Ȃ�B
	void initHashTable(uint nPrimeNumber);

	void removeAll();		///<�S�v�f����菜��


///�L�[���Z�b�g����B
///���ȏ㓯���L�[��setAt()�����s�����ꍇ�͊Y������l��setAt()�����V����t�Œu����������B
	void setAt(KEYTYPE tKey,VALUETYPE t);

///�L�[������B
///�q�b�g�����ꍇ�͖߂�l��true���Ԃ�ptOut�ɒl�������Ă���B
///�q�b�g���Ȃ������ꍇ��false���A��BptOut�ɂ͉�������Ȃ��B
	bool lookup(KEYTYPE tKey,VALUETYPE* ptOut) const;

///�L�[�ō폜�B
	bool removeAt(KEYTYPE tKey);

	mapposition getStartPosition() const;
	void getNext(mapposition* ppos,KEYTYPE* ptKey,VALUETYPE* ptValue) const;

protected:
	uint getHash(KEYTYPE tKey)const 	{return getHash1(tKey,MapBase<KEYTYPE,VALUETYPE>::m_nHashTableSize);}

	SKVPair* lookup_Internal(uint nHash) const	{return m_apKVP[nHash];}

//ppos�̎��̈ʒu��T���B
	void findNextPosition(mapposition* ppos) const;

protected:
	SKVPair** m_apKVP;
};


/**
	@brief	����������MapCollidable�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class VALUETYPE>
class StringMapCollidable : public MapCollidable<String,VALUETYPE>
{
public:
	StringMapCollidable()	{}
	StringMapCollidable(uint nHashTableSize):MapCollidable<String,VALUETYPE>(nHashTableSize)	{}
	virtual ~StringMapCollidable()	{}
};

/**
	@brief	int�����MapCollidable�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
template<class VALUETYPE>
class IntMapCollidable : public MapCollidable<int,VALUETYPE>
{
public:
	IntMapCollidable()	{}
	IntMapCollidable(uint nHashTableSize):MapCollidable<int,VALUETYPE>(nHashTableSize)	{}
	virtual ~IntMapCollidable()	{}
};

}	//namespace monapi2

//////////////////////////////////////////////////////////////////////
//�e���v���[�g��.cpp�ɏ����Ă͔F������Ȃ���������̂�.h�ɓ���Ă�
#include "CollectionMapInline.h"

#endif

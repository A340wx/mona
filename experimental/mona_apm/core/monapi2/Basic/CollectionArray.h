/**
	@file	CollectionArray.h
	@brief	�R���N�V���� ���I�z��

	�R���N�V���� ���I�z��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_COLLECTIONARRAY_H
#define _MONAPI2_BASIC_COLLECTIONARRAY_H

#include "switch.h"
#include "Type.h"
#include "String.h"
#include "CollectionList.h"

namespace monapi2	{

/**
���I�z��N���X�B
int�Ƃ�float�Ƃ��̒P���Ȍ^�A���͂��łɂ���class*���Ȃ��������Ɉ����B
�V����class�Ȃǂ�����ă��X�g�ɒ~�������ꍇ��ArrayAD���Q�ƁB

	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
class Array
{
public:
	Array(uint nItitialSize=0);					///<�R���X�g���N�^�B
	virtual ~Array();								///<�f�X�g���N�^

//�擾
	uint getCount() const	{return m_nCount;};		///<�v�f���𓾂�
	uint getSize() const	{return m_nSize;};		///<�̈�̑傫���𓾂�
	TYPE getAt(uint n) const;						///<n�Ԗڂ̗v�f�𓾂�

//����
	void add(TYPE t);								///<�����ɑ���
	bool setAt(uint nIndex,TYPE tValue);			///<�w�肵���C���f�b�N�X�̒l��ݒ�
	void setSize(uint nSize);						///<�̈���m��
	bool insertAt(uint nIndex,uint nCount);			///<�w�肵���C���f�b�N�X�Ƀu���b�N��}���B
	bool removeAt(uint nIndex,uint nCount);			///<�w�肵���C���f�b�N�X����u���b�N���폜�B
	virtual void removeAll();						///<�S�Ẵ����o�������ď���������B

///�ړ��E���ёւ�
///�\�[�g�͏�ɏ��������~�����~�����ꍇ��pFnCompare���t�ɂ��邩�A��납��A�N�Z�X����΂����E�E�E
	void sort(FnCompare pFnCompare);


protected:
///�������B
	void init(uint nItitialSize);

///������nSize�̗̈���m�ۂ���B
	TYPE* getNewSize(uint nSize);

///�Œ�nCount�����܂�܂Ŋg���B�o�b�t�@�̍Ċm�ۂ��s���o�b�t�@���ړ������Ȃ�߂�l�ɌÂ��o�b�t�@�A�Ċm�ۂ͂Ȃ������̂Ȃ�NULL�B
	TYPE* extendBuffer(uint nSize);

///���S�̂��߂̃R�s�[�R���X�g���N�^��`�B
///�q�[�v�|�C���^���j�]����̂�protected�ŃA�N�Z�X�ł��Ȃ��悤�ɂ��ăR�s�[�͋֎~�B
	Array(Array&)		{};

///�Â��o�b�t�@�̈���폜�B
	virtual void deleteOldBuffer(TYPE* pBuffer,uint nSize);

protected:
	TYPE*			m_apData;			///<�����|�C���^
	uint			m_nCount;			///<���݂̗v�f��
	uint			m_nSize;			///<����Ă���o�b�t�@�̑傫���B���ʂ͗v�f�����傫���B
	FnCompare		m_pFnCompare;		///<��r�֐�
};


/**
�����o��new�ō���đ����Ă䂭Array�B
��������ListAD�ق��Y��ɂ͂����Ȃ��B
class Array���x�[�X��delete�Ɋւ�镔�����蓮�ŃI�[�o�[���C�h���Ă䂭�B

	@date	2005/08/20	junjunn �쐬
*/
template<class TYPE>
class ArrayAD : public Array<TYPE>
{
public:
	~ArrayAD();								///<�f�X�g���N�^
	bool setAt(uint nIndex,TYPE tValue);
	bool removeAt(uint nIndex,uint nCount);

protected:
	virtual void deleteOldBuffer(TYPE* pBuffer,uint nSize);		///<�Â��o�b�t�@�̈���폜�B
};

/**
	@brief	�����������Array�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
//@memo �������BString���^�C�v�Ɏg���Ă鎖�Ńo�b�N�O���E���h�Ō��\String����������Ă͏����Ă���B
//String*�Ƃ��ɂ��Ď��������������͗}����ׂ����낤���E�E�E
class StringArray : public Array<String>
{
public:
///�f�t�H���g�̃\�[�g���@
	void sort(FnCompare pFnCompare=compareByPString)	{Array<String>::sort(pFnCompare);}
};



}	//namespace monapi2

#endif


//�e���v���[�g��.cpp�ɏ����Ă͔F������Ȃ���������̂�.h�ɓ���Ă�
#include "CollectionArrayInline.h"

/**
	@file	Buffer.h
	@brief	�ėp�o�b�t�@

	�ėp�o�b�t�@

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_BUFFER_H
#define _MONAPI2_BASIC_BUFFER_H

#include "switch.h"
#include "Type.h"

namespace monapi2	{

/**
	�ėp�֗��q�[�v�o�b�t�@�B��{�I�ɂ�new���ė̈�𓾂āA�f�X�g���N�^�Ŏ���delete����@�\�������킦�����B.
	�K�v�ȕ��������I�Ƀ��������m�ۂ�
	������f�X�g���N�^�Ŏ����I�ɍs����̂Ŕ��ɕ֗��B

	@date	2005/08/20	junjunn �쐬
*/
class Buffer
{
//���\�b�h
public:
///@name ����
//@{
	Buffer();								///<�R���X�g���N�^
	Buffer(int iInitialSize);				///<�R���X�g���N�^�BSet(cp,iLength);
	~Buffer();								///<�f�X�g���N�^
//@}


///@name ����
//@{
	void copy(const uint8_t* cpSource,int iLength);	///<�̈���m�ۂ��R�s�[�B
	void copy(const Buffer* cpbuf);					///<�\���ȗ̈���m�ۂ�cpbuf���R�s�[

	uint8_t* extendBuffer(int iNewSize,bool bKeepOriginalData=false);					///<iLength�o�C�g�̗̈���m��
	void clear();									///<�����o�b�t�@�̃N���A
//@}


///@name �擾
//@{
//	int getLength()			const {return m_iLength;}
	int getSize()			const {return m_iSize;}
	const	uint8_t* getData()	const {return m_pBuffer;}		//�����f�[�^�ɃA�N�Z�X�Bconst
			uint8_t* getBuffer()	{return m_pBuffer;}			//�����f�[�^�ɃA�N�Z�X�B
//@}

//�����o
protected:
	uint8_t*	m_pBuffer;					///<�����o�b�t�@
//	int		m_iLength;					///<�����B�m�ۂ��Ă���̈�̃T�C�Y�Ƃ͕ʁB
	int		m_iSize;					///<�m�ۂ��Ă���̈�̃T�C�Y
};

}	//namespace monapi2

#endif

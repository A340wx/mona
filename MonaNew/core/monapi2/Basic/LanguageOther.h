/**
	@file	LanguageOther.h
	@brief	����E�����R�[�h�c�[��

	����E�����R�[�h�c�[��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_LANGUAGEOTHER_H
#define _MONAPI2_BASIC_LANGUAGEOTHER_H

#include "switch.h"
#include "Type.h"
#include "Language.h"

namespace monapi2	{

#if 1

#define GENERATE_CONVERSION_CODE

/**
�����R�[�h�ϊ��f�[�^�������W�F�l���[�^

Unicode�R���\�[�V�A���Ŕz���Ă���^�u��؂�`����.txt�ϊ��\��ǂ�
�ϊ��R�[�h���t�@�C���ɓf���o���B
������C�\�[�X�R�[�h�`���Ȃ̂ł��̂܂�#include�����Ⴆ�΃R�[�h����������B
�E�E�E���������ۂ̓f�[�^�ʂ������\�[�X�R�[�h�Ƃ��ăR���p�C������Ǝ��Ԃ�������ʓ|�Ȃ̂�
�R���p�C���͂��Ȃ��B
�����LanguageFn::readTable�Ńt�@�C�����O���f�[�^�t�@�C���Ƃ��ēǂݍ��݁A
�K�v�Ȏ��ɃZ�b�g����̂������Ǝv���B


�g�����F
�E�����R�[�h�ϊ��\�[�X�R�[�h�쐬

	//�ϊ��̈�����������Ă����B
		LanguageFn::initRule();
	//�Ƃ肠�����I�u�W�F�N�g�����B
		CGenerateConversionRule GCC;
	//�ϊ��̈�ݒ�B
		GCC.getConversionRule2Way()->setShiftJISUnicode();
	//���́��o�̓t�@�C���ݒ�@���@���s
		GCC.generate("CP932.txt","Language2.cpp");


�E�����R�[�h�ϊ��\�[�X�R�[�h��ǂݍ���

	//�p�����[�^�[�ݒ聕���s
		LanguageFn::readTable("Language2.cpp");


�ϊ��Ɏw������̈�ɂ��Ă͐l�Ԃ����ׂĎ蓮�ŃZ�b�g���Ă����K�v������B
������dumpBMP�����s����ƃr�b�g�}�b�v�ŕϊ��Ɏg����̈悪�킩��̂�
��������Đl�Ԃ��l�p�`�ɐ؂蕪���A�g���Ă���̈��void LanguageFn::initRule()��
���ɏ����ăZ�b�g����B

	@date	2005/08/20	junjunn �쐬
*/
class CGenerateConversionCode
{
public:
///�ϊ��̈�̌Ăяo���B
	CConversionRule2Way* getConversionRule2Way()	{return &m_ConversionRule2Way;}
///��ƃ��C��
	bool generate(pcchar1 cszConversionTableFilePath,pcchar1 cszPathOut);


protected:
///���݂�m_aIntPair�̓��e�����߂�C�R�[�h��f���o��
	void generateCCode(int i1to2,String* pstrOut);
///CIntPair::m_i1�Ŕ�r����B
	static int compareByCode1(const void* p,const void* q);
//�ϊ��\��BMP�C���[�W�ɕϊ��B�ϊ��\�����o�I�ɕ߂炦�Ăǂ��ɗL���ȃf�[�^������̂��T���B
//�ݒ肵���f�[�^��setConversionRule�̒��Ɏ蓮�Őݒ�B
	void dumpBMP();


public:


protected:
//�����o
///int�y�A�\��
	class CIntPair	{public:int m_i1,m_i2;};
///�����R�[�h1�ƕ����R�[�h2�̑S�y�A��ێ�����B
	CIntPair m_aIntPair[0xFFFF];
///�ϊ��̈惋�[���B
	CConversionRule2Way m_ConversionRule2Way;
};

#endif //#ifdef GENERATECONVIRSIONCODE

}	//namespace monapi2

#endif

/**
	@file	Language.h
	@brief	����E�����R�[�h

	����E�����R�[�h

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_LANGUAGE_H
#define _MONAPI2_BASIC_LANGUAGE_H

#include "switch.h"
#include "Type.h"
#include "String.h"
#include "CollectionArray.h"
#include "../MultiMedia/Rect.h"

namespace monapi2	{

/**
	@brief	�����֐����W�߂�static�N���X�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class CharFn
{
public:
//�擾
	static bool isLower(char1 c);		///<c��'a'�`'z'
	static bool isUpper(char1 c);		///<c��'A'�`'Z'
	static bool isAlpha(char1 c);		///<c��'a'�`'z'�A'A'�`'Z'
	static bool isAlphaDigit(char1 c);	///<c��'a'�`'z'�A'A'�`'Z'�A'0'�`'9'
	static bool isCSymbol(char1 c);		///<c��'a'�`'z'�A'A'�`'Z'�A'0'�`'9'�A'_'
	static bool isDigit(char1 c);		///<c��'0'�`'9'
	static bool isHex(char1 c);			///<c��'0'�`'9'�A'A'�`'F'
	static bool isSpace(char1 c);		///<c��0x09-0x0D�A0x20
	static bool isASCII(char1 c);		///<c��7�r�b�g�͈̔�(< 0x80)��


//����
	static byte toLower(char1 c);		///<c���������ɕϊ��B
	static byte toUpper(char1 c);		///<c��啶���ɕϊ��B
};


/*
���C�h�̃}���`�����̕ϊ�
�݌v�A�C�f�A�F

ShiftJIS����Unicode�̕ϊ���0xFFFF�̑傫���̑Ή��\������đS�������Έꔭ�ŏI��邪
���ۂ͂قƂ�ǂ̗̈�͎g�p����ĂȂ��̂ł��̂܂܂ł͖��ʂ��傫���B
�g�p����Ă���̈�͂����܂��ɕ����Ďl�p�`�̌`�ŎU��΂��Ă���̂�
���ꂼ���񋓂��Ă��������̕ϊ���������OK�B
���ׂ̈Ɉȉ��̍\���ɂȂ��Ă���B

	Rect
		1�̕ϊ��̈�

	Rect g_arectConversionXXXtoYYY[]	�Ȃ�
		XXX��YYY�ɂ���S�Ă̕ϊ��̈�B

	class ConversionRule
		g_arectConversionXXXtoYYY + �ϊ��̖��O

	CConversionRule2Way
		XXX����YYY�ւ�ConversionRule�@�{�@YYY����XXX�ւ�ConversionRule�B


	@date	2005/08/20	junjunn �쐬
*/
class CConversionRule
{
public:
	void set(pcchar1 cszName,Rect* parectConversion)
	{
		m_strName= cszName;
		m_parectConversion = parectConversion;
	}

public:
	Rect* m_parectConversion;
	String m_strName;
};

/**
1��2�A2��1�̕ϊ��̈���p�b�N
	@date	2005/08/20	junjunn �쐬
*/
class CConversionRule2Way
{
public:
	void setShiftJISUnicode();

public:
	CConversionRule m_aConversionRule[2];
};


/**
���C�h�̃}���`�����̕ϊ��B

��������API�Ƃ��Ă̑��݁B
���ۂ̕ϊ��\���̕���CLanguageCodeConverter������Ă�B


	@date	2005/08/20	junjunn �쐬
*/
class LanguageFn
{
public:
//������ϊ�
	static int convertShiftJIStoUnicode(pchar2 wszOut	,pcchar1 cszIn	,int iMaxInLen=-1);	///<char �� wchar
	static int convertUnicodetoShiftJIS(pchar1 szOut	,pcchar2 cwszIn	,int iMaxInLen=-1);	///<wchap �� char
//class Buffer���g�����ϊ�
	static int convertShiftJIStoUnicode(class Buffer* pbufOut,pcchar1 cszIn);		///<char �� wchar
	static int convertUnicodetoShiftJIS(Buffer* pbufOut,pcchar2 cwszIn);			///<wchar �� char

//�P�����R�[�h�ϊ�
///SJIS�����R�[�h����Unicode(2�o�C�g���`��)�����R�[�h�ɕϊ�
	static int convertShiftJIStoUnicode(int iSJISCode);
	static int convertShiftJIStoUnicode(byte x,byte y);
///Unicode(2�o�C�g���`��)�����R�[�h����SJIS�����R�[�h�ɕϊ�
	static int convertUnicodetoShiftJIS(int iSJISCode);
	static int convertUnicodetoShiftJIS(byte x,byte y);

///�ϊ��R�[�h�e�[�u����ǂݏo���B
	static void init(pcchar1 cszPathShiftJIStoUnicode);
	static void initRule();
};


/**
ShiftJIS����Unicode�Ȃǂ̒P�����ɂ��Ă̕ϊ��\�B
�ϊ��\����邽�߂Ƀt�@�C������f�[�^�����ǂݏo���K�v�����肱�ꂪ�I�u�W�F�N�g���ۂ��̂�
�N���X�ɂ����B
LanguageFn�̊֐��͂���ɖ₢���킹�����Ă���B

	@date	2005/08/20	junjunn �쐬
*/
class CLanguageCodeConverter
{
public:
///�R���X�g���N�^
	CLanguageCodeConverter()	{m_bReady=false;}
///�������o���Ă��邩�B
	bool isReady()	{return m_bReady;}
///�ϊ��R�[�h�e�[�u����ǂݏo���B
	void readTable(pcchar1 cszPath);
///SJIS�����R�[�h����Unicode(2�o�C�g���`��)�����R�[�h�ɕϊ�
	int convert1to2(int iCode1);
	int convert1to2(byte x,byte y);
///Unicode(2�o�C�g���`��)�����R�[�h����SJIS�����R�[�h�ɕϊ�
	int convert2to1(int iCode2);
	int convert2to1(byte x,byte y);

//1��2�A�܂���2��1�̋��ʉ�
	int convert(byte x,byte y,int i1to2);

public:
///�ϊ��̈�B�ǂ��̗̈�ɗL���ȃf�[�^������̂�Rect��ݒ肷��B
	CConversionRule2Way m_ConversionRule2Way;

protected:
///�ϊ��f�[�^
	ArrayAD<word*> m_arrayPWordConversionData[2];
///�������ł��Ă��邩
	bool m_bReady;
};


//�X�N���v�g�̏����Ɋւ���֐��B
void getCGenerateConversionCodeTableName(pchar1 szOut,CConversionRule* pConversionRule,int iIndex);

}	//namespace monapi2

#endif

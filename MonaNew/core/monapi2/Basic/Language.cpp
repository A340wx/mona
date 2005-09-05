/**
	@file	Language.cpp
	@brief	����E�����R�[�h

	����E�����R�[�h

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Language.h"
#include "StringFn.h"
#include "Buffer.h"
#include "FileFn.h"


namespace monapi2	{

//Unicode��ShiftJIS�̕ϊ����[�`���B
//��x�t�@�C����ǂލ��ޏ�������Ƃ��K�v�Ȃ̂ŃI�u�W�F�N�g�Ƃ��đ��݂��Ă���B
CLanguageCodeConverter g_ShiftJISUnicodeConverter;

//�ϊ��̈�B
Rect g_arectConversionShiftJIStoUnicode[5+1];
Rect g_arectConversionUnicodeShiftJISto[8+1];


//LanguageFn/////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertShiftJIStoUnicode(pchar2 wszOut,pcchar1 cszIn,int iMaxInLen)
{
	if (cszIn==NULL || iMaxInLen==0)	return 0;

	pchar2	pWriteStart	= wszOut;
	pchar2	pWrite		= pWriteStart;
	pcchar1	pReadStart	= cszIn;
	pcchar1	pRead		= pReadStart;
	pcchar1	pReadEnd	= pRead + iMaxInLen;

	char1 c;
	while ((c=*pRead) != '\0')
	{
		if (CharFn::isASCII(c))
		{
			*pWrite = (char2)convertShiftJIStoUnicode(0,c);
			pRead++;
		}
		else
		{
			*pWrite = (char2)convertShiftJIStoUnicode(pRead[0],pRead[1]);
			pRead+=2;
		}
		pWrite++;

		if (iMaxInLen>=0 && pRead>=pReadEnd)		break;
	}

	*pWrite = '\0';
	return pWrite - pWriteStart;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertUnicodetoShiftJIS(pchar1 szOut,pcchar2 cwszIn,int iMaxInLen)
{
	pchar1	pWriteStart	= szOut;
	pchar1	pWrite		= pWriteStart;
	pcchar2	pRead		= cwszIn;
	pcchar2	pReadEnd	= pRead + iMaxInLen;

	char2 c;
	while ((c=*pRead) != '\0')
	{
		if (c<0x80)
		{
			*pWrite++ = (char1)convertUnicodetoShiftJIS((uint)c);
		}
		else
		{
			int iReturn = convertUnicodetoShiftJIS((uint)c);
			*pWrite++ = (char1)((iReturn & 0xFF00) >> 8);
			*pWrite++ = (char1)(iReturn & 0xFF);
		}

		pRead++;

		if (iMaxInLen>=0 && pRead>=pReadEnd)
			break;
	}

	*pWrite = '\0';
	return pWrite - pWriteStart;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertShiftJIStoUnicode(Buffer* pbufOut,pcchar1 cszIn)
{
	int iSizeIn = StringFn::getLength(cszIn) + 1;
	
	pbufOut->extendBuffer(iSizeIn * 2);
	return convertShiftJIStoUnicode((pchar2)pbufOut->getBuffer(),cszIn);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertUnicodetoShiftJIS(Buffer* pbufOut,pcchar2 cwszIn)
{
	int iSizeIn = (StringFn::getLength(cwszIn) + 1) * 2;

	pbufOut->extendBuffer(iSizeIn/2);
	return convertUnicodetoShiftJIS((pchar1)pbufOut->getBuffer(),cwszIn);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertShiftJIStoUnicode(int iSJISCode)
{
	return g_ShiftJISUnicodeConverter.convert1to2(iSJISCode);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertShiftJIStoUnicode(byte x,byte y)
{
	return g_ShiftJISUnicodeConverter.convert1to2(x,y);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertUnicodetoShiftJIS(int iUnicodeCode)
{
	return g_ShiftJISUnicodeConverter.convert2to1(iUnicodeCode);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int LanguageFn::convertUnicodetoShiftJIS(byte x,byte y)
{
	return g_ShiftJISUnicodeConverter.convert2to1(x,y);
}

/**
	@brief	���[����ǂݍ��ށB
	@date	2005/08/20	junjunn �쐬
*/
void LanguageFn::initRule()
{
	g_arectConversionShiftJIStoUnicode[0].set(0x00,0x00	,0x00 + 1,0xDF + 1);
	g_arectConversionShiftJIStoUnicode[1].set(0x81,0x40	,0x9F + 1,0xFC + 1);
	g_arectConversionShiftJIStoUnicode[2].set(0xE0,0x40	,0xEE + 1,0xFC + 1);
	g_arectConversionShiftJIStoUnicode[3].set(0xFA,0x40	,0xFB + 1,0xFC + 1);
	g_arectConversionShiftJIStoUnicode[3].set(-1,0,0,0);	//�ԕ�

	g_arectConversionUnicodeShiftJISto[0].set(0x00,0x00	,0x00 + 1,0xF7 + 1);
	g_arectConversionUnicodeShiftJISto[1].set(0x03,0x91	,0x03 + 1,0xC9 + 1);
	g_arectConversionUnicodeShiftJISto[2].set(0x04,0x01	,0x04 + 1,0x51 + 1);
	g_arectConversionUnicodeShiftJISto[3].set(0x20,0x00	,0x26 + 1,0xE9 + 1);
	g_arectConversionUnicodeShiftJISto[4].set(0x2F,0x00	,0x33 + 1,0xFE + 1);
	g_arectConversionUnicodeShiftJISto[5].set(0x4E,0x00	,0x9E + 1,0xFF + 1);
	g_arectConversionUnicodeShiftJISto[6].set(0xF9,0x0E	,0xFA + 1,0xDC + 1);
	g_arectConversionUnicodeShiftJISto[7].set(0xFF,0x01	,0xFF + 1,0xE5 + 1);
	g_arectConversionUnicodeShiftJISto[8].set(-1,0,0,0);	//�ԕ�

	g_ShiftJISUnicodeConverter.m_ConversionRule2Way.setShiftJISUnicode();
}

/**
	@brief	�������B
	@date	2005/08/20	junjunn �쐬
*/
void LanguageFn::init(pcchar1 cszPathShiftJIStoUnicode)
{
	initRule();
	g_ShiftJISUnicodeConverter.readTable(cszPathShiftJIStoUnicode);
}


//CLanguageCodeConverter///////////////
/**
	@date	2005/08/20	junjunn �쐬
*/
void CLanguageCodeConverter::readTable(pcchar1 cszPath)
{
	if (m_bReady)	return;

//�t�@�C����ǂݍ���
	String strSource;
	FileFn::read(cszPath,&strSource);
	pcchar1 pSource = strSource.getString();

//1��2��2��1�̓������
	for (int iConversionWay=0;iConversionWay<2;iConversionWay++)
	{
		CConversionRule* pConversionRule = &m_ConversionRule2Way.m_aConversionRule[iConversionWay];

//�S�Ă̗̈������B
		for (int iRuleRect=0;;iRuleRect++)
		{
			Rect* pRect = &pConversionRule->m_parectConversion[iRuleRect];
			if (pRect->getLeft() < 0)	break;		//�ԕ�

//�̈���m��
			word* awBuffer = new word[pRect->getArea()];
			m_arrayPWordConversionData[iConversionWay].add(awBuffer);

//awTable_UnicodetoShiftJIS_0_224_0_1�Ȃǂ̃e�[�u���������T���B
			char szTableName[64];
			getCGenerateConversionCodeTableName(szTableName,pConversionRule,iRuleRect);
			pcchar1 pTableNamePos = StringFn::find(pSource,szTableName);
			if (pTableNamePos==NULL)		continue;
//����{��T��
			pcchar1 pBracketLeft = StringFn::find(pTableNamePos,'{');
			if (pBracketLeft==NULL)			continue;
//�e�[�u���̍ŏ��̃G���g���[�B0x�Ŏn�܂镶�����T���B
			pcchar1 pTableElementStart = StringFn::find(pBracketLeft,"0x");
			if (pTableElementStart==NULL)	continue;

			pcchar1 p = pTableElementStart;

//��ɑ���0x�`����������������ǂݍ��ށB
			for (int iCount=0;;iCount++)
			{
				if (p[0]!='0' && p[1]!='x')		break;
				int iInt = StringFn::toInt(p+2,16,&p);

				awBuffer[iCount] = (word)iInt;

				p++;	//','���X�L�b�v
				while (*p=='\n')	p++;	//���s���X�L�b�v�B
				while (*p=='\t')	p++;	//�^�u���X�L�b�v�B
				if (*p=='}')	break;		//�I���B
			}
		}
	}

	m_bReady=true;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
int CLanguageCodeConverter::convert1to2(int iCode1)
{
	return convert1to2((char1)((iCode1 & 0xFF00)>>8),(char1)(iCode1 & 0xFF));
}

/**
	@date	2005/08/20	junjunn �쐬
*/
int CLanguageCodeConverter::convert1to2(byte x,byte y)
{
	return convert(x,y,0);
}

/**
	@date	2005/08/20	junjunn �쐬
*/
int CLanguageCodeConverter::convert(byte x,byte y,int i1to2)
{
	if (! isReady())	return 0;

	CConversionRule* pConversionRule = &m_ConversionRule2Way.m_aConversionRule[i1to2];

//�S�Ă̗̈������B
	for (int iRuleRect=0;;iRuleRect++)
	{
		Rect* pRect = &pConversionRule->m_parectConversion[iRuleRect];
		if (pRect->getLeft() < 0)	break;		//�ԕ�
//�̈�ɂ���Ȃ�
		if (pRect->isPointInside(x,y))
		{
			word* awConversionTable = m_arrayPWordConversionData[i1to2].getAt(iRuleRect);
			int iReturn = awConversionTable[(y-pRect->getTop()) + pRect->getHeight()*(x - pRect->getLeft())];
			return iReturn;
		}
	}

	return 0;
}

/**
	@date	2005/08/20	junjunn �쐬
*/
int CLanguageCodeConverter::convert2to1(int iCode2)
{
	return convert2to1((char1)((iCode2 & 0xFF00)>>8),(char1)(iCode2 & 0xFF));
}

/**
	@date	2005/08/20	junjunn �쐬
*/
int CLanguageCodeConverter::convert2to1(byte x,byte y)
{
	return convert(x,y,1);
}

/**
	@date	2005/08/20	junjunn �쐬
*/
void CConversionRule2Way::setShiftJISUnicode()
{
	m_aConversionRule[0].set("ShiftJIStoUnicode",g_arectConversionShiftJIStoUnicode);
	m_aConversionRule[1].set("UnicodetoShiftJIS",g_arectConversionUnicodeShiftJISto);
}

/**
	@date	2005/08/20	junjunn �쐬
*/
void getCGenerateConversionCodeTableName(pchar1 szOut,CConversionRule* pConversionRule,int iIndex)
{
	Rect* pRect = &pConversionRule->m_parectConversion[iIndex];

	StringFn::format(szOut,
		"awTable_%s_%2X_%2X_%2X_%2X",
		pConversionRule->m_strName.getString(),pRect->getLeft(),pRect->getTop(),pRect->getRight(),pRect->getBottom());
}

}	//namespace monapi2

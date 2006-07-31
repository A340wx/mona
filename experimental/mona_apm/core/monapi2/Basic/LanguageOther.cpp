/**
	@file	LanguageOther.cpp
	@brief	����E�����R�[�h�c�[��

	����E�����R�[�h�c�[��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "LanguageOther.h"
#include "StringFn.h"
#include "FileFn.h"
#include "StringOther.h"

#ifdef GENERATE_CONVERSION_CODE
	#include "../MultiMedia/Bitmap.h"
#endif

namespace monapi2
{

#ifdef GENERATE_CONVERSION_CODE

/**
	@brief	.h�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool CGenerateConversionCode::generate(cpchar1 cszConversionTableFilePath,cpchar1 cszPathOut)
{
//�t�@�C����ǂ�
	String strFileContent;
	if (! FileFn::read(cszConversionTableFilePath,&strFileContent)) return false;

//�s�ɕ���
	StringDivide SDLine(strFileContent,"\n");

	int i;
//�ϊ��e�[�u���̗p��
	for (i=0;i<0xFFFF;i++)	
	{
		m_aIntPair[i].m_i1=i;
		m_aIntPair[i].m_i2=0;
	}

//�S�s����
	for (uint iLine=0;iLine<SDLine.getCount();iLine++)
	{
//�^�u�ŕ���
		StringDivide Sdword(SDLine.getAt(iLine),"	");

//�ŏ��̓R�[�h1
		cpchar1 cszCode1= Sdword.getAt(0);
		int iCode1	=StringFn::toInt(cszCode1+2,16);

//�L���ł͂Ȃ��s�B
		if (cszCode1[0] != '0') continue;		//�s����0x�Ŏn�܂�̂�

//���̓R�[�h2
		cpchar1 cszCode2 = Sdword.getAt(1);
		int iCode2;

//��`����Ă��Ȃ��ꏊ�ɂ͋󔒂�������Ă���B����͖����B		
		if (cszCode2[0] != ' ')		iCode2=StringFn::toInt(cszCode2+2,16);
		else						iCode2=0;

//�ϊ��e�[�u���ɓ����B
//		ASSERT(iCode1<0xFFFF);
		m_aIntPair[iCode1].m_i2 = iCode2;
	}

//�ϊ��\��F�ɒ�����Bitmap�ɂ���B��������đ啝�Ȑ헪�����B
//	dumpBMP();return false;

//�ŏI�I�ɓf���o���S�R�[�h
	String strCodeWhole;

//�w�b�_�[
	strCodeWhole=
		"/**\n"
		"	@file	Language2.cpp\n"
		"	@brief	class CGenerateConversionCode�Ŏ����쐬���ꂽShiftJIS����Unicode�ϊ���C++�t�@�C��\n"
		"\n"
		"	class CGenerateConversionCode�Ŏ����쐬���ꂽShiftJIS����Unicode�ϊ���C++�t�@�C��\n"
		"\n"
		"	License=Mona License\n"
		"	@version $Revision$\n"
		"	@date	$Date$\n"
		"*/\n"
		"\n"
		"#include \"Language.h\"\n"
		"\n"
		"namespace monapi2	{\n"
		"\n"
		"//���̃t�@�C���̓R���p�C���Ɏ��Ԃ�����̂Ŏ��ۂ͂��Ȃ��B����Ƀf�[�^�t�@�C���Ƃ��ēǂݏo���B\n"
		"#if 0\n\n";


//1��2�̕ϊ��e�[�u��
	generateCCode(0,&strCodeWhole);

//�R�[�h1��2������
	for (i=0;i<0xFFFF;i++)
	{
		int iI2Copy=m_aIntPair[i].m_i2;
		m_aIntPair[i].m_i2=m_aIntPair[i].m_i1;
		m_aIntPair[i].m_i1=iI2Copy;
	}
//(��)�R�[�h2�ŕ��ёւ�
	quicksort(m_aIntPair,0xFFFF,sizeof(CIntPair),compareByCode1);

//2��1�̕ϊ��e�[�u��
	generateCCode(1,&strCodeWhole);

//�t�b�^�[
	strCodeWhole+="\n\n#endif	//#if 0\n\n}	//namespace monapi2\n";

//�o��
	FileFn::write(cszPathOut,&strCodeWhole);

	return true;
}

/**
	@brief	.h�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void CGenerateConversionCode::dumpBMP()
{
	Bitmap bitmap;
	bitmap.createCanvas(0x100,0x100);

//�^�����ɓh��Ԃ��B
	bitmap.fill(0);

	for (int i=0x0;i<0xFFFF;i++)
	{
		int iCode1=m_aIntPair[i].m_i1;
		int iCode2=m_aIntPair[i].m_i2;

		if (iCode2>0)
		{
			colort color=(0x00FF0000+(iCode2));
			bitmap.setPixel(((iCode1&0xFF00)>>8),iCode1&0xFF,color);
		}
	}

	bitmap.write("test.bmp");
}

/**
	@brief	.h�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void CGenerateConversionCode::generateCCode(int i1to2,String* pstrOut)
{
	CConversionRule* pConversionRule = &m_ConversionRule2Way.m_aConversionRule[i1to2];

//�����̃e�[�u���ɕ����ď���
	{
		pstrOut->formatJoinSelf(
			"int LanguageFn::convert%s(byte x,byte y)\n"
			"{\n",
			pConversionRule->m_strName.getString());


		char szTemp[256];
//�S�Ă̗̈������
		for (int i=0;;i++)
		{
			Rect* pRect = &pConversionRule->m_parectConversion[i];
			if (pRect->getLeft() < 0)	break;	//�ԕ�

			StringFn::format(szTemp,
				"	if (0x%2X<=x&&x<0x%2X && 0x%2X<=y&&y<0x%2X)\n	{\n",
				pRect->getLeft(),pRect->getRight(),pRect->getTop(),pRect->getBottom());
			*pstrOut +=	szTemp;

			char szTableName[100];
			getCGenerateConversionCodeTableName(szTableName,pConversionRule,i);

			StringFn::format(szTemp,"		vchar %s[]={\n			",szTableName);
			*pstrOut +=	szTemp;

			int iElementOutCount=0;	//�R�[�h2������������f���o�������B
			for (int x=pRect->getLeft();x<pRect->getRight();x++)
			{
				for (int y=pRect->getTop();y<pRect->getBottom();y++)
				{
					int iCode2=m_aIntPair[y + 0x100*x].m_i2;
					StringFn::format(szTemp,"0x%4X,",iCode2);
					(*pstrOut) +=	szTemp;

//��萔�ŉ��s�܂ł���
					if (++iElementOutCount==8)
					{
						(*pstrOut)+="\n";
						if (x!=pRect->getRight()-1 || y!=pRect->getBottom()-1)	//�Ōザ��Ȃ��Ȃ�
						{
							StringFn::format(szTemp,"			");
							(*pstrOut)+=szTemp;
							iElementOutCount=0;
						}
					}
				}
			}

			StringFn::format(szTemp,
				"		};\n"
				"		return %s[(y-0x%2X) + 0x%2X*(x-0x%2X)];\n	}\n\n",
				szTableName,pRect->getLeft(),pRect->getHeight(),pRect->getTop());
			(*pstrOut) +=	szTemp;
		}
	}

	*pstrOut +=
		"	return 0;\n"
		"}\n";
}

/**
	@brief	.h�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int CGenerateConversionCode::compareByCode1(const void* p,const void* q)
{
	CIntPair* pIntPairP=(CIntPair*)p;
	CIntPair* pIntPairQ=(CIntPair*)q;

	return pIntPairP->m_i1-pIntPairQ->m_i1;
}

#endif //#ifdef GENERATE_CONVERSION_CODE

}	//namespace monapi2

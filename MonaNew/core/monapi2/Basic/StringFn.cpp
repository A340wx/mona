/**
	@file	StringFn.cpp
	@brief	������֘A

	������֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "StringFn.h"
#include "Language.h"

namespace monapi2
{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint StringFn::getLength(cpchar1 cszP)
{
	if (cszP==NULL)	return 0;
	cpchar1 p=cszP;
	while (*p!='\0')		p++;

	return p-cszP;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint StringFn::getLength(cpcharv cszP)
{
	cpcharv p=cszP;
	while (*p!=0)		p++;

	return p-cszP;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::findDiff(cpchar1 cszP,cpchar1 cszQ,int iSearchCount)
{

//�p�ɂɎg���֐��Ȃ̂Ń��[�v�̒��̃X�s�[�h�������ł������Ȃ�悤�ɃP�[�X�𕪊򂷂�B
	if (iSearchCount<0)
	{
		cpchar1 p=cszP;
		cpchar1 q=cszQ;
		for (;;)
		{
			if (*p!=*q)		return p-cszP;	\
			if (*p=='\0')	return -1;		\
			p++;q++;
		}
	}
	else
	{
		return findDiffUpto(cszP,cszQ,cszP+iSearchCount);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::findDiffUpto(cpchar1 cszP,cpchar1 cszQ,cpchar1 cszPUpto)
{
	cpchar1 p=cszP;
	cpchar1 q=cszQ;
	for (;;)
	{
		if (p==cszPUpto)	return -1;
		if (*p!=*q)			return p-cszP;
		if (*p=='\0')		return -1;
		p++;q++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::findDiffNoCase(cpchar1 cszP,cpchar1 cszQ,int iSearchCount)
{
	cpchar1 p=cszP;
	cpchar1 q=cszQ;
	cpchar1 cszPUpto = cszP+iSearchCount;

	for (;;)
	{
		if (p==cszPUpto)	return -1;
		char p2=CharFn::toLower(*p);
		char q2=CharFn::toLower(*q);
		if (p2!=q2)			return p-cszP;
		if (p2=='\0')		return -1;
		p++;q++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::compare(cpchar1 cszP,cpchar1 cszQ,int iSearchCount)
{
	int iDiffPos = StringFn::findDiff(cszP,cszQ,iSearchCount);
	if (iDiffPos==-1)
	{
		return 0;
	}
	else
	{
		return	cszP[iDiffPos]-cszQ[iDiffPos];
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 StringFn::find(cpchar1 cszSource,char1 cFind,int iSearchCount)
{
	return findUpto(cszSource,cFind,cszSource+iSearchCount);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
//@memo cszFind�ɉ����ăX�L�b�v�l��ς��邱�Ƃō������\�B
pchar1 StringFn::find(cpchar1 cszSource,cpchar1 cszFind,int iSearchCount)
{
	if (cszSource==NULL) return NULL;

	if (iSearchCount<0)
	{
		int iLengthFind = getLength(cszFind);
		cpchar1 p = cszSource;
		for (;;)
		{
			if (isEqual(p,cszFind,iLengthFind))	return (pchar1)p;	\
			if (*p=='\0')						return NULL;		\
			p++;
		}
	}
	else
	{
		return findUpto(cszSource,cszFind,cszSource+iSearchCount);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 StringFn::findUpto(cpchar1 cszSource,char1 cFind,cpchar1 cszSourceUpto)
{
	if (cszSource==NULL) return NULL;

	cpchar1 p = cszSource;

	for (;;)
	{
		if (p==cszSourceUpto)	return NULL;
		if (*p==cFind)			return (pchar1)p;
		if (*p=='\0')			return NULL;
		p++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 StringFn::findUpto(cpchar1 cszSource,cpchar1 cszFind,cpchar1 cszSourceUpto)
{
	cpchar1 p = cszSource;
	int iLengthFind = getLength(cszFind);
	for (;;)
	{
		if (p==cszSourceUpto)				return NULL;
		if (isEqual(p,cszFind,iLengthFind))	return (pchar1)p;
		if (*p=='\0')						return NULL;
		p++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 StringFn::findReverse(cpchar1 cszSource,char1 cFind,int iSearchCount)
{
	if (cszSource==NULL) return NULL;

	cpchar1 p = cszSource;
	cpchar1 pLastAppear=NULL;
	cpchar1 cszSourceUpto = cszSource+iSearchCount;

	for (;;)
	{
		if (p==cszSourceUpto)				return NULL;
		if (*p==cFind)	pLastAppear=p;
		if (*p=='\0')	return (pchar1)pLastAppear;	//��const�ւ̃L���X�g�͂��傤���Ȃ��B
		p++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 StringFn::findReverse(cpchar1 cszSource,cpchar1 cszFind,int iSearchCount)
{
	if (cszSource==NULL) return NULL;

	cpchar1 p = cszSource;
	cpchar1 pLastAppear=NULL;
	cpchar1 cszSourceUpto = cszSource+iSearchCount;
	int iLengthFind = getLength(cszFind);

	for (;;)
	{
		if (p==cszSourceUpto)				return NULL;
		if (isEqual(p,cszFind,iLengthFind))	pLastAppear=p;
		if (*p=='\0')						return (pchar1)pLastAppear;
		p++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::getCountAppear(cpchar1 cszSource,char1 cFind,int iSearchCount)
{
	if (cszSource==NULL) return 0;

	cpchar1 p=cszSource-1;
	cpchar1 cszSourceUpto = cszSource+iSearchCount;
	int iAppearCount=0;

	while (p = StringFn::findUpto(p+1,cFind,cszSourceUpto))
	{
		iAppearCount++;
	}

	return iAppearCount;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::getCountAppear(cpchar1 cszSource,cpchar1 cszFind,int iSearchCount)
{
	if (cszSource==NULL) return 0;

	cpchar1 p=cszSource-1;
	cpchar1 cszSourceUpto = cszSource+iSearchCount;
	int iAppearCount=0;
	int iLengthFind=StringFn::getLength(cszFind);

	while (p = StringFn::findUpto(p+1,cszFind,cszSourceUpto))
	{
		if (iSearchCount!=-1 && p+iLengthFind>cszSourceUpto)	break;
		iAppearCount++;
		p+=iLengthFind-1;
	}

	return iAppearCount;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::getIntAt(cpchar1 cszSource,int iBase,cpchar1* pcszEnd)
{
	cpchar1 p = cszSource;

	bool (*FnIsDigit)(char1)=(iBase==10)?CharFn::isDigit:CharFn::isHex;
	
//�܂��͐������o�Ă���܂Ői�߂�
	int iNegative = 1;

	for (;;)
	{
		if		(*p=='\0')	{if (pcszEnd) *pcszEnd=p;return 0;}
		else if (*p=='-')	iNegative*=-1;
		else if (FnIsDigit(*p))	break;

		p++;
	}

	int iReturn=0;
	for (;;)
	{
		char c=*p;
		if (! FnIsDigit(c))	break;

		int iNumber;
		if		(c>='A')	iNumber=c-'A'+10;
		else if (c>='a')	iNumber=c-'a'+10;
		else				iNumber=c-'0';

		iReturn=iReturn*iBase + iNumber;
		p++;
	}
		
	if (pcszEnd) *pcszEnd=p;
	return iReturn*iNegative;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::toInt(cpchar1 cszSource,int iBase,cpchar1* pcszEnd)
{
	return getIntAt(cszSource,iBase,pcszEnd);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
float StringFn::toFloat(cpchar1 cszSource,cpchar1* pcszEnd)
{
//cszEnd��NULL�̉\��������̂ł�����g���B
	cpchar1 cszEndTemp;

//�܂��͐����p�[�g���E��
	float fReturn = (float)getIntAt(cszSource,10,&cszEndTemp);

//�����p�[�g
	if (*cszEndTemp == '.')
	{
		float fFloatPart = (float)getIntAt(cszEndTemp+1,10,&cszEndTemp);

//������fFloatPart�͐����ł̌`�Ȃ̂ŏ����_�ɒ�������10�Ŋ��葱����B
		while (fFloatPart > 1)
			fFloatPart/=10;

		fReturn+=(fReturn>=0)?fFloatPart:-fFloatPart;
	}

	if (pcszEnd)	*pcszEnd=cszEndTemp;
	return fReturn;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::duplicate(pchar1* pszOut,cpchar1 cszIn)
{
	*pszOut = new char1[StringFn::getLength(cszIn) + 1];
	return StringFn::copy(*pszOut,cszIn);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
//�����R�[�h�͍l�����Ă��Ȃ��B
void StringFn::toLower(pchar1 szSource)
{
	for(pchar1 p=szSource;*p!='\0';p++)
	{
		*p=CharFn::toLower(*p);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void StringFn::toUpper(pchar1 szSource)
{
	for(pchar1 p=szSource;*p!='\0';p++)
	{
		*p=CharFn::toUpper(*p);
	}
}


//����////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::copy(pchar1 szOut,cpchar1 cszIn,int iCopyCount)
{
	if (cszIn==NULL)	return 0;

	pchar1  p=szOut;
	cpchar1 cq=cszIn;

	if (iCopyCount<0)
	{
		while (*p++=*cq++)
			;

		return cq-cszIn-1;
	}
	else
	{
		if (iCopyCount==0)	return 0;
//@Memo�@�������̂��߂Ȃ�MemoryFn::copy�ɂ���4�o�C�g�]���ɂ��ׂ����B
//�r����'\0'�����Ă��~�߂��Ȃ��Ȃ邪�E�E�E
		cpchar1 cqEnd=cszIn+iCopyCount;
		while (*p++=*cq++)
		{
			if (cq>=cqEnd)	break;
		}
		*p='\0';
		return cq-cszIn;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::copy(pchar2 szOut,cpchar2 cszIn,int iCopyCount)
{
	pchar2  p=szOut;
	cpchar2 cq=cszIn;

	if (iCopyCount<0)
	{
		while (*p++=*cq++)
			;

		return cq-cszIn-1;
	}
	else
	{
		cpchar2 cqEnd=cszIn+iCopyCount;
		while (*p++=*cq++)
		{
			if (cq>=cqEnd)	break;
		}
		*p='\0';
		return cq-cszIn;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::format(pchar1 szBuffer,cpchar1 cszFormat,...)
{
	vapointer vap;

	VAPOINTER_SET_START(vap,cszFormat);
	return formatV(szBuffer,cszFormat,vap);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::estimateVALength(cpchar1 cszFormat,vapointer vapStart)
{
	uint nNewLength=0;

//vl��cszFormat�̌�̈������w���悤�ɂȂ�B
	vapointer vap = vapStart;

	for (cpchar1 pRead = cszFormat;*pRead!='\0';)
	{
		char1 c1=pRead[0];
		if (c1 == '%')				//�u�������V���{������
		{
			char1 c2=pRead[1];
			if (c2=='%')			//�G�X�P�[�v�V�[�N�G���X�������B
			{
				nNewLength+=1;
			}
			else
			{
				if		(c2=='s')		//������
				{
					char* p= VAPOINTER_ADVANCE(vap,char*);
					nNewLength+=StringFn::getLength(p);
				}
				else if	(c2=='d' || c2=='x' || c2=='X')		//����
				{
					VAPOINTER_ADVANCE(vap,int);
					nNewLength+=16;		//2^32��10���Ȃ̂ŏ����_�Ƃ�+-�����Ă�����ŏ\����
				}
			}
			pRead+=2;
		}
		else
		{
			if (! CharFn::isASCII(c1))
			{
				pRead+=2;
				nNewLength+=2;
			}
			else
			{
				pRead++;
				nNewLength++;
			}
		}
	}

	return nNewLength;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::formatV(pchar1 szBuffer,cpchar1 cszFormat,vapointer vapStart)
{
	vapointer vap = vapStart;
	pchar1 pWrite = szBuffer;

	for (cpchar1 pRead = cszFormat;*pRead!='\0';)
	{
		char1 c1=pRead[0];
		if (c1 == '%')				//�u�������V���{������
		{
			char1 c2=pRead[1];
			if (c2=='%')			//�G�X�P�[�v�V�[�N�G���X�������B
			{
				*pWrite++='%';
			}
			else
			{
				int iWidth = 0;
				if (CharFn::isDigit(c2))
				{
					iWidth = c2-'0';
					c2=pRead[2];
					pRead++;
				}

				if		(c2=='s')		//������
				{
					char* p = VAPOINTER_ADVANCE(vap,char*);
					pWrite+=StringFn::copy(pWrite,p);
				}
				else if	(c2=='d')		//����
				{
					int i = VAPOINTER_ADVANCE(vap,int);
					char szString[20];;
					toString(szString,i,10,false,iWidth);
					pWrite+=StringFn::copy(pWrite,szString);
				}
				else if	(c2=='x')		//16�i����
				{
					int i = VAPOINTER_ADVANCE(vap,int);
					char szString[20];;
					toString(szString,i,16,false,iWidth);
					pWrite+=StringFn::copy(pWrite,szString);
				}
				else if	(c2=='X')		//16�i����
				{
					int i = VAPOINTER_ADVANCE(vap,int);
					char szString[20];;
					toString(szString,i,16,true,iWidth);
					pWrite+=StringFn::copy(pWrite,szString);
				}
				else	//�s���B�L�������̂܂܏o�́B
				{
					*pWrite++='%';
					*pWrite++=c2;
				}
			}
			pRead+=2;
		}
		else
		{
			if (! CharFn::isASCII(c1))
			{
				*pWrite++=*pRead++;
				*pWrite++=*pRead++;
			}
			else
			{
				*pWrite++=*pRead++;
			}
		}
	}

	*pWrite='\0';
	return pWrite-szBuffer;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::toString(pchar1 szBuffer,int iTarget,int iBase,bool bCapital,int iWidth)
{
//�܂��͐��`�͂܂��Ȃ��̏�ԂŐ������쐬�B
	char szNumberWithoutFormat[32];
	pchar1 pWrite = szNumberWithoutFormat;
	if (iTarget==0)
	{
		pWrite+=StringFn::copy(pWrite,"0");
	}
	else
	{
		if (iTarget<0)
		{
			*pWrite++='-';
			iTarget=-iTarget;
		}

		if (iBase==10)
		{
			bool bWriteOn = false;
			for (int iDivide = 1000000000;iDivide!=0;iDivide/=10)
			{
				char cDigit = (char)(iTarget/iDivide);
				if (cDigit!=0)	bWriteOn=true;
				if (bWriteOn)
					*pWrite++=toString(cDigit,bCapital);
				iTarget-=cDigit*iDivide;
			}
		}
		else
		{
			int abMaskTable[]={0xF0000000,0x0F000000,0x00F00000,0x000F0000,0x0000F000,0x00000F00,0x000000F0,0x0000000F};
			bool bWriteOn = false;
			for (int i=0;i<8;i++)
			{
				int cDigit = (char)((iTarget & abMaskTable[i]) >> ((7-i)*4));
				if (cDigit!=0)	bWriteOn=true;
				if (bWriteOn)
					*pWrite++=toString(cDigit,bCapital);
			}
		}
		*pWrite='\0';
	}

//���ꂩ�琮�`����B
	int iNumberWidth = StringFn::getLength(szNumberWithoutFormat);
	pWrite = szBuffer;
	for (int i=iNumberWidth;i<iWidth;i++)
	{
		*(pWrite++) = '0';
	}
	pWrite+=StringFn::copy(pWrite,szNumberWithoutFormat);

	return pWrite-szBuffer;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
char StringFn::toString(int i,bool bCapital)
{
	if (i<10)
	{
		return (char)('0'+i);
	}
	else
	{
		int i2=(char)(i-10);
		return (bCapital)?(char)('A'+i2):(char)('a'+i2);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::replace(pchar1 szSource,char1 cFrom,char1 cTo)
{
	int iReplaceCount=0;

	pchar1 p = szSource-1;
	while (p = find(p+1,cFrom))
	{
		*p = cTo;
		iReplaceCount++;
	}
	return iReplaceCount;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::replace(pchar1 szSource,cpchar1 cszFrom,cpchar1 cszTo)
{
//�܂��͕����񂪈�x�ł�����Ă��邩�y�����ׂ�B�u���������K�v�Ȃ��Ȃ炱�̎��_�ŋp�����Ă��������y���Ȃ�B
	cpchar1 cpNextAppear;
	if ((cpNextAppear = StringFn::find(szSource,cszFrom))==NULL)	return 0;

//�u����������ƕ����񂪂ǂ�ǂ�ς���Ă䂭�̂Ō��̃R�s�[������Ă�������͂Ɏg���B
	pchar1 cszSourceCopy;
	duplicate(&cszSourceCopy,szSource);

	int iReplaceCount = replace(szSource,cszSourceCopy,cszFrom,cszTo,cpNextAppear - szSource);

	delete cszSourceCopy;
	return iReplaceCount;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::replace(pchar1* pszOut,cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo)
{
//�܂��͒u��������̒��������߂�B
	int iReplaceLength = getReplaceLength(cszIn,cszFrom,cszTo);

	*pszOut = new char1[iReplaceLength+1];

	return replace(*pszOut,cszIn,cszFrom,cszTo);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::replace(class String* pstrOut,cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo)
{
	int iReplaceLength = getReplaceLength(cszIn,cszFrom,cszTo);
	pchar1 pBuffer = pstrOut->extendBuffer(iReplaceLength);
	return replace(pBuffer,cszIn,cszFrom,cszTo);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::getReplaceLength(cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo)
{
	int iOriginalLength = getLength(cszIn);

	int iCountAppear = getCountAppear(cszIn,cszFrom);
	int iLengthDiff = getLength(cszTo) - getLength(cszFrom);

	int iNewLength = iOriginalLength + iLengthDiff * iCountAppear;
	return iNewLength;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	StringFn::replace(pchar1 szOut,cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo,int iFirstAppear)
{
	cpchar1 cpNextAppear;

//����replace�`����̌Ăяo���ōŏ��Ɍ����ꏊ�����łɒ��ׂĂ���B
	if (iFirstAppear!=-1)
	{
		cpNextAppear = cszIn + iFirstAppear;
	}
	else
	{
//�܂��͕����񂪈�x�ł�����Ă��邩�y�����ׂ�B�u���������K�v�Ȃ��Ȃ炱�̎��_�ŋp�����Ă��������y���Ȃ�B
		if ((cpNextAppear = StringFn::find(cszIn,cszFrom))==NULL)	return 0;
	}


//�u�������̕K�v�ȏ�����˔j�����̂ł�������u�������J�n�B

//���̑��Z�b�g�A�b�v
	pchar1 pWrite	= szOut;
	cpchar1 cpRead	= cszIn;
	int iLengthFrom	= StringFn::getLength(cszFrom);

//�u���������C��
	int iReplaceCount = 0;
	while(*cpRead)
	{
		if (cpRead == cpNextAppear)
		{
			pWrite+=StringFn::copy(pWrite,cszTo);
			cpRead+=iLengthFrom;
			cpNextAppear = StringFn::find(cpRead,cszFrom);

			iReplaceCount++;
		}
		else	
		{
			*pWrite++=*cpRead++;
		}
	}

	*pWrite = '\0';
	return iReplaceCount;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int StringFn::remove(pchar1 szOut,char1 cRemove)
{
	char szRemove[2];
	szRemove[0]=cRemove;
	szRemove[1]='\0';

	return replace(szOut,szRemove,"");
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
cpchar1 StringFn::getEnd(cpchar1 cszSource)
{
	return cszSource + getLength(cszSource);
}


}		//namespace monapi2

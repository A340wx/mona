/**
	@file	String.cpp
	@brief	�ėp������N���X

	�ėp������N���X

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "String.h"
#include "StringFn.h"
#include "Memory.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
StringData::StringData()
{
	m_nSize		= 0;
	m_nLength	= 0;
	m_szData	= NULL;

	m_iRefCount=0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void StringData::registerRef()
{
	m_iRefCount++;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void StringData::unregisterRef()
{
	m_iRefCount--;

	if (m_iRefCount<=0)
	{
		delete m_szData;
		delete this;
	}
}

//String////////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String::String()
{
	init();

	createNewBuffer(0);
	empty();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String::String(int iInitialBufferLength)
{
	init();

	createNewBuffer(iInitialBufferLength);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String::String(cpchar1 cszInitialString)
{
	init();

	createNewBuffer(0);
	copy(cszInitialString);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String::String(const String& refInitialString)
{
	init();

	copy(&refInitialString);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::init()
{
	m_pStringData		= NULL;
//	m_cszStringPointer	= NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String::~String()
{
	releaseBuffer();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::releaseBuffer()
{
	if (m_pStringData)
	{
		m_pStringData->unregisterRef();
		m_pStringData=NULL;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool String::isContainable(uint nLength)
{
	if (m_pStringData==NULL)	return false;

	return (nLength+1 <= m_pStringData->m_nSize);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 String::requestModifiableBuffer(uint nLength,bool bKeepOriginalData)
{
//��������Q�Ƃ���Ă���̂Ŏ��R�ɂ͕ύX�ł��Ȃ��B����ĐV�������B
	if (m_pStringData->isLocked())
	{
		return createNewBuffer(nLength,bKeepOriginalData);
	}
//������l�����g���Ă���̂ŕύX�ł���B
	else
	{
		return extendBufferDirect(nLength,bKeepOriginalData);
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool String::isEqual(cpchar1 csz) const
{
	return StringFn::isEqual(getString(),csz);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool String::operator==(cpchar1 csz) const
{
	return isEqual(csz);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool String::operator!=(cpchar1 csz) const
{
	return (!isEqual(csz));
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool String::isEqualNoCase(cpchar1 csz) const
{
	return StringFn::isEqualNoCase(getString(),csz);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
char1 String::getAt(uint n) const
{
	if (n >= getLength())	return 0;

	return getString()[n];
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	String::find(char1 cFind,uint nStart) const
{
	if (nStart >= getLength())	return -1;

	cpchar1 cszFound = StringFn::find(getString()+nStart,cFind);
	if (cszFound==NULL)	return -1;
	else				return cszFound-getString();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	String::find(cpchar1 cszFind,uint nStart) const
{
	if (nStart >= getLength())	return -1;

	cpchar1 cszFound = StringFn::find(getString()+nStart,cszFind);
	if (cszFound==NULL)	return -1;
	else				return cszFound-getString();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	String::findReverse(char1 cfind) const
{
	cpchar1 cszFound = StringFn::findReverse(getString(),cfind);
	if (cszFound==NULL)	return -1;
	else				return cszFound-getString();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	String::findReverse(cpchar1 cszfind) const
{
	cpchar1 cszFound = StringFn::findReverse(getString(),cszfind);
	if (cszFound==NULL)	return -1;
	else				return cszFound-getString();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::getLeft(String* pstrOut,uint nCount) const
{
	getMiddle(pstrOut,0,nCount);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::getRight(String* pstrOut,uint nCount) const
{
	getMiddle(pstrOut,getLength()-nCount,nCount);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::getMiddle(String* pstrOut,uint nStart,uint nCount) const
{
	if (nStart+nCount>getLength())	return;

	pstrOut->requestModifiableBuffer(nCount,false);
	pstrOut->copy(getString()+nStart,nCount);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String String::join(cpchar1 csz) const
{
	String strNew(getString());
	strNew+=csz;
	return strNew;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String String::operator+(cpchar1 csz) const
{
	String strNew(getString());
	strNew+=csz;
	return strNew;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::empty()
{
	pchar1 pBuffer = requestModifiableBuffer(0,false);
	StringFn::empty(pBuffer);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool String::setAt(uint n,char1 c)
{
	if (n>=getLength())	return false;

	pchar1 pBuffer = requestModifiableBuffer(getLength(),true);
	pBuffer[n] = c;
	return true;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::copy(cpchar1 csz,int iCount)
{
	uint nLength = (iCount==-1)?StringFn::getLength(csz):iCount;

	pchar1 pBuffer = requestModifiableBuffer(nLength,false);

	StringFn::copy(pBuffer,csz,iCount);
	setLength(nLength);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::copy(const String* pstr)
{
	releaseBuffer();

	m_pStringData = pstr->getStringData();
	m_pStringData->registerRef();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String& String::operator=(cpchar1 csz)
{
	copy(csz);
	return *this;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String& String::operator=(const String& rstr)
{
	copy(&rstr);
	return *this;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::joinSelf(cpchar1 csz)
{
	int iOldLegth = getLength();
	uint nNewLength = iOldLegth + StringFn::getLength(csz);

	pchar1 pBuffer = requestModifiableBuffer(nNewLength,true);
	StringFn::copy(pBuffer + iOldLegth,csz);
	setLength(nNewLength);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
String& String::operator+=(cpchar1 csz)
{
	joinSelf(csz);
	return *this;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 String::extendBufferDirect(uint nMinLength,bool bKeepOriginalData)
{
//�\���ȑ傫���������Ă���̂Ŋg���̕K�v�Ȃ��B
	if (isContainable(nMinLength))	return getBufferDirect();

//���݂̃T�C�Y����{�X���Ď��܂�܂Ŋi�[�B
	uint nNewBufferLength = getSize();
	while (nMinLength+1 > nNewBufferLength)
		nNewBufferLength*=2;

//�V�̈���m�ۂ��ČÂ��f�[�^�������z��
	createNewBuffer(nNewBufferLength-1,bKeepOriginalData);

	return getBufferDirect();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 String::createNewBuffer(int iSizeWithoutNull,bool bKeepOriginalData)
{
	StringData* pOldStringData = getStringData();
	
	m_pStringData	= new StringData;
	m_pStringData->m_nSize	= iSizeWithoutNull+1;
	m_pStringData->m_szData	= new char1[getSize()];

	if (bKeepOriginalData)
	{
		setLength(iSizeWithoutNull);
		StringFn::copy(getBufferDirect(),pOldStringData->m_szData,getLength());
	}
	else
	{
		setLength(0);
		m_pStringData->m_szData[0]='\0';
	}

	if (pOldStringData)
		pOldStringData->unregisterRef();

	m_pStringData->registerRef();

	return getBufferDirect();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::format(cpchar1 cszFormat,...)
{
	vapointer vap;
	VAPOINTER_SET_START(vap,cszFormat);
	formatV(cszFormat,vap);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::formatV(cpchar1 cszFormat,vapointer vapStart)
{
	int iNewEstimateLength = StringFn::estimateVALength(cszFormat,vapStart);
	pchar1 pBuffer = requestModifiableBuffer(iNewEstimateLength,false);

	int iLength = StringFn::formatV(pBuffer,cszFormat,vapStart);
	setLength(iLength);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::formatJoinSelf(cpchar1 cszFormat,...)
{
	vapointer vapStart;
	VAPOINTER_SET_START(vapStart,cszFormat);

	int iAddLength = StringFn::estimateVALength(cszFormat,vapStart);
	int iOldLength = getLength();
	int iNewLength = iOldLength+iAddLength;
	pchar1 pBuffer = requestModifiableBuffer(iNewLength,true);

	int iLength = StringFn::formatV(pBuffer + iOldLength,cszFormat,vapStart);
	setLength(iOldLength + iLength);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int String::replace(char1 cFrom,char1 cTo)
{
	pchar1 pBuffer = requestModifiableBuffer(getLength(),true);
	return StringFn::replace(pBuffer,cFrom,cTo);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int String::replace(pchar1 cszFrom,pchar1 cszTo)
{
	int iNewLength = StringFn::getReplaceLength(getString(),cszFrom,cszTo);

	pchar1 pBuffer = requestModifiableBuffer(iNewLength,true);

	return StringFn::replace(pBuffer,cszFrom,cszTo);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int String::remove(char1 cRemove)
{
	char szRemove[2];
	szRemove[0]=cRemove;
	szRemove[1]='\0';

	return replace(szRemove,"");
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int String::remove(pchar1 csz)
{
	return replace(csz,"");
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::insert(pchar1 cszIn,uint nIndex)
{
	if (nIndex>=getLength())	return;

	int iLengthIn = StringFn::getLength(cszIn);

	int iOldLength = getLength();

//@memo �����͊ۂ��ƃR�s�[���ĂȂ��̂ŕK�v�ȏꏊ�����R�s�[������������ł���E�E�E
	pchar1 pBuffer = requestModifiableBuffer(getLength() + iLengthIn,true);

	pchar1 pInsertPos = pBuffer + nIndex;

//��Ɍ��̃f�[�^���ړ������Ă����B
	MemoryFn::copySafe(pInsertPos + iLengthIn,pInsertPos,iOldLength-nIndex+1);

//�}���B
	MemoryFn::copy(pInsertPos,cszIn,iLengthIn);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::cut(uint nIndex,uint nCount)
{
	if (nIndex>=getLength())	return;

//@memo �����͊ۂ��ƃR�s�[���ĂȂ��̂ŕK�v�ȏꏊ�����R�s�[������������ł���E�E�E
//���̕����c���Ă����K�v�����邽�ߒ����͓����B
	pchar1 pBuffer = requestModifiableBuffer(getLength(),true);

	pchar1 pDeletePos = pBuffer + nIndex;

//�f�[�^���ړ��B
	MemoryFn::copySafe(pDeletePos,pDeletePos+nCount,getLength()-nIndex-nCount+1);
	setLength(getLength()-nCount);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::toUpper()
{
	pchar1 pBuffer = requestModifiableBuffer(getLength(),true);
	StringFn::toUpper(pBuffer);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::toLower()
{
	pchar1 pBuffer = requestModifiableBuffer(getLength(),true);
	StringFn::toLower(pBuffer);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 String::getBuffer()
{
	return requestModifiableBuffer(getLength(),true);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pchar1 String::extendBuffer(uint nLength)
{
	return requestModifiableBuffer(nLength,true);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void String::recalculateLength(int iLength)
{
	if (iLength!=-1)	setLength(iLength);
	else				setLength(StringFn::getLength(getString()));
}


}		//namespace monapi2

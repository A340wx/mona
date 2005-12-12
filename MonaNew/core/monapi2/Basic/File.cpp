/**
	@file	File.cpp
	@brief	�t�@�C���ڍב���

	�t�@�C���ڍב���

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B

#ifdef MONA
	#include <monapi.h>
	#include <monapi/CMemoryInfo.h>
	#include <monapi/Messages.h>

	#include <Basic/Memory.h>
#endif

#include "File.h"

namespace monapi2	{

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
const char* File::getName() const
{
	return NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
const char* File::getPath() const
{
	return NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int File::getSize() const
{
	return 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int File::getLastModifiedTime() const
{
	return 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
	@date	2005/09/20	junjunn ���}�[�u���������B
*/
bool File::open(const char* cszPath,bool bAllowWrite)
{
#ifdef MONA
	monapi_cmemoryinfo* pMemoryInfo = monapi_call_file_read_data(cszPath,MONAPI_FALSE);
	if (! pMemoryInfo)	return false;

	m_oBuffer.copy(pMemoryInfo->Data,pMemoryInfo->Size);
	bAllowWrite=false;
	return true;
#else
	const char* pOpenFlag = (bAllowWrite)?"wb":"rb";
	m_pFile = fopen(cszPath,pOpenFlag);
	return (m_pFile!=NULL);
#endif
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint File::read(byte* pOut,uint nIndex,uint nCount) const
{
#ifndef MONA
	fseek(m_pFile,nIndex,SEEK_SET);
	return fread(pOut,sizeof(byte),nCount,m_pFile);
#else
	MemoryFn::copy(pOut,m_oBuffer.getData() + nIndex,nCount);
	return nIndex+nCount;
#endif
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint File::write(const byte* cpIn,uint nIndex,uint nCount) const
{
#ifndef MONA
	fseek(m_pFile,nIndex,SEEK_SET);
	return fwrite(cpIn,sizeof(byte),nCount,m_pFile);
#endif

	cpIn=NULL,nCount=0;nIndex=0;
	return 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void File::close()
{
#ifndef MONA
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile=NULL;
	}
#endif
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void File::setPath(const char )
{
}


}		//namespace monapi2

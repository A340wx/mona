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
*/
bool File::open(const char* cszPath,bool bAllowWrite)
{
#ifndef MONA
	const char* pOpenFlag = (bAllowWrite)?"wb":"rb";
	m_pFile = fopen(cszPath,pOpenFlag);
	return (m_pFile!=NULL);
#endif

	cszPath=NULL, bAllowWrite=false;
	return 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint File::read(byte* pOut,uint nIndex,uint nCount)
{
#ifndef MONA
	fseek(m_pFile,nIndex,SEEK_SET);
	return fread(pOut,sizeof(byte),nCount,m_pFile);
#endif

	pOut=NULL,nIndex=0,nCount=0;
	return 0;
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

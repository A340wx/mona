/**
	@file	FileOther.h
	@brief	�t�@�C�����[�e�B���e�B

	�t�@�C������E�t�@�C��������E�t�@�C�����[�e�B���e�B

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifdef MONA
	#include <monapi.h>
	#include <monapi/messages.h>
#endif

#include "Math.h"
#include "FileOther.h"
#include "StringFn.h"

namespace monapi2	{

//SplitPath//////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void SplitPath::init()
{
	StringFn::empty(m_szDirectory);
	StringFn::empty(m_szFilename);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void SplitPath::set(cpchar1 cszPath)
{
	init();

//��ԉE�̋�؂������
	cpchar1 pDivYen = StringFn::findReverse(cszPath,'\\');
//�������ł�����
	cpchar1 pDivSlash = StringFn::findReverse(cszPath,'/');

	cpchar1 pDiv = getMax(pDivYen,pDivSlash);

//���ʂɌ���������
	if (pDiv)
	{
		StringFn::copy(m_szDirectory,cszPath,pDiv - cszPath);
		StringFn::copy(m_szFilename	,pDiv+1);
	}
	else
	{
//������Ȃ�������csz���t�@�C�������f�B���N�g�������ǂ��炩�𐄑�����B
		pchar1 pDestination = StringFn::find(cszPath,'.')?m_szFilename:m_szDirectory;
		StringFn::copy(pDestination,cszPath);
	}
}

//SplitFilename//////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void SplitFilename::init()
{
	StringFn::empty(m_szName);
	StringFn::empty(m_szExtension);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void SplitFilename::set(cpchar1 cszFilename)
{
//���O�Ɗg���q�ɕ�����
	cpchar1 pDiv = StringFn::findReverse(cszFilename,'.');

	if (pDiv)
	{
		int iLengthLeft = pDiv - cszFilename;
		StringFn::copy(m_szName,cszFilename,iLengthLeft);
		StringFn::copy(m_szExtension,pDiv + 1);

#ifdef _WIN32
//�����N�V���[�g�J�b�g�̏ꍇ��aaa.txt.lnk�̂悤�Ȍ`���Ȃ̂�aaa.txt�ɕ����ł���悤������i�K���ׂ�
		if (StringFn::isEqual(m_szExtension,"lnk"))
		{
			char1 szFilenameCp[g_iMAX_PATH];
			StringFn::copy(szFilenameCp,cszFilename);		//�R�s�[�����
			*(szFilenameCp + iLengthLeft)='\0';				//.�̏ꏊ��\0���Z�b�g��

			SplitFilename SF2(szFilenameCp);				//������񒧐�
			StringFn::copy(m_szName		,SF2.getName());
			StringFn::copy(m_szExtension,SF2.getExtension());
		}
#endif
	}
//�ۂ��Ɩ��O�ɂ���B
	else
	{
		StringFn::copy(m_szName,cszFilename);
	}
}

#ifdef MONA
//ScanDirectory///////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
ScanDirectory::ScanDirectory(cpchar1 cszPath,bool includeFile,bool includeDirectory,ESortBy eSortBy)
{
	scan(cszPath,includeFile,includeDirectory,eSortBy);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void ScanDirectory::init()
{
	m_iCount = 0;
	m_oArrayPFileProperty.removeAll();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/10/12	junjunn �쐬
*/
void ScanDirectory::scan(cpchar1 cszPath,bool bIncludeFile,bool bIncludeDirectory,ESortBy /*eSortBy*/)
{
	init();
	m_strPathBase = cszPath;

	monapi_cmemoryinfo* pMemoryInfo = monapi_call_file_read_directory(cszPath,MONAPI_FALSE);

	if (! pMemoryInfo)		return;
	int iCount = *(int*)pMemoryInfo->Data;
	if (iCount == 0)		return;

	monapi_directoryinfo* pDirectoryInfo = (monapi_directoryinfo*)(pMemoryInfo->Data + sizeof(int));
	for (int i=0;i<iCount;i++) 
	{
		cpchar1 cszName = pDirectoryInfo->name;
		if (!StringFn::isEqual(cszName,".") &&	!StringFn::isEqual(cszName,".."))
		{
			bool bDirectory = (pDirectoryInfo->attr & ATTRIBUTE_DIRECTORY);

			if (
				(bIncludeFile && !bDirectory) ||
				(bIncludeDirectory && bDirectory)
				)
			{
				FileProperty* pFileProperty = new FileProperty;
				pFileProperty->m_strName	= cszName;
				pFileProperty->m_bDirectory = bDirectory;
				pFileProperty->m_iSize		= pDirectoryInfo->size;

				if (m_strPathBase.isEqual("/"))
					pFileProperty->m_strPath.format("/%s",cszName);
				else
					pFileProperty->m_strPath.format("%s/%s",m_strPathBase.getString(),cszName);

				m_oArrayPFileProperty.add(pFileProperty);
				m_iCount++;
			}
		}
		pDirectoryInfo++;
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/10/12	junjunn �쐬
*/
cpchar1 ScanDirectory::getNameAt(int iIndex) const
{
	if (! assertIndex(iIndex)) return NULL;

	return m_oArrayPFileProperty.getAt(iIndex)->getName();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
cpchar1 ScanDirectory::getPathAt(int iIndex) const
{
	if (! assertIndex(iIndex)) return NULL;

	return m_oArrayPFileProperty.getAt(iIndex)->getPath();
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/10/12	junjunn �쐬
*/
FileProperty* ScanDirectory::getFilePropertyAt(int iIndex)
{
	if (! assertIndex(iIndex)) return NULL;

	return m_oArrayPFileProperty.getAt(iIndex);
}

#endif	//ifdef MONA
}		//namespace monapi2

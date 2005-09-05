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
void SplitPath::set(pcchar1 cszPath)
{
	init();

//��ԉE�̋�؂������
	pcchar1 pDivYen = StringFn::findReverse(cszPath,'\\');
//�������ł�����
	pcchar1 pDivSlash = StringFn::findReverse(cszPath,'/');

	pcchar1 pDiv = getMax(pDivYen,pDivSlash);

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
void SplitFilename::set(pcchar1 cszFilename)
{
//���O�Ɗg���q�ɕ�����
	pcchar1 pDiv = StringFn::findReverse(cszFilename,'.');

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

//ScanDirectory///////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
ScanDirectory::ScanDirectory(pcchar1 cszPath,bool includeFile,bool includeDirectory,ESortBy eSortBy)
{
	scan(cszPath,includeFile,includeDirectory,eSortBy);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
ScanDirectory::ScanDirectory()
{
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pcchar1 ScanDirectory::getNameAt(int iIndex)
{
	iIndex=0;
	return NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pcchar1 ScanDirectory::getFullPathAt(int iIndex)
{
	iIndex=0;
	return NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pcchar1 ScanDirectory::getFilePropertyAt(int iIndex)
{
	iIndex=0;
	return NULL;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int ScanDirectory::getCount()
{
	return 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void ScanDirectory::scan(pcchar1 cszPath,bool bIncludeFile,bool bIncludeDirectory,ESortBy eSortBy)
{
	cszPath=NULL;
	bIncludeFile=false;
	bIncludeDirectory=false;
	eSortBy=SORTBY_NAME;
}


}		//namespace monapi2

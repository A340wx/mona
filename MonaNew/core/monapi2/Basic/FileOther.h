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
#ifndef _MONAPI2_BASIC_FILEOTHER_H
#define _MONAPI2_BASIC_FILEOTHER_H

#include "switch.h"
#include "Type.h"
#include "FileFn.h"

namespace monapi2	{

/**
"C:/aaa/bbb/ccc/ddd.txt"�Ȃǂ�"C:/aaa/bbb/ccc"��"ddd.txt"�ɕ�����B.

@par �g�����F
@code
��{�I�Ȏg�����F

//�\�z
	CSplitPath SplitPath("C:/aaa/bbb/ccc/ddd.txt");


//�g�p
	pcchar1 cszDir		= SplitPath.GetDir();		//=="C:/aaa/bbb/ccc"
	pcchar1 cszFilename	= SplitPath.GetFilename();	//=="ddd.txt"
@endcode

	@date	2005/08/20	junjunn �쐬
*/

class SplitPath
{
//���\�b�h
public:
///@name ����
//@{
	SplitPath()					{init();}					///<�R���X�g���N�^
	SplitPath(pcchar1 cszPath)	{set(cszPath);}				///<�R���X�g���N�^
	void init();											///<������
//@}


///@name �Z�b�g
//@{
	void set(pcchar1 cszPath);								///<�Z�b�g
//@}

///@name �擾
//@{
	pcchar1 getDirectory()	const {return m_szDirectory;}	///<�f�B���N�g��������Ԃ�
	pcchar1 getFilename()	const {return m_szFilename;}	///<�t�@�C����������Ԃ�
//@}


//�����o
protected:
	char1 m_szDirectory[g_iMAX_PATH];								///<�f�B���N�g������
	char1 m_szFilename[g_iMAX_PATH];							///<�t�@�C��������
};


/**
"test.txt"�Ȃǂ�"test"��"txt"�ɕ�����B.

@par �g�����F
@code
��{�I�Ȏg�����F

//�\�z
	CSplitFilename SplitFilename("test.txt");


//�g�p
	pcchar1 cszDir		= SplitFilename.GetName();		//=="test"
	pcchar1 cszFilename	= SplitFilename.GetExtension();	//=="txt"
@endcode

	@date	2005/08/20	junjunn �쐬
*/
class SplitFilename
{
//���\�b�h
public:
///@name ����
//@{
	SplitFilename()						{init();}				///<�R���X�g���N�^
	SplitFilename(pcchar1 cszFilename)	{set(cszFilename);}		///<�R���X�g���N�^
	void init();												///<�������B
//@}


///@name �擾
//@{
	pcchar1 getName()		const {return m_szName;}			///<���O������Ԃ�
	pcchar1 getExtension()	const {return m_szExtension;}		///<�g���q������Ԃ�
//@}

//����
	void set(pcchar1 cszFilename);								///<�Z�b�g

//�����o
protected:
	char1 m_szName[g_iMAX_PATH];								///<���O����
	char1 m_szExtension[g_iMAX_PATH];							///<�g���q����
};



/**
	@brief	�f�B���N�g�����X�L�������Ē��g��񋓁BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class ScanDirectory
{
protected:
	enum ESortBy
	{
		SORTBY_NONE,
		SORTBY_NAME,
		SORTBY_EXTENSION,
		SORTBY_LASTMODIFIEDTIME,
	};

	ScanDirectory(pcchar1 cszPath,bool includeFile,bool includeDirectory,enum ESortBy eSortBy=SORTBY_NONE);
	ScanDirectory();

	pcchar1 getNameAt(int iIndex);
	pcchar1 getFullPathAt(int iIndex);
	pcchar1 getFilePropertyAt(int iIndex);
	int getCount();

	void scan(pcchar1 cszPath,bool bIncludeFile,bool bIncludeDirectory,enum ESortBy eSortBy=SORTBY_NONE);
};

}	//namespace monapi2

#endif

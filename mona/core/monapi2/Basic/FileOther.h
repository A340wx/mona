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
#include "String.h"
#include "CollectionArray.h"

namespace monapi2	{

/**
"C:/aaa/bbb/ccc/ddd.txt"�Ȃǂ�"C:/aaa/bbb/ccc"��"ddd.txt"�ɕ�����B.

@par �g�����F
@code
��{�I�Ȏg�����F

//�\�z
	CSplitPath SplitPath("C:/aaa/bbb/ccc/ddd.txt");


//�g�p
	cpchar1 cszDir		= SplitPath.GetDir();		//=="C:/aaa/bbb/ccc"
	cpchar1 cszFilename	= SplitPath.GetFilename();	//=="ddd.txt"
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
	SplitPath(cpchar1 cszPath)	{set(cszPath);}				///<�R���X�g���N�^
	void init();											///<������
//@}


///@name �Z�b�g
//@{
	void set(cpchar1 cszPath);								///<�Z�b�g
//@}

///@name �擾
//@{
	cpchar1 getDirectory()	const {return m_szDirectory;}	///<�f�B���N�g��������Ԃ�
	cpchar1 getFilename()	const {return m_szFilename;}	///<�t�@�C����������Ԃ�
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
	cpchar1 cszDir		= SplitFilename.GetName();		//=="test"
	cpchar1 cszFilename	= SplitFilename.GetExtension();	//=="txt"
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
	SplitFilename(cpchar1 cszFilename)	{set(cszFilename);}		///<�R���X�g���N�^
	void init();												///<�������B
//@}


///@name �擾
//@{
	cpchar1 getName()		const {return m_szName;}			///<���O������Ԃ�
	cpchar1 getExtension()	const {return m_szExtension;}		///<�g���q������Ԃ�
//@}

//����
	void set(cpchar1 cszFilename);								///<�Z�b�g

//�����o
protected:
	char1 m_szName[g_iMAX_PATH];								///<���O����
	char1 m_szExtension[g_iMAX_PATH];							///<�g���q����
};



/**
	@brief	�f�B���N�g�����X�L�������Ē��g��񋓁BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/

//�P��̃t�@�C����
class FileProperty
{
public:
	cpchar1 getName()	const {return m_strName;}
	cpchar1 getPath()	const {return m_strPath;}
	int getSize()		const {return m_iSize;}
	bool isDirectory()	const {return m_bDirectory;}


public:
	String m_strName;			///<���O
	String m_strPath;			///<�p�X
	bool m_bDirectory;			///<true�Ȃ�f�B���N�g���Afalse�Ȃ�t�@�C���B
	int m_iSize;				///<�T�C�Y
};

class ScanDirectory
{
//�\�[�g�͖��C���v�������g
	enum ESortBy
	{
		SORTBY_NONE,
		SORTBY_NAME,
		SORTBY_EXTENSION,
		SORTBY_LASTMODIFIEDTIME,
	};

public:
	ScanDirectory(cpchar1 cszPath,bool bIncludeFile,bool bIncludeDirectory,enum ESortBy eSortBy=SORTBY_NONE);
	ScanDirectory()	{init();}

	cpchar1 getNameAt(int iIndex) const;
	cpchar1 getPathAt(int iIndex) const;
	FileProperty* getFilePropertyAt(int iIndex);
	int getCount()						{return m_iCount;}

	void scan(cpchar1 cszPath,bool bIncludeFile,bool bIncludeDirectory,enum ESortBy eSortBy=SORTBY_NONE);


protected:
	void init();
	bool assertIndex(int iIndex) const	{return (iIndex>=0 && iIndex<m_iCount);}


protected:
	int m_iCount;
	String m_strPathBase;			///<���ݒT�����Ă���f�B���N�g���̃p�X�B

	ArrayAD<FileProperty*> m_oArrayPFileProperty;
};

}	//namespace monapi2

#endif

/**
	@file	FileFn.cpp
	@brief	�t�@�C���ꔭ����

	�t�@�C���ꔭ����

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "FileFn.h"
#include "Buffer.h"
#include "String.h"

//�f�o�b�O�̂��߂̉��}�[�u
#ifdef _WIN32
	#include <afxwin.h>
	#include <io.h>
#endif

namespace monapi2	{

//FileFn//////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::isExist(pcchar1 cszPath)
{
	cszPath;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::isFile(pcchar1 cszPath)
{
	cszPath;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int FileFn::getSize(pcchar1 cszPath)
{
#ifdef _WIN32
	struct _finddata_t FindData;
	if (_findfirst(cszPath,&FindData)!=-1)
		return FindData.size;
	else
		return -1;
#endif

	return -1;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint FileFn::getLastModifiedTime(pcchar1 cszPath)
{
	cszPath;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::read(pcchar1 cszPath,byte* pBufferOut,int iBufferSize)
{
//�f�o�b�O�̂��߂̉��}�[�u
#ifdef _WIN32
	FILE* p=fopen(cszPath,"r");
	fread(pBufferOut,sizeof(byte),iBufferSize,p);
	fclose(p);
	return true;
#endif

	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::read(pcchar1 cszPath,Buffer* pbufOut)
{
	int iFileSize = getSize(cszPath);
	if (iFileSize!=-1)
	{
		byte* pBuffer = pbufOut->extendBuffer(iFileSize);
		read(cszPath,pBuffer,iFileSize);
		return true;
	}

	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::read(pcchar1 cszPath,String* pstrOut)
{
	int iFileSize = getSize(cszPath);
	if (iFileSize!=-1)
	{
		pchar1 pBuffer = pstrOut->extendBuffer(iFileSize+1);
		read(cszPath,(byte*)pBuffer,iFileSize);
		pBuffer[iFileSize] = '\0';
		return true;
	}

	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::write(pcchar1 cszPath,const byte* cpIn,int iCount)
{
//�f�o�b�O�̂��߂̉��}�[�u
#ifdef _WIN32
	FILE* p=fopen(cszPath,"wb");
	fwrite(cpIn,sizeof(byte),iCount,p);
	fclose(p);
	return true;
#endif

	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::write(pcchar1 cszPath,const Buffer* cpbufIn)
{
	return write(cszPath,cpbufIn->getData(),cpbufIn->getSize());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::write(pcchar1 cszPath,const String* cpstrIn)
{
	return write(cszPath,(byte*)cpstrIn->getString(),cpstrIn->getLength());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::createDirectory(pcchar1 cszPath,pcchar1 cszDirName)
{
	cszDirName;
	cszPath;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::deleteFile(pcchar1 cszPath)
{
	cszPath;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::deleteDirectory(pcchar1 cszPath)
{
	cszPath;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::move(pcchar1 cszPathFrom,pcchar1 cszPathTo)
{
	cszPathFrom;
	cszPathTo;
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::copy(pcchar1 cszPathFrom,pcchar1 cszPathTo)
{
	cszPathFrom;
	cszPathTo;
	return false;
}


}		//namespace monapi2

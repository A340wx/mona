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
#ifdef MONA
	#include <monapi.h>
	#include <monapi/messages.h>
#endif

#ifdef _WIN32
	#include <afxwin.h>
	#include <io.h>
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

#include "FileFn.h"
#include "Buffer.h"
#include "String.h"
#include "Memory.h"

//�f�o�b�O�̂��߂̉��}�[�u

namespace monapi2	{

//FileFn//////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::isExist(cpchar1 /*cszPath*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::isFile(cpchar1 /*cszPath*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int FileFn::getSize(cpchar1 cszPath)
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
uint FileFn::getLastModifiedTime(cpchar1 /*cszPath*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
	@date	2005/09/20	junjunn ����
*/
bool FileFn::read(cpchar1 cszPath,byte* pBufferOut,int iBufferSize)
{
#ifdef MONA
	monapi_cmemoryinfo* pMemoryInfo = monapi_call_file_read_data(cszPath,MONAPI_FALSE);
	if (! pMemoryInfo)	return false;

	MemoryFn::copy(pBufferOut,pMemoryInfo->Data,pMemoryInfo->Size);
	return true;
#else
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
	@date	2005/09/20	junjunn ����
*/
bool FileFn::read(cpchar1 cszPath,Buffer* pbufOut)
{
#ifdef MONA
	monapi_cmemoryinfo* pMemoryInfo = monapi_call_file_read_data(cszPath,MONAPI_FALSE);
	if (! pMemoryInfo)	return false;

	pbufOut->copy(pMemoryInfo->Data,pMemoryInfo->Size);
	return true;
#else
	pbufOut;cszPath;
	return false;
#endif
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
	@date	2005/09/20	junjunn ����
*/
bool FileFn::read(cpchar1 cszPath,String* pstrOut)
{
#ifdef MONA
	monapi_cmemoryinfo* pMemoryInfo = monapi_call_file_read_data(cszPath,MONAPI_FALSE);
	if (! pMemoryInfo)	return false;

	int iFileSize = pMemoryInfo->Size;
//String�n�̓T�[�r�X��'\0'�܂Ŋm�ۂ��Ă���B
	pchar1 pBuffer = pstrOut->extendBuffer(iFileSize+1);
	MemoryFn::copy(pBuffer,pMemoryInfo->Data,pMemoryInfo->Size);
	pBuffer[iFileSize] = '\0';
	return true;
#else
	FILE* pFile = fopen(cszPath,"rb");
	if (pFile)
	{
		struct _stat oStat;
		_stat(cszPath,&oStat);
		int iFileSize=oStat.st_size;
		pchar1 pBuffer = pstrOut->extendBuffer(iFileSize+1);
		fread(pBuffer,1,iFileSize,pFile);
		pBuffer[iFileSize] = '\0';
		fclose(pFile);
		return true;
	}

	return false;
#endif
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::write(cpchar1 cszPath,const byte* cpIn,int iCount)
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
bool FileFn::write(cpchar1 cszPath,const Buffer* cpbufIn)
{
	return write(cszPath,cpbufIn->getData(),cpbufIn->getSize());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::write(cpchar1 cszPath,const String* cpstrIn)
{
	return write(cszPath,(byte*)cpstrIn->getString(),cpstrIn->getLength());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::createDirectory(cpchar1 /*cszPath*/,cpchar1 /*cszDirName*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::deleteFile(cpchar1 /*cszPath*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::deleteDirectory(cpchar1 /*cszPath*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::move(cpchar1 /*cszPathFrom*/,cpchar1 /*cszPathTo*/)
{
	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool FileFn::copy(cpchar1 /*cszPathFrom*/,cpchar1 /*cszPathTo*/)
{
	return false;
}


}		//namespace monapi2

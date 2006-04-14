/**
	@file	FileFn.h
	@brief	�t�@�C���ꔭ����

	�t�@�C���ꔭ����

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_FILEFN_H
#define _MONAPI2_BASIC_FILEFN_H

#include "switch.h"
#include "Type.h"

namespace monapi2	{

const int g_iMAX_PATH = 256;		///<Windows��Ŏg����ő�p�X������

///
/**
	@brief	�t�@�C���֐����W�߂�static�N���X�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class FileFn
{
public:		//�܂��������Ȃ̂�
	static bool isExist(cpchar1 cszPath);
	static bool isFile(cpchar1 cszPath);
	static int getSize(cpchar1 cszPath);
	static uint getLastModifiedTime(cpchar1 cszPath);
	static bool read(cpchar1 cszPath,byte* pBufferOut,int iBufferSize);
	static bool read(cpchar1 cszPath,class Buffer* pbufOut);
	static bool read(cpchar1 cszPath,class String* pstrOut);

	static bool write(cpchar1 cszPath,const byte* cpIn,int iCount);
	static bool write(cpchar1 cszPath,const Buffer* cpbufIn);
	static bool write(cpchar1 cszPath,const String* cpstrIn);
	static bool createDirectory(cpchar1 cszPath,cpchar1 cszDirName);
	static bool deleteFile(cpchar1 cszPath);
	static bool deleteDirectory(cpchar1 cszPath);
	static bool move(cpchar1 cszPathFrom,cpchar1 cszPathTo);
	static bool copy(cpchar1 cszPathFrom,cpchar1 cszPathTo);
};

}	//namespace monapi2

#endif

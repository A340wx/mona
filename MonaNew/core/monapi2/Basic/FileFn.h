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
	static bool isExist(pcchar1 cszPath);
	static bool isFile(pcchar1 cszPath);
	static int getSize(pcchar1 cszPath);
	static uint getLastModifiedTime(pcchar1 cszPath);
	static bool read(pcchar1 cszPath,byte* pBufferOut,int iBufferSize);
	static bool read(pcchar1 cszPath,class Buffer* pbufOut);
	static bool read(pcchar1 cszPath,class String* pstrOut);

	static bool write(pcchar1 cszPath,const byte* cpIn,int iCount);
	static bool write(pcchar1 cszPath,const Buffer* cpbufIn);
	static bool write(pcchar1 cszPath,const String* cpstrIn);
	static bool createDirectory(pcchar1 cszPath,pcchar1 cszDirName);
	static bool deleteFile(pcchar1 cszPath);
	static bool deleteDirectory(pcchar1 cszPath);
	static bool move(pcchar1 cszPathFrom,pcchar1 cszPathTo);
	static bool copy(pcchar1 cszPathFrom,pcchar1 cszPathTo);
};

}	//namespace monapi2

#endif

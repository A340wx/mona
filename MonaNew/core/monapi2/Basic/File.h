/**
	@file	File.h
	@brief	�t�@�C���ڍב���

	�t�@�C���ڍב���

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_FILE_H
#define _MONAPI2_BASIC_FILE_H

#include "switch.h"
#include "Type.h"

#ifndef MONA
	#include <stdio.h>
#endif

namespace monapi2	{

/**
	@brief	�ڍׂȃt�@�C������BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class File
{
public:
//�R���X�g���N�^
	File()	{init();}
	File(const char* cszPath,bool bAllowWrite=false)	{init();open(cszPath,bAllowWrite);}
	~File()	{close();}

//�擾
	const char* getName() const;
	const char* getPath() const;
	int getSize() const;
	int getLastModifiedTime() const;

//����
	bool open(const char* cszPath,bool bAllowWrite=false);
	uint read(byte* pOut,uint nIndex,uint nCount) const;
	uint write(const byte* cpIn,uint nIndex,uint nCount) const;
	void close();

	void setPath(const char cszPath);


protected:
	void init() {
#ifndef MONA
		m_pFile=NULL;
#endif
	}


//���}���u
#ifndef MONA
	FILE* m_pFile;
#endif
};

}	//namespace monapi2

#endif

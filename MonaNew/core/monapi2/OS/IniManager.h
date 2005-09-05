/**
	@file	IniManager.h
	@brief	.ini�`���̃f�[�^�̃t�@�C���ւ̓��o��

	.ini�`���̃f�[�^�̃t�@�C���ւ̓��o��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_OS_INIMANAGER_H
#define _MONAPI2_OS_INIMANAGER_H

#include "../Basic/switch.h"
#include "../Basic/Type.h"
#include "../Basic/CollectionMap.h"

namespace monapi2	{

typedef StringMap<String> StringStringMap;

/**
	@brief	.ini�`���̃X�N���v�g�B �L�[���ƒl�̃y�A�œ��o�͂��s���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class IniManager
{
public:
	IniManager(pcchar1 cszPath)	{init();read(cszPath);}		///<�R���X�g���N�^
	IniManager()				{init();}					///<�R���X�g���N�^
	void init()					{m_strstrmap.initHashTable(101);}

	void read(pcchar1 cszPath);						///<�t�@�C������ǂݍ���
	void write(pcchar1 cszPath);					///<�t�@�C���ɏ�������
	void toString(String* pstrOut);					///<�����f�[�^�𕶎���`���ɂ���B


//�擾
///@name �l���Q�b�g
//@{
	bool	lookup(pcchar1 cszDir,pcchar1 cszKey,bool bDefault);
	int		lookup(pcchar1 cszDir,pcchar1 cszKey,int iDefault);
	float	lookup(pcchar1 cszDir,pcchar1 cszKey,float fDefault);
	pcchar1	lookup(pcchar1 cszDir,pcchar1 cszKey,pcchar1 cszDefault);

//@}

///@name �l���Z�b�g
//@{
	void	setAt(pcchar1 cszDir,pcchar1 cszKey	,bool bValue);
	void	setAt(pcchar1 cszDir,pcchar1 cszKey	,int iValue);
	void	setAt(pcchar1 cszDir,pcchar1 cszKey	,float fValue);
	void	setAt(pcchar1 cszDir,pcchar1 cszKey	,pcchar1 cszValue);
//@}

	const	StringStringMap* getMap(){return &m_strstrmap;}		///<�S�Ă̗v�f�����񂷂鎞�̂��߂̒��ڌĂяo��

protected:
	void	parse(pcchar1 cszContent);	///<szContent����͂��A�܂܂�Ă���"�L�[ - �l"�����o��
	bool	isLineComment(pcchar1 p);


//�����o
protected:
	StringStringMap		m_strstrmap;			///<�L�[���Ƃ��̒l�����т�����
	String				m_strCurDir;				///<���݂̃f�B���N�g��

//�L�[�ƒl��LookUp���鎞�Ɏg���o�b�t�@�BGetStr�̒l��Ԃ���悤�ɃI�u�W�F�N�g�Ƃ��Ď����Ă����B
	String				m_strValueBuffer;
};

/**
CScriptIni�Œl�̖��O�ƃL�[�����ꏏ�ɂ��邽�߂̃}�N���B���o�͂̑��ΐ����T�|�[�g

	@date	2005/08/20	junjunn �쐬
*/
#define INIMANAGER_LOOKUP2(iniManager,dir,value,defaultValue)	\
	value = (iniManager).lookup(dir,#value,defaultValue);

#define INIMANAGER_SETAT2(iniManager,dir,value)	\
	(iniManager).setAt(dir,#value,value);

#define INIMANAGER_LOOKUPSETAT2(iniManager,save,dir,value,defaultValue)	\
	if (save)	{INIMANAGER_SETAT2(iniManager,dir,value)}				\
	else		{INIMANAGER_LOOKUP2(iniManager,dir,value,defaultValue)}

}	//namespace monapi2

#endif

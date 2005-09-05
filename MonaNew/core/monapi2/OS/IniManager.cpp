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
#include "IniManager.h"
#include "../Basic/StringFn.h"
#include "../Basic/StringOther.h"
#include "../Basic/FileFn.h"

namespace monapi2	{

/**
IniManager::Write()�̎��̃\�[�g�Ɏg��

	@date	2005/08/20	junjunn �쐬
*/
class CDirKeyValue
{
public:
	String m_strDir;
	String m_strKey;
	String m_strValue;
};

/**
	@date	2005/08/20	junjunn �쐬
*/
int compareDirKeyValue(const void *p, const void *q)
{
	CDirKeyValue* pDKV1=(CDirKeyValue*)p;
	CDirKeyValue* pDKV2=(CDirKeyValue*)q;
	return (StringFn::compare(pDKV1->m_strDir,pDKV2->m_strDir));
}


//IniManager/////////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool IniManager::isLineComment(pcchar1 p)
{
	if (StringFn::isEmpty(p))		return true;

	char1 c0 = p[0];
	char1 c1 = p[1];

	if (c0=='/'  && c1=='/')		return true;
	if (c0=='#')					return true;
	if (c0=='\n')					return true;

	return false;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::read(pcchar1 cszPath)
{
//�t�@�C������ǂݏo���B
	String str;
	if (! FileFn::read(cszPath,&str))		return;

//���`�B
	str.remove('\r');

//���
	parse(str);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::parse(pcchar1 cszContent)
{
	m_strCurDir.empty();

//�s�ɕ���
	StringDivide SDLine(cszContent,"\n");
//�s������	
	for (int i=0;i<SDLine.getCount();i++)
	{
//���݂̍s�B
		pcchar1 pLine = SDLine.getAt(i);
//�R�����g�s�Ȃ�X�L�b�v
		if (isLineComment(pLine))		continue;

//�f�B���N�g���w��̍s�炵��
		if (pLine[0]=='[')
		{
//�f�B���N�g�����̏��߂ƏI���B
			pcchar1 pStart = pLine+1;
			pcchar1 pEnd = StringFn::find(pLine,']');
			if (pEnd==NULL)	pEnd = StringFn::getEnd(pStart);	//���J�b�R���Ȃ��̂͂����������Ȃ�Ƃ��C������B
			m_strCurDir.copy(pStart,pEnd-pStart);
		}
//�l
		else
		{
//Key=Value�`������؂�B
			StringDivide SDKeyValue(pLine,"=");
//�L�[��
			String strKey=SDKeyValue.getAt(0);
//�擪�̋󔒂���菜���B
			strKey.remove(" ");		//��
			strKey.remove("	");		//�^�u

//�l
			String strValue;
			if (SDKeyValue.getCount()>=2)
			{
//	strTest= "a=b";
//�Ȃǒl�ɂ�=�������Ă��܂��Ă��鍢�����P�[�X���l�����Ďc�����ɂ�������B
				String strValueUnified=SDKeyValue.getAt(1);
				for (int i=2;i<SDKeyValue.getCount();i++)
				{
					strValueUnified+="=";
					strValueUnified+=SDKeyValue.getAt(i);
				}

//�擪��������B
				pcchar1 pStart = strValueUnified;
//�擪�̋󔒂��X�L�b�v�B
				while (*pStart==' ' || *pStart=='	')	pStart++;

//�Ō��������B
				pcchar1 pEnd=pStart;
//="�`"�`����������Ή�����"��������B
				if (*pStart=='"')
				{
					pStart++;
					pEnd=StringFn::find(pStart,'"');
					if (pEnd==NULL)	pEnd = StringFn::getEnd(pStart+1);	//���J�b�R���Ȃ��̂͂����������Ȃ�Ƃ��C������B
				}
//=�`�`����������;���s�̏I����������B
				else
				{
					while (! (*pEnd==';' || *pEnd=='\0'))	pEnd++;

				}

//�l�����o���B
				int iLen=pEnd-pStart;
				pchar1 pBuffer=(pchar1)strValue.extendBuffer(iLen+1);
				StringFn::copy(pBuffer,pStart,iLen);
			}

//�f�B���N�g���{�L�[���ō��t���L�[���B
			String strKeyWhole;
			strKeyWhole.format("%s/%s",m_strCurDir.getString(),strKey.getString());
			m_strstrmap.setAt(strKeyWhole,strValue);
		}
	}
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::toString(String* pstrOut)
{
	pstrOut->empty();
	int iCount=m_strstrmap.getCount();
	if (iCount==0)		return;

//�\�[�g���邽�ߔz��ɒu��������
	CDirKeyValue* paDKV=new CDirKeyValue[iCount];

	int i=0;
	mapposition pos = m_strstrmap.getStartPosition();
	String strKey,strValue;
	while(pos)
	{
		m_strstrmap.getNext(&pos,&strKey,&strValue);
		StringDivide SD(strKey,"/");
		paDKV[i].m_strDir=SD.getAt(0);
		paDKV[i].m_strKey=SD.getAt(1);
		paDKV[i].m_strValue=strValue;
		i++;
	}

//�\�[�g
	quicksort(paDKV,iCount,sizeof(CDirKeyValue),compareDirKeyValue);

//������ɏo��
	String strLine;
	pcchar1 cszLastDir="";
	for (i=0;i<iCount;i++)
	{
//�V�����f�B���N�g���ɂȂ�����f�B���N�g���Z�N�V������}���B
		if (! StringFn::isEqual(cszLastDir,paDKV[i].m_strDir))
		{
			strLine.format("[%s]\n",paDKV[i].m_strDir.getString());
			*pstrOut+=strLine;
			cszLastDir = paDKV[i].m_strDir;
		}
		strLine.format("%s=%s\n",paDKV[i].m_strKey.getString(),paDKV[i].m_strValue.getString());
		*pstrOut+=strLine;
	}

	delete[] paDKV;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::write(pcchar1 cszPath)
{
	String str;
	toString(&str);
	FileFn::write(cszPath,&str);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool IniManager::lookup(pcchar1 cszDir,pcchar1 cszKey,bool bDefault)
{
	pcchar1 p=lookup(cszDir,cszKey,"");
	return (StringFn::isEmpty(p))?bDefault:(StringFn::toInt(p)!=0);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int	IniManager::lookup(pcchar1 cszDir,pcchar1 cszKey,int iDefault)
{
	pcchar1 p=lookup(cszDir,cszKey,"");
	return (StringFn::isEmpty(p))?iDefault:StringFn::toInt(p);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
float IniManager::lookup(pcchar1 cszDir,pcchar1 cszKey,float fDefault)
{
	pcchar1 p=lookup(cszDir,cszKey,"");
	return (StringFn::isEmpty(p))?fDefault:(float)StringFn::toFloat(p);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
pcchar1	IniManager::lookup(pcchar1 cszDir,pcchar1 cszKey,pcchar1 cszDefault)
{
	String	strFullKey;
	strFullKey.format("%s/%s",cszDir,cszKey);

	if (m_strstrmap.lookup(strFullKey,&m_strValueBuffer))
	{
		return m_strValueBuffer;
	}

	return cszDefault;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::setAt(pcchar1 cszDir,pcchar1 cszKey,bool bValue)
{
	setAt(cszDir,cszKey,bValue);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::setAt(pcchar1 cszDir,pcchar1 cszKey,int iValue)
{
	char1 szValue[32];
	StringFn::toString(szValue,iValue);

	setAt(cszDir,cszKey,szValue);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::setAt(pcchar1 cszDir,pcchar1 cszKey,float fValue)
{
	char1 szValue[32];
	StringFn::format(szValue,"%f",fValue);

	setAt(cszDir,cszKey,szValue);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void IniManager::setAt(pcchar1 cszDir,pcchar1 cszKey,pcchar1 cszValue)
{
	String strFullKey;
	strFullKey.format("%s/%s",cszDir,cszKey);

	m_strstrmap.setAt(strFullKey,cszValue);
}

}	//namespace monapi2

/**
	@file	String.h
	@brief	�ėp������N���X

�ėp������N���X�B.

�f�[�^�͓����ɒ��ڎ��̂ł͂Ȃ�StringData* m_pStringData�ƌ����`�ŕʂ̏��ւ̎Q�Ƃŕێ�����B
����͖��ʂȃR�s�[��h�����߁B
�Ⴆ��
	String a="ABC";
	String b=a;
�Ƃ����Ƃ��Q�ƂȂ��̐��f�[�^����a�ɂ�b�ɂ�"ABC"����d�ɑ��݂�����������������
�܂��R�s�[���s����ۂ�CPU���H����B
����ɒl�ɂ��󂯓n�����s����ΑS�Ă̒��r�o�߂ɃR�s�[���쐬����Ă͎̂Ă�ꋰ�낵���s�����B
(�֐��Ń|�C���^�Q�Ƃ��󂯓n������悤�ɂ���Ε��ʂ͒l�̎󂯓n���͂��Ȃ��ōςނ̂���
StringList�̒��Ŏg����String�Ȃǂł͒l�ɂ��󂯓n�����g���Ď������Ȃ��ƕs�\�B)

�Q�ƗL��������Ƃ��̏ꍇb��a�̃f�[�^���Q�Ƃ��邾���Ȃ̂ŃR�s�[�͂��Ă��Ȃ����ׂ��قƂ�ǂȂ��B
a�̃f�[�^��ύX����ۂɂ͂��̎��ɏ��߂�a�̃f�[�^�̃R�s�[�����b����Ɨ������悤�ɍ���Ă���̂�
a�̕ύX��b�ɉe�����y�΂��Ȃ��Ȃ�B

�f�[�^�͂��̕��@�ŕʂ̏��ւ̎Q�Ƃɂ��ĎQ�ƃJ�E���g�ŊǗ����K�x�[�W�R���N�V�����݂����Ɉ�����
�l�󂯓n���̍ۂɂ����ʂȃR�s�[���Ȃ��Ȃ��C�Ɍ����悭�Ȃ�B

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_STRING_H
#define _MONAPI2_BASIC_STRING_H

#include "Switch.h"
#include "Type.h"
#include "VariableArgument.h"

namespace monapi2
{

/**
	@brief	class String���Q�Ƃ��镶������f�[�^�B
	@date	2005/08/20	junjunn �쐬
*/
class StringData
{
public:
///�R���X�g���N�^
	StringData();
///�Q�ƃJ�E���g�A�b�v�B���̕ϐ����Q�Ƃ��Ă���Ƌ�����B
	void registerRef();
///�Q�ƃJ�E���g�_�E���B���̕ϐ����Q�Ƃ��I������Ƌ�����B�Q�ƃJ�E���g��0�ɂȂ�������ŁB
	void unregisterRef();

///�ǂ�����String�������ȊO�ɂ�����Q�Ƃ��Ă��邩�B
///�Q�Ƃ���Ă��Ȃ����(! Locked())���R�ɕύX�\����
///�Q�Ƃ���Ă����(Locked())�ύX�ɂ͐V�����o�b�t�@�����K�v������B
	bool isLocked()		{return getRefCount()>1;}


protected:
	int getRefCount()	{return m_iRefCount;}

public:
	pchar1	m_szData;		///<�f�[�^�{��
	uint	m_nLength;		///<�����񂪎g�p���Ă���傫���B'\0'�͊܂߂Ă��Ȃ��B����Ė{���͂���+1�m�ۂ��Ă���B
	uint	m_nSize;		///<�o�b�t�@���m�ۂ��Ă���傫���B
	int		m_iRefCount;	///<�Q�ƃJ�E���g

/*
m_nSize��m_nLength�̉��œ�̒��������邩��₱�������ۂ���
m_nLength��'\0'�܂ł̕�����̒�����m_nSize�͊m�ۂ��Ă��郁�����̑傫���B

�v�����ꂽ������̒�����������������new���Ċm�ۂ���ƌ��1�����ł�+=�����邽�т�
delete����new���Ă̌J��Ԃ��Ō����������B
����ăo�b�t�@�̈�͗v�����ꂽ�����͑����傫�߂ɂƂ��Ă��������������B
�����當���񒷂Ɨ̈撷�̓�̒l���ʁX�ɂ���B

��̓I�ɂ͂����ł�1,2,4,8,16,32�E�E�E�Ɣ{�X�ő��₵��
�v�����ꂽ�T�C�Y�𒴂����ԋ߂������g���Ă���B

�Ⴆ��CStirng str = "ABCDEFGHI"�Ɨ����Ƃ��͕K�v�Ȓ�����9+1�o�C�g(+1��'\0'�̕�)�B
���̎�str�̓����ł�16�o�C�g�̃o�b�t�@���m�ۂ����̒���"ABCDEFGHI"���i�[����B
�����m_nLength=9�Am_nSize=16�ɂȂ��Ă�B

�]����7�o�C�g�͕����񂪌ォ�瑫����鎞�Ɏg����B
*/
};


/**
	@brief	�ėp������N���X�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class String
{
public:
///�R���X�g���N�^�ƃf�X�g���N�^
	String();									///<�R���X�g���N�^
	String(int iInitialBufferLength);			///<�R���X�g���N�^
	String(cpchar1 cszInitialString);			///<�R���X�g���N�^
	String(const String& refInitialString);		///<�R���X�g���N�^
	~String();									///<�f�X�g���N�^

///�擾
	cpchar1	getString()	const{return m_pStringData->m_szData;}			///<������𓾂�B
			operator cpchar1()	const{return getString();}				///<�L���X�g���Z�q�B
	uint	getLength()	const{return m_pStringData->m_nLength;}			///<������̒����𓾂�('\0'�͊܂܂Ȃ�)�B
	uint	getSize()	const{return m_pStringData->m_nSize;}			///<������̗̈�T�C�Y�𓾂�B
	bool	isEmpty()	const{return getLength()==0;}		///<�����񂪋󂩂ǂ���
	bool	isEqual(cpchar1 csz) const;						///<���ꂩ�ǂ�����r�B
	bool	operator==(cpchar1 csz) const;					///<���ꂩ�ǂ�����r�B
	bool	operator!=(cpchar1 csz) const;					///<�񓯈ꂩ�ǂ�����r�B
	bool	isEqualNoCase(cpchar1 csz) const;				///<���ꂩ�ǂ�����r�B�召���������B
	char1	getAt(uint n) const;							///<�w��̃C���f�b�N�X�̕�����Ԃ��B
	int		find(char1 cFind,uint nStart=0) const;			///<�����B
	int		find(cpchar1 cszFind,uint nStart=0) const;		///<�����B
	int		findReverse(char1 cFind) const;					///<�t�����B
	int		findReverse(cpchar1 cszFind) const;				///<�t�����B
	void	getLeft(String* pstrOut,uint nCount) const;		///<���̐���������V����String���\�z�B
	void	getRight(String* pstrOut,uint nCount) const;	///<�E�̐���������V����String���\�z�B
	void	getMiddle(String* pstrOut,uint nStart,uint nCount) const;	///<�����̐���������V����String���\�z�B

	String	join(cpchar1 csz) const;						///<�A�����ĐV����String���\�z�B
	String	operator+(cpchar1 csz) const;					///<�A�����ĐV����String���\�z�B

//����
	void copy(cpchar1 csz,int iCount=-1);					///<����B
	String& operator=(cpchar1 csz);							///<����B
	void copy(const String* pstr);							///<����B
	String& operator=(const String& rstr);					///<����B
	void joinSelf(cpchar1 csz);								///<�����ɒ��ژA���B
	String& operator+=(cpchar1 csz);						///<�����ɒ��ژA���B
	void empty();											///<��ɂ���B
	void format(cpchar1 cszFormat,...);						///<sprintf�`���ŕ���������B
	void formatJoinSelf(cpchar1 cszFormat,...);				///<sprintf�`���ŕ����������čŌ�ɂ�������B
	bool setAt(uint n,char1 c);								///<�w��̃C���f�b�N�X�ɕ������Z�b�g�B
	int replace(char1 cFrom,char1 cTo);						///<�u������
	int replace(pchar1 cszFrom,pchar1 cszTo);				///<�u������
	int remove(char1 cRemove);								///<����
	int remove(pchar1 cszRemove);							///<����
	void insert(pchar1 cszIn,uint nIndex);					///<�}��
	void cut(uint nIndex,uint nCount);						///<�폜
	void toUpper();											///<�啶���ϊ�
	void toLower();											///<�������ϊ�
	pchar1 getBuffer();										///<�����o�b�t�@�𒼐ړ���B
	pchar1 extendBuffer(uint nLength);						///<�����o�b�t�@���g���B�|�C���^������B
	void recalculateLength(int iLength=-1);					///<getBuffer,extendBuffer�ł�����ꂽ����������̒������Čv�Z�B


protected:
///������
	void init();
///format�Ȃǂ̓��������B
	void formatV(cpchar1 cszFormat,vapointer vl);
///nLength�͊i�[�\���B
	bool isContainable(uint nLength);
///�������Z�b�g����
	void setLength(uint n)		{m_pStringData->m_nLength=n;}
///�����̎Q�Ƃ��Ă���m_pStringData������B
	void releaseBuffer();
///getBuffer�̓��[�U�[���Ăяo���A�o�b�t�@�̃R�s�[�����Ȃ���o�b�t�@�ւ̃A�N�Z�X�𓾂郁�\�b�h�B
///�������͒��ڃA�h���X���Ăяo���B���O�����Ă邾���ŗp�r�͈Ⴄ�Ǝv�������������B
	pchar1 getBufferDirect()	{return m_pStringData->m_szData;}
///�Q�Ƃւ̃A�N�Z�X�B
	StringData* getStringData()	const {return m_pStringData;}


//�����o�b�t�@����

/**
�o�b�t�@�̓��e�������珑��������̂ŏ��������\�ȗ̈��v������B
�Q�ƃJ�E���g�������ȊO�ɂȂ��A���T�C�Y���\������Ȃ玩���̃o�b�t�@�����̂܂ܗ��p���邵�A
��������Q�Ƃ���ă��b�N����Ă���Ȃ�V�����̈�����B
*/
	pchar1 requestModifiableBuffer(uint nLength,bool bKeepOriginalData);

/**
�Œ��nMinLength�̃o�b�t�@�T�C�Y���m�ۂ���B
�o�b�t�@�̃T�C�Y������Ȃ��Ȃ�g�����邵�A���ł�nMinLength�������Ă���Ȃ牽�����Ȃ��B
�o�b�t�@�̑傫�����l�����Ď���createNewBuffer���Ăяo���B
@memo �����͂܂������ł͂Ȃ��B��ǂ݂̂��ߕK�v�ȏ�̗̈�𓾂�@�\���������B

extendBuffer�Ɩ��O�����Ă��邪�������̓��[�U�[���Ăяo���A
�o�b�t�@�̃R�s�[�����Ȃ���o�b�t�@�ւ̃A�N�Z�X�𓾂郁�\�b�h�B
�������͒��ڑ��삷��B���O�����Ă邾���ŗp�r�͈Ⴄ�Ǝv�������������B
*/
	pchar1 extendBufferDirect(uint nMinLength,bool bKeepOriginalData);

/**
BufferLen�̒������m�ۂ���BiBufferLen��'\0'���܂܂Ȃ�������̒����B
createNewBuffer()�ŏ����'\0'�𑫂��������Ă����B

�����̊֐��̗���Ƃ��Ă�
	requestModifiableBuffer
	��	(���݂̃o�b�t�@��������Q�Ƃ���Ă��Ȃ����ڎg���邩�A
	���@ ����Ƃ��Q�Ƃ���Ă���̂ŐV�������ׂ������f�B)
	��
	extendBufferDirect
	��	(�v������钷������ǂ݂̂��ߑ��߂Ɍv�Z����B�X�L�b�v�B)
	��
	createNewBuffer
		(���ۂɎw�肳�ꂽ�傫�������)
*/
	pchar1 createNewBuffer(int iSizeWithoutNull,bool bKeepOriginalData=false);



//�����o
protected:
/**
�ψ������̈����ɂ��āB

���i��operator cpchar1()�������̂�
	cpchar1 p = string;
�Ƃ������Ă������Ő�����String����cpchar1�ւ̃L���X�g�������������^�ɕϊ�����܂���
�ψ����g�p���ɂ͌^�̏�񂪏��ł��܂�����
	StringFn::format(szBuffer,"%s",string->getString());
�Ɩ����I�Ɏw�肵�Ă��������B
	StringFn::format(szBuffer,"%s",string);
�ł̓o�O��܂��B

MFC��CString�^�ɂ͉ψ�������
	sprintf(szBuffer,"%s",string);
�̂悤�ɏ����Ă�������char*������Ƃ��ďo�͂����@�\����������Ă��܂��B

����͑���CString�{�̂�const char* m_p�����������o�Ɏ������ʂ̕�����ƌ����ڂ͑S������ɁA
CString�̂��̑��{�̃f�[�^��(m_p���w�����ʂ�NUL������ + �{�̃����o���)�̂悤��
������̏I���Ƀ����o�f�[�^���������A�Q�Ƃ���Ƃ���
�im_p + m_p�̒����j�Œ��ׂ�悤�Ȃ��Ȃ�ϑ��I�Ȓu���������Ă��邩�炾�Ǝv���܂��B

�����ł������ł��Ȃ����͂Ȃ��ł��������R�[�h�I�ɂ͂��Ȃ�̔�����
�ψ������̎����L���X�g�����ׂ̈����ɂ���Ȕ������鉿�l������̂��E�E�E���Ęb��
�Ƃ肠���������_�ł͂����Ď������Ă��܂���B

���Ȃ݂ɂ��̃N���X�ɂ���������ocpchar1 m_szDataPointer�����Ă����m_pStringData->m_szData
��ݒ肵�Ă������@�ɂ����Stirng�̐��f�[�^��������f�[�^���w���悤�ɂȂ�̂ŃL���X�g�͐������܂����A
�ψ����̕���VAP_ADVANCE(p,sizeof(char*))�Ȃǂ����s����̂Ō��ǖ����ł��E�E�E
*/

///�f�[�^�{��
	class StringData* m_pStringData;
};

}	//namespace monapi2

#endif

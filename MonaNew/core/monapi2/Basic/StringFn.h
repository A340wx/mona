/**
	@file	StringFn.h
	@brief	������֘A

	������֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_STRINGFN_H
#define _MONAPI2_BASIC_STRINGFN_H

#include "Switch.h"
#include "Type.h"
#include "VariableArgument.h"

namespace monapi2	{

///������֐����W�߂�static�N���X
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class StringFn
{
public:
//�擾
	static inline	bool	isEmpty(pcchar1 cszSource);										///<�󂩂ǂ����B
	static inline	bool	isEqual(pcchar1 cszP,pcchar1 cszQ,int iSearchCount=-1);			///<�������ꔻ��B
	static inline	bool	isEqualNoCase(pcchar1 cszP,pcchar1 cszQ,int iSearchCount=-1);	///IsEqual�̑啶���������֌W�Ȃ��o�[�W�����B
	static			int		findDiff(pcchar1 cszP,pcchar1 cszQ,int iSearchCount=-1);			///<�������r�BiSearchCount==-1�̏ꍇ�͑S����r�A����ȊO�̏ꍇ�͎w�肵�������܂ŁB
	static			int		findDiffUpto(pcchar1 cszP,pcchar1 cszQ,pcchar1 cszPUpto);		///<�������r�BcszP<cszPUpto�܂ŁB
	static			int		findDiffNoCase(pcchar1 cszP,pcchar1 cszQ,int iSearchCount=-1);	///<compare�̑啶���������֌W�Ȃ��o�[�W�����B
	static			int		compare(pcchar1 cszP,pcchar1 cszQ,int iSearchCount=-1);			///<�A���t�@�x�b�g���ɂǂ��炪�O�����r�B
	static			uint	getLength(pcchar1 cszSource);									///<������̒����B
	static			uint	getLength(pcchar2 cszSource);									///<������̒����B
	static 			pchar1	find(pcchar1 cszSource,char1 cFind,int iSearchCount=-1);		///<cszSource�̂Ȃ�����cFind��������B
	static			pchar1	find(pcchar1 cszSource,pcchar1 cszFind,int iSearchCount=-1);	///<cszSource�̂Ȃ�����cszFind��������B
	static			pchar1	findUpto(pcchar1 cszSource,char1 cFind,pcchar1 cszSourceUpto);	///<cszSource�̂Ȃ�����cFind��������B
	static			pchar1	findUpto(pcchar1 cszSource,pcchar1 cszFind,pcchar1 cszSourceUpto);	///<cszSource�̂Ȃ�����cszFind��������B
	static			pchar1	findReverse(pcchar1 cszSource,char1 cFind,int iSearchCount=-1);
	static			pchar1	findReverse(pcchar1 cszSource,pcchar1 cszFind,int iSearchCount=-1);
	static			pcchar1	getEnd(pcchar1 cszSource);
	static			int		getCountAppear(pcchar1 cszSource,char1 cFind,int iSearchCount=-1);		///<cszSource��cFind������o�Ă������B
	static			int		getCountAppear(pcchar1 cszSource,pcchar1 cszFind,int iSearchCount=-1);	///<cszSource��cszFind������o�Ă������B
	static			int		toInt(pcchar1 cszSource,int iBase=10,pcchar1* pcszEnd=NULL);			///<cszSource����n�܂镶����𐔒l�ɉ��߂���BcszEnd�͖��������ĖႤ�A�h���X�B
	static			float	toFloat(pcchar1 csz,pcchar1* pcszEnd=NULL);						///<cszSource����n�܂镶����𐔒l�ɉ��߂���BcszEnd�͖��������ĖႤ�A�h���X�B
	static inline	pchar1	findEnd(pcchar1 pAt);											///<{return pAt+strlen(pAt);}
	static			int		duplicate(pchar1* pszOut,pcchar1 cszIn);						///<�q�[�v�ɃR�s�[������ĕԂ��B
	static			int		getReplaceLength(pcchar1 cszIn,pcchar1 cszFrom,pcchar1 cszTo);	///<�u��������̒��������߂�B

	static inline	void	empty(pchar1 szOut);										///<��ɂ���B
	static			int		copy(pchar1 szOut,pcchar1 cszIn,int iCopyCount=-1);			///<������R�s�[�B�߂�l�̓R�s�[�����������B
	static			int		copy(pchar2 szOut,pcchar2 cszIn,int iCopyCount=-1);			///<������R�s�[�B�߂�l�̓R�s�[�����������B
	static inline	int		join(pchar1 szOut,pcchar1 cszIn,int iCopyCount=-1);			///<������A���B�߂�l�̓R�s�[�����������B
	static			int		format(pchar1 szBuffer,pcchar1 cszFormat,...);				///<sprintf�`���ŕ���������B
	static			int		formatV(pchar1 szBuffer,pcchar1 cszFormat,vapointer vap);	///<sprintf�`���ŕ���������B
	static			int		toString(pchar1 szBuffer,int iTarget,int iBase=10,bool bCapital=false,int iWidth=0);
	static			int		replace(pchar1 szOut,char1 cFrom,char1 cTo);				///<�����u������chr�ŁBszSrc�ɂ͒u��������̕�����̒������i�[�ł��邾���̃o�b�t�@���Ȃ���΂Ȃ�Ȃ��B
	static			int		replace(pchar1 szOut,pcchar1 cszIn,pcchar1 cszFrom,pcchar1 cszTo,int iFirstAppear=-1);		///<�����u�������B
	static			int		replace(pchar1* pszOut,pcchar1 cszIn,pcchar1 cszFrom,pcchar1 cszTo);			///<�����u�������B
	static			int		replace(class String* pstrOut,pcchar1 cszIn,pcchar1 cszFrom,pcchar1 cszTo);		///<�����u�������B
	static			int		replace(pchar1 szInOut,pcchar1 cszFrom,pcchar1 cszTo);		///<�����u������chr�ŁBszSrc�ɂ͒u��������̕�����̒������i�[�ł��邾���̃o�b�t�@���Ȃ���΂Ȃ�Ȃ��B
	static			int		remove(pchar1 szOut,char1 cRemove);							///<cRemove��szSrc�����菜���B
	static	inline	int		remove(pchar1 szOut,pcchar1 cszRemove);						///<cszRemove��szSrc�����菜���B
	static			void	toLower(pchar1 szSource);									///<szSource�S�����������ɕϊ��B
	static			void	toUpper(pchar1 szSource);									///<szSource�S����啶���ɕϊ��B


//API�Ƃ��Ă͌��J���Ă��Ȃ����B
public:
//ToInt��ToFloat�̃T�u���[�`���BcszSource����n�܂镶�����int�ɒ�������������̖�����pstrEnd�ɓ����B
	static int getIntAt(pcchar1 cszSource,int iBase,pcchar1* pcszEnd);
	static int estimateVALength(pcchar1 cszFormat,vapointer vap);		///<sprintf�`���ŕ���������B
	static char toString(int iTarget,bool bCapital=false);
};


}	//namespace monapi2

#include "StringFnInline.h"

#endif

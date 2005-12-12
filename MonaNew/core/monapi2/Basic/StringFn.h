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
	static inline	bool	isEmpty(cpchar1 cszSource);										///<�󂩂ǂ����B
	static inline	bool	isEqual(cpchar1 cszP,cpchar1 cszQ,int iSearchCount=-1);			///<�������ꔻ��B
	static inline	bool	isEqualNoCase(cpchar1 cszP,cpchar1 cszQ,int iSearchCount=-1);	///IsEqual�̑啶���������֌W�Ȃ��o�[�W�����B
	static			int		findDiff(cpchar1 cszP,cpchar1 cszQ,int iSearchCount=-1);			///<�������r�BiSearchCount==-1�̏ꍇ�͑S����r�A����ȊO�̏ꍇ�͎w�肵�������܂ŁB
	static			int		findDiffUpto(cpchar1 cszP,cpchar1 cszQ,cpchar1 cszPUpto);		///<�������r�BcszP<cszPUpto�܂ŁB
	static			int		findDiffNoCase(cpchar1 cszP,cpchar1 cszQ,int iSearchCount=-1);	///<compare�̑啶���������֌W�Ȃ��o�[�W�����B
	static			int		compare(cpchar1 cszP,cpchar1 cszQ,int iSearchCount=-1);			///<�A���t�@�x�b�g���ɂǂ��炪�O�����r�B
	static			uint	getLength(cpchar1 cszSource);									///<������̒����B
	static			uint	getLength(cpcharv cszSource);									///<������̒����B
	static 			pchar1	find(cpchar1 cszSource,char1 cFind,int iSearchCount=-1);		///<cszSource�̂Ȃ�����cFind��������B
	static			pchar1	find(cpchar1 cszSource,cpchar1 cszFind,int iSearchCount=-1);	///<cszSource�̂Ȃ�����cszFind��������B
	static			pchar1	findUpto(cpchar1 cszSource,char1 cFind,cpchar1 cszSourceUpto);	///<cszSource�̂Ȃ�����cFind��������B
	static			pchar1	findUpto(cpchar1 cszSource,cpchar1 cszFind,cpchar1 cszSourceUpto);	///<cszSource�̂Ȃ�����cszFind��������B
	static			pchar1	findReverse(cpchar1 cszSource,char1 cFind,int iSearchCount=-1);
	static			pchar1	findReverse(cpchar1 cszSource,cpchar1 cszFind,int iSearchCount=-1);
	static			cpchar1	getEnd(cpchar1 cszSource);
	static			int		getCountAppear(cpchar1 cszSource,char1 cFind,int iSearchCount=-1);		///<cszSource��cFind������o�Ă������B
	static			int		getCountAppear(cpchar1 cszSource,cpchar1 cszFind,int iSearchCount=-1);	///<cszSource��cszFind������o�Ă������B
	static			int		toInt(cpchar1 cszSource,int iBase=10,cpchar1* pcszEnd=NULL);			///<cszSource����n�܂镶����𐔒l�ɉ��߂���BcszEnd�͖��������ĖႤ�A�h���X�B
	static			float	toFloat(cpchar1 csz,cpchar1* pcszEnd=NULL);						///<cszSource����n�܂镶����𐔒l�ɉ��߂���BcszEnd�͖��������ĖႤ�A�h���X�B
	static inline	pchar1	findEnd(cpchar1 pAt);											///<{return pAt+strlen(pAt);}
	static			int		duplicate(pchar1* pszOut,cpchar1 cszIn);						///<�q�[�v�ɃR�s�[������ĕԂ��B
	static			int		getReplaceLength(cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo);	///<�u��������̒��������߂�B

	static inline	void	empty(pchar1 szOut);										///<��ɂ���B
	static			int		copy(pchar1 szOut,cpchar1 cszIn,int iCopyCount=-1);			///<������R�s�[�B�߂�l�̓R�s�[�����������B
	static			int		copy(pchar2 szOut,cpchar2 cszIn,int iCopyCount=-1);			///<������R�s�[�B�߂�l�̓R�s�[�����������B
	static inline	int		join(pchar1 szOut,cpchar1 cszIn,int iCopyCount=-1);			///<������A���B�߂�l�̓R�s�[�����������B
	static			int		format(pchar1 szBuffer,cpchar1 cszFormat,...);				///<sprintf�`���ŕ���������B
	static			int		formatV(pchar1 szBuffer,cpchar1 cszFormat,vapointer vap);	///<sprintf�`���ŕ���������B
	static			int		toString(pchar1 szBuffer,int iTarget,int iBase=10,bool bCapital=false,int iWidth=0);
	static			int		replace(pchar1 szOut,char1 cFrom,char1 cTo);				///<�����u������chr�ŁBszSrc�ɂ͒u��������̕�����̒������i�[�ł��邾���̃o�b�t�@���Ȃ���΂Ȃ�Ȃ��B
	static			int		replace(pchar1 szOut,cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo,int iFirstAppear=-1);		///<�����u�������B
	static			int		replace(pchar1* pszOut,cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo);			///<�����u�������B
	static			int		replace(class String* pstrOut,cpchar1 cszIn,cpchar1 cszFrom,cpchar1 cszTo);		///<�����u�������B
	static			int		replace(pchar1 szInOut,cpchar1 cszFrom,cpchar1 cszTo);		///<�����u������chr�ŁBszSrc�ɂ͒u��������̕�����̒������i�[�ł��邾���̃o�b�t�@���Ȃ���΂Ȃ�Ȃ��B
	static			int		remove(pchar1 szOut,char1 cRemove);							///<cRemove��szSrc�����菜���B
	static	inline	int		remove(pchar1 szOut,cpchar1 cszRemove);						///<cszRemove��szSrc�����菜���B
	static			void	toLower(pchar1 szSource);									///<szSource�S�����������ɕϊ��B
	static			void	toUpper(pchar1 szSource);									///<szSource�S����啶���ɕϊ��B


//API�Ƃ��Ă͌��J���Ă��Ȃ����B
public:
//ToInt��ToFloat�̃T�u���[�`���BcszSource����n�܂镶�����int�ɒ�������������̖�����pstrEnd�ɓ����B
	static int getIntAt(cpchar1 cszSource,int iBase,cpchar1* pcszEnd);
	static int estimateVALength(cpchar1 cszFormat,vapointer vap);		///<sprintf�`���ŕ���������B
	static char toString(int iTarget,bool bCapital=false);				///<0�`15��'0'�`'9'�A'A'�`'F'�ɂ���B
	static void toStringFloatPlain(pchar1 szBuffer,double d);			////<d�𕶎���ɂ���B1.234e+45�Ƃ��̌`���ł͂Ȃ�1.234�Ƃ��̃V���v���Ȍ`�����B�傫�����͕\�������E�E�E
};


}	//namespace monapi2

#include "StringFnInline.h"

#endif

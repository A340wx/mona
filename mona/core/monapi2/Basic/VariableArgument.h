/**
	@file	VariableArgument.h
	@brief	�ψ����̎�舵��

	�ψ����̎�舵��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_VARIABLEARGUMENT_H
#define _MONAPI2_BASIC_VARIABLEARGUMENT_H

namespace monapi2
{

/**
	@brief	�ψ������y�Ɉ������߂̃}�N���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
typedef	char*	vapointer;
#define VAPOINTER_SET_START(vap,lastArgument)	(void)((vap)=(vapointer)&(lastArgument)+sizeof(lastArgument))
#define VAPOINTER_ADVANCE(vap,type)				((type*)(vap+=sizeof(type)))[-1]

}		//namespace monapi2

#endif

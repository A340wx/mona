/**
    @file  Type.h
    @brief ��{�^�Etypedef

    ��{�^�Etypedef

	License=Mona License
	@version $Revision$
	@date   update:$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_TYPE_H
#define _MONAPI2_BASIC_TYPE_H

#include "switch.h"

namespace monapi2
{

/**
	@brief	�^�BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/

/**
�^�̍l���ɂ͌Œ蕝�Ɖϕ��Ƃ�����B
��̌^�̍l���̏ڍׂɂ��Ă�monapi2���t�@�����X�ŁB
*/

//�ϕ��B
//	typedef	signed int				int;		///<OS�ˑ�singned int
typedef	unsigned int			uint;		///<OS�ˑ�unsigned int

//�Œ蕝�B
typedef	signed char				int8;		///<1�o�C�g���Œ��signed
typedef	signed short			int16;		///<2�o�C�g���Œ��signed
typedef	signed int				int32;		///<4�o�C�g���Œ��signed
typedef	unsigned char			uint8;		///<1�o�C�g���Œ��unsigned
typedef	unsigned short			uint16;		///<2�o�C�g���Œ��unsigned
typedef	unsigned int			uint32;		///<4�o�C�g���Œ��unsigned

//�Œ蕝�̈�ʓI�Ɏg����ʖ��B
typedef	uint8					byte;		///<uint8�̕ʖ�
typedef	uint16					word;		///<uint16�̕ʖ�
typedef	uint32					dword;		///<uint32�̕ʖ��B�I�t�Z�b�g(�A�h���X)���L�q����Ӗ��ł̂Ƃ��Ȃǂɂ悭�g����B


/**
bool��int�B
�Ȃ�bool�Ȃ̂�int�Ȃ̂��H�ƌ����΃v���O�����̂قƂ�ǂ̕ϐ���int�^�Ȃ̂�
bool���g�������{���͑S����int�œ��ꂷ�����
int��bool�܂���bool��int�ւ̈ÖٓI�ȃL���X�g���Z���Ȃ��Ȃ葬���Ȃ�̂ŁB
�����Ƃ��v���O�����S�̂��炷��Ɣ��X���鎞�Ԃ��낤��
Y/N�̓���͈Ӗ��I��bool�ŏ����̂��l�I�ɍD���Ȃ̂Ŏ��͂��܂�g���Ă܂��񂪁E�E�E
*/
typedef int 					booli;


//�Œ蕝
typedef	char					char1;			///<1�o�C�g�����B�{����unsigned�Ȃ񂾂���signed�����y�������ĂăR���p�C���ł��������₷���̂�signed�ɂ��Ƃ��B
typedef	unsigned short			char2;			///<2�o�C�g����
typedef	unsigned int			char4;			///<4�o�C�g����

typedef char1*					pchar1;			///<�W��������ւ̃|�C���^
typedef const char1*			cpchar1;		///<const�W��������ւ̃|�C���^
typedef char2*					pchar2;			///<2�o�C�g������ւ̃|�C���^
typedef const char2*			cpchar2;		///<const2�o�C�g������ւ̃|�C���^
typedef char4*					pchar4;			///<4�o�C�g������ւ̃|�C���^
typedef const char4*			cpchar4;		///<const4�o�C�g������ւ̃|�C���^

//�ϕ�
typedef	char4					charv;			///<�W�������B
typedef charv*					pcharv;			///<�W��������ւ̃|�C���^
typedef const charv*			cpcharv;		///<const�W��������ւ̃|�C���^

#ifndef NULL
	#define NULL 0
#endif


/**
	64�r�b�g�ϐ����G�~�����[�g����B�R�[�h�������J�̖͂��ŕK�v�ɂȂ�܂ł͋@�\����B

	@date	2005/09/06	junjunn �쐬
*/

template<class TYPE>
class int64Base
{
public:
	word operator =(const word w)	{set(0,w);return w;}
	int operator =(const int i)		{set(0,i);return i;}
	uint operator =(const uint n)	{set(0,n);return n;}
	operator uint()	{return m_t[0];}

protected:
	void set(TYPE w1,TYPE w2)	{m_t[1] = w1;m_t[0]=w2;};
	TYPE m_t[2];
};

typedef int64Base<int> int64;
typedef int64Base<uint> uint64;

}	//namespace monapi2

#endif

/*!
    @file  Type.h
    @brief ��{�^�Etypedef

    ��{�^�Etypedef

	License=Mona License
    \version $Revision$
    \date   update:$Date$
*/
#ifndef _MONAPI2_TYPE_H
#define _MONAPI2_TYPE_H

namespace monapi2
{

//author junjunn

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
�Ȃ�bool�Ȃ̂�int�Ȃ̂��H�ƌ�����bool���g�������{���͑S����int�œ��ꂷ�����
int��bool�܂���bool��int�ւ̈ÖٓI�ȃL���X�g���Z���Ȃ��Ȃ葬���Ȃ�̂ŁB
�����Ƃ��v���O�����S�̂��炷��Ɣ��X���鎞�Ԃ��낤��
Y/N�̓���͈Ӗ��I��bool�ŏ����̂��l�I�ɍD���Ȃ̂Ŏ��͂��܂�g���Ă܂��񂪁E�E�E
*/
typedef int 					booli;


//�ϕ�
typedef	unsigned char			vchar;			///<�W�������B�ォ��typedef uint16 vchar�Ƃ����j�R�[�h�ɍ��킹�����ς�邩���B
typedef vchar*					pvchar;			///<�W��������ւ̃|�C���^
typedef const vchar				pcvchar;		///<const�W��������ւ̃|�C���^

//�Œ蕝
typedef	unsigned char			char1;			///<1�o�C�g����
typedef	unsigned short			char2;			///<2�o�C�g����

typedef char1*					pchar1;			///<�W��������ւ̃|�C���^
typedef const char1*			pcchar1;		///<const�W��������ւ̃|�C���^
typedef char2*					pchar2;			///<���j�R�[�h������ւ̃|�C���^
typedef const char2*			pcchar2;		///<const���j�R�[�h������ւ̃|�C���^


}	//namespace monapi2

#endif

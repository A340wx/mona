/**
	@file	Bit.h
	@brief	�r�b�g����

	�r�b�g����

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_BIT_H
#define _MONAPI2_BASIC_BIT_H

#include "switch.h"
#include "Type.h"

namespace monapi2	{

/**
	@brief int�^�̕ϐ��Ƀr�b�g�P�ʂœ��o�͂���Bstatic�N���X
	@date	2005/08/20	junjunn �쐬
*/
class BitFn
{
public:
	static bool get(int iTarget,int iBitIndex);				///<iTarget��iBit�Ԗڂ̃r�b�g��bool��Ԃ��B
	static void set(int *piTarget,int iBitIndex,bool bOn);	///<*piTarget��iBit�Ԗڂ̃r�b�g��bOn���Z�b�g����B

	static const uint m_acnBitMask[32];
};

inline uint8_t getByte0(uint32_t dw)	{return (uint8_t)((dw & 0x000000FF));}
inline uint8_t getByte1(uint32_t dw)	{return (uint8_t)((dw & 0x0000FF00) >> 8);}
inline uint8_t getByte2(uint32_t dw)	{return (uint8_t)((dw & 0x00FF0000) >> 16);}
inline uint8_t getByte3(uint32_t dw)	{return (uint8_t)((dw & 0xFF000000) >> 24);}
inline uint8_t getByte0(int i)		{return (uint8_t)((i & 0x000000FF));}
inline uint8_t getByte1(int i)		{return (uint8_t)((i & 0x0000FF00) >> 8);}
inline uint8_t getByte2(int i)		{return (uint8_t)((i & 0x00FF0000) >> 16);}
inline uint8_t getByte3(int i)		{return (uint8_t)((i & 0xFF000000) >> 24);}
inline uint8_t getByte0(uint16_t w)	{return (uint8_t)(w & 0x00FF);}
inline uint8_t getByte1(uint16_t w)	{return (uint8_t)(w >> 8);}
inline uint16_t getWord0(int w)		{return (uint16_t)(w & 0xFFFF);}
inline uint16_t getWord1(int w)		{return (uint16_t)(w >> 16);}

inline uint packByte(int i,int i2)	{return ((uint16_t)i) | (((uint16_t)i2)<<8);}
inline uint packWord(int i,int i2)	{return ((uint16_t)i) | (((uint16_t)i2)<<16);}

}	//namespace monapi2

#endif

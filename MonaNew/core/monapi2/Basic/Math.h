/**
	@file	Math.h
	@brief	���w�֘A

	���w�֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#ifndef _MONAPI2_BASIC_MATH_H
#define _MONAPI2_BASIC_MATH_H

#include "switch.h"
#include "Type.h"
#include "Limit.h"

namespace monapi2	{

/**
	@brief	���w����BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/

const double PI		=	3.14159265358979323846;		///<�~����
#ifndef NAPIER
const double NAPIER	=	2.71828182845904523536;		///<���R�ΐ��̒�
#endif
#ifndef HUGE_VAL
const double HUGE_VAL	=	_DOUBLE_MAX;				///<exp�ȂǂŌv�Z�ł���ő�l�𒴂����Ƃ��ɏo�Ă���B
#endif

//�l�����Z�B
void divide(int iNumerator,int iDenominator,int* piQuotient,int* piRemainder);
void divide(double dNumerator,double dDenominator,int* piQuotient,double* pdRemainder);

//�w��
double power(double x, double y);
uint power(uint x, uint y);
double power2(double x);
double squareroot(double num);
double log(double x);

#undef log2		  	 	 	//�ꕔ�̊��ł�log2�̃}�N������`����Ă��ďՓ˂���̂ŁB 
double log2(double x);

double log10(double x);
double exponential(double x);

//�O�p�֐�
double sin(double angle);
double cos(double angle);
double tan(double angle);
double atan(double x,double y);
double atan(double x);
double acos(double x);
double asin(double x);

//�؂�グ�E�؂�̂āE�l�̌ܓ��E��Βl�ȂǕό`�␮�`
int		mod(int iTarget,int iModule);
double	mod(double iTarget,double dModule);
double	ceil(double x);
double	floor(double x);
double	round(double x);
inline int		absolute(int i)		{return (i>0)?i:-i;}
inline double	absolute(double d)	{return (d>0)?d:-d;}

//����
void initRandom(int iSeed);
int getRandom(uint nRange);

//���̑�
float convertLinearUnit(float fTarget,float fValue1From,float fValue1To,float fValue2From,float fValue2To);
inline void swap(int* pi1,int* pi2)	{int iTemp=*pi1;*pi1=*pi2;*pi2=iTemp;}

inline int getMin(int i1,int i2)					{return (i1<i2)?i1:i2;}
inline int getMin(uint i1,uint i2)					{return (i1<i2)?i1:i2;}
inline cpchar1 getMin(cpchar1 p1,cpchar1 p2)		{return (p1<p2)?p1:p2;}

inline int getMax(int i1,int i2)					{return (i1>i2)?i1:i2;}
inline int getMax(uint i1,uint i2)					{return (i1>i2)?i1:i2;}
inline cpchar1 getMax(cpchar1 p1,cpchar1 p2)		{return (p1>p2)?p1:p2;}

void putBetween(int* piTarget,int iMin,int iMax);

//dTarget = dModule * q + r;�̌`�ɂ���B
//r��dModule/2��菬�����Ȃ�悤�Ɂi�\�Ȍ���]��̐�Βl�����Ȃ��jq��1���₷�����炵�Ē�������B
void getModule_ReduceRemainder(double dTarget,double udModule,int* piQuotient,double* piRemainder);


/**
	@brief	2^(����)���v�Z���邽�߂̃T�u���[�`��
	@date	2005/08/20	junjunn �쐬
*/
class SCPowerOf2
{
public:
//2^x���v�Z�B�S�Ă�x�B
	static double get(double x);

protected:
public:
//2^x���v�Z�B-1<x<1����
	static double getFloat(double x);
//2^x���v�Z�Bx�͐����ɐ؂�̂Ă���B
	static double getInt(double x);
};


/**
	@brief	�����_�������B
	@date	2005/08/20	junjunn �쐬
*/
//�������ǂ̗]�n�����肻���E�E�E
class KnuthRandom
{
public:
	KnuthRandom();

	void init(long lSeed);	///<������
	void randomize();		///<�����_������

	long getInt();			///< 0 <= x < iRANDOM_RANGE �̊Ԃ�long��Ԃ�
	double getFloat();		///< 0 <= x < 1 �̊Ԃ�double��Ԃ�

	float getRange()	{return m_fRange;}


protected:
	enum {
		iTABLE_SIZE =55,
		iTABLE_MID_SIZE =24,
		iTABLE_SEED	= 21,
		iRANDOM_RANGE = _INT_MAX,	//0�`���͈̔͂Ő��l�����������B
	};

	int m_iCurPos;
	float m_fRange;
	long m_aiBuffer[iTABLE_SIZE+1];
};

}	//namespace monapi2

#endif

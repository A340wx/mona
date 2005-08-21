/**
	@file	Math.h
	@brief	���w�֘A

	���w�֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
#ifndef _MONAPI2_BASIC_MATH_H
#define _MONAPI2_BASIC_MATH_H

#include "Type.h"
#include "Limit.h"

namespace monapi2	{

const double PI		=	3.14159265358979323846;		///<�~����
const double NAPIER	=	2.71828182845904523536;		///<���R�ΐ��̒�
const double HUGE_VAL =	_DOUBLE_MAX;				///<exp�ȂǂŌv�Z�ł���ő�l�𒴂����Ƃ��ɏo�Ă���B


//�l�����Z�B
void divide(int iNumerator,int iDenominator,int* piQuotient,int* piRemainder);
void divide(double dNumerator,double dDenominator,int* piQuotient,double* pdRemainder);

//�w��
	double power(double x, double y);
	uint power(uint x, uint y);
	double squareroot(double num);
	double log(double x);
	double log10(double x);
	double exponential(double x);

//�O�p�֐�
double sin(double angle);
	double cos(double angle);
	double tan(double angle);
	double atan(double x, double y);
	double atan(double x);
	double acos(double x);
	double asin(double x);

//�؂�グ�E�؂�̂āE�l�̌ܓ��E��Βl�ȂǕό`�␮�`
	double mod(double x,double *buf);
	double ceil(double x);
	double floor(double x);
	double round(double x);
	int absolute(int i);

//����
	void initRandom(int seed);
	int getRandom(int Size);

class Random
{
public:
	Random();
	Random(unsigned long seed);
	~Random();

public:
	int nextInt();
	double nextDouble();
	void setSeed(unsigned long seed);

//	void init_genrand(unsigned long s);
//	void init_by_array(unsigned long init_key[],int key_length);
//	double genrand_real1(void);
//	unsigned long genrand_int31(void);
};



//dTarget = dModule * q + r;�̌`�ɂ���B
//r��dModule/2��菬�����Ȃ�悤��q��1���₷�����炵�Ē�������B�B
void getModule_ReduceRemainder(double dTarget,double udModule,int* piQuotient,double* piRemainder);

//2^x���v�Z�B
double getPowerOf2(double x);

//getPowerOf2�̃T�u���[�`���B2^f���v�Z�B-1<f<1����
double getPowerOf2Float(double x);

//getPowerOf2�̃T�u���[�`���B2^f���v�Z�Bf�͐����ɐ؂�̂Ă���B
double getPowerOf2Int(double x);
}	//namespace monapi2

#endif

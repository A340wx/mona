/**
	@file	Math.cpp
	@brief	���w�֘A

	���w�֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
#include "switch.h"
#include "Math.h"

namespace monapi2
{
//�����Ɏg���I�u�W�F�N�g
KnuthRandom g_KnuthRandom;

const double g_cd1OverLn2	= 1.4426950408890;	// 1/ln2
const double g_cdLn2		= 0.69314718055995;	// ln2

//���q�𕪕�Ŋ����ď��Ə�]�����߂�B
///@author junjunn @date update:2005/08/20
void divide(int iNumerator,int iDenominator,int* piQuotient,int* piRemainder)
{
	*piQuotient = iNumerator / iDenominator;
	*piRemainder = iNumerator - iDenominator * *piQuotient;
}

//���q�𕪕�Ŋ����ď��Ə�]�����߂�B
///@author junjunn @date update:2005/08/20
void divide(double dNumerator,double dDenominator,int* piQuotient,double* pdRemainder)
{
	*piQuotient = (int)(dNumerator / dDenominator);
	*pdRemainder = dNumerator - dDenominator * *piQuotient;
}

//���`�P�ʕϊ�
///@author junjunn @date update:2005/08/20
float convertLinearUnit(float fTarget,float fValue1From,float fValue1To,float fValue2From,float fValue2To)
{
	return (fValue2To - fValue1To) / (fValue2From - fValue1From) * (fTarget-fValue1From)+ fValue1To;
}

//dTarget = dModule * q + r;�̌`�ɂ���B
//r��dModule/2��菬�����Ȃ�悤��q��1���₷�����炵�Ē�������B
///@author junjunn @date update:2005/08/20
void getModule_ReduceRemainder(double dTarget,double udModule,int* piQuotient,double* piRemainder)
{
	*piQuotient = (int) (dTarget/udModule);
	*piRemainder = dTarget - udModule * *piQuotient;

//��]��dMolude�̔������傫�������ꍇ���̕�����i�߂��B
	if (dTarget>0)
	{
		if (*piRemainder * 2 > udModule)
		{
			(*piQuotient)++;
			*piRemainder-=(udModule);
		}
	}
	else
	{
		if (-(*piRemainder) * 2 > udModule)
		{
			(*piQuotient)--;
			*piRemainder+=(udModule);
		}
	}
}

//��]�����߂�
///@author junjunn @date update:2005/08/20
int mod(int iTarget,int iModule)
{
	int i=iTarget % iModule;
	return i;
}

//��]�����߂�
///@author junjunn @date update:2005/08/20
double mod(double dTarget,double dModule)
{
	int iQuotient;
	double dRemainder;
	divide(dTarget,dModule,&iQuotient,&dRemainder);

	return dRemainder;
}

//�؂�̂�
///@author junjunn @date update:2005/08/20
double floor(double x)
{
	return (x>=0)?(int)x:(int)x-1;
}

//�؂�グ
///@author junjunn @date update:2005/08/20
double ceil(double x)
{
	return (x>=0)?(int)x+1:(int)x;
}

//�l�̌ܓ�
///@author junjunn @date update:2005/08/20
double round(double x)
{
	return (x>=0)?floor(x+0.5):ceil(x-0.5);	//0.5�𑫂��̂͌ÓT�I�ȃg���b�N�B
}

//log base 2
///@author junjunn @date update:2005/08/20
double log2(double x)
{
	if (x < 0)	return 0;

	double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld1
		fld x
		fyl2x
		fstp	qword ptr dResult
	}
#else
	ASSERT(0);
#endif

	return dResult;
}

//log base 10
///@author junjunn @date update:2005/08/20
double log10(double x)
{
/*
		10^y=x;			���߂鎮��
		10=2^z;			z�𓱓����Ă����u���B
	��	(2^z)^y=x;
	��	2^(z*y)=x;
	��	z*y=log2(x);
	��	y=log2(x)/z;
*/
	const double cd1OverLog2of10 = 0.30102999566398;	//��L��1/z
	double dResult = log2(x) * cd1OverLog2of10;
	return dResult;
}

//log base e
///@author junjunn @date update:2005/08/20
double log(double x)
{
/*
		e^y=x;			���߂鎮��
		e=2^z;			z�𓱓����Ă����u���B
	��	(2^z)^y=x;
	��	2^(z*y)=x;
	��	z*y=log2(x);
	��	y=log2(x)/z;

*/
	double dResult = log2(x) * g_cdLn2;
	return dResult;
}

//e^x���v�Z�B
///@author junjunn @date update:2005/08/20
double exponential(double x)
{
//�A�Z���u����
	if (1)
	{
/*
		y=e^x;			���߂鎮�B
		e=2^z;			������z�𓱓����Ă����u����
	��	y=(2^z)^x;
	��	y=2^(z*x);

	����Ă�������y�����߂���B
*/
		return SCPowerOf2::get(g_cd1OverLn2 * x);	//���ʂ̒�����L��z*x
	}
//�����W�J��
	else
	{
/*
e^x�̃e�C���[�W�J��e^x=1+x+x^2/2! + x^3/3!�@�E�E�E

�ǂ��x�ł��������邪x���傫���Ƃ��ɂ͎��Ԃ�������̂�
x = i(����) + d(��������)�̌`�ɕ�������

  e^x = e^(i + d) = e^i + e^d;

�ɂ���B
e^i�͐����񐔂ׂ̂���Ȃ̂ŕ��ʂɌv�Z�ł���B
e^d�̓e�C���[�W�J�Ōv�Z����B

���ꂪ��ʂƎv���邪���ꂶ��܂�Ȃ��̂�Mona�I���W�i����
x = i(����) + d1(����1������) + d(����2������)�܂ōׂ�����������
���x�Ɛ��x���҂����Ƃɂ���E�E�E
*/
		int iXInteger;
		double dXFloat;
		getModule_ReduceRemainder(x,1,&iXInteger,&dXFloat);

//e^i�̕����B

//getPowerOf2Int���g���邪�܂��ǂ�����A�Z���u���łȂ̂Ŏ蓮�ł�����Ⴆ�B
		double dExponentialIntegerResult;
		{
			if (iXInteger>0)
			{
				dExponentialIntegerResult=NAPIER;
				for (int i=0;i<iXInteger-1;i++)
				{
					dExponentialIntegerResult*=NAPIER;
				}
			}
			else
			{
				dExponentialIntegerResult=1;
				for (int i=0;i<-iXInteger;i++)
				{
					dExponentialIntegerResult/=NAPIER;
				}
			}
		}

//�����_1�������Ƃ���ȉ��ɕ����B
		int iDecimal1;
		double dXFloat2=dXFloat;
		getModule_ReduceRemainder(dXFloat,0.1,&iDecimal1,&dXFloat2);

		double adExponentialDecimal1[]=
		{
			0.40656965974060,	//	e^-0.9
			0.44932896411722,	//	e^-0.8
			0.49658530379141,	//	e^-0.7
			0.54881163609403,	//	e^-0.6
			0.60653065971263,	//	e^-0.5
			0.67032004603564,	//	e^-0.4
			0.74081822068172,	//	e^-0.3
			0.81873075307798,	//	e^-0.2
			0.90483741803596,	//	e^-0.1
			1.0000000000000,	//	e^-0.0
			1.1051709180756,	//	e^ 0.1
			1.2214027581602,	//	e^ 0.2
			1.3498588075760,	//	e^ 0.3
			1.4918246976413,	//	e^ 0.4
			1.6487212707001,	//	e^ 0.5
			1.8221188003905,	//	e^ 0.6
			2.0137527074705,	//	e^ 0.7
			2.2255409284925,	//	e^ 0.8
			2.4596031111569,	//	e^ 0.9
		};

		double dExponentialFloat2Result=0;
		{
			double dProduct = 1;
			double iFactorial=1;
			for (int i=1;i<10;i++)	//10�񂮂炢��double�̐��x���o��݂����B����ȏ�͖��ʁB
			{
				dExponentialFloat2Result += dProduct/iFactorial;
				iFactorial*=i;
				dProduct *= (dXFloat2);
			}
		}

		return dExponentialIntegerResult * adExponentialDecimal1[iDecimal1+9] * dExponentialFloat2Result;
	}
}

//x^y���v�Z�B
uint power(uint x, uint y)
{
	uint nResult=1;
	for (uint n=0;n<y;n++)
	{
		nResult*=x;
	}
	return nResult;
}

//2^y���v�Z�B
double power2(double x)
{
	return SCPowerOf2::get(x);
}

//x^y���v�Z�B
double power(double x, double y)
{
/*
	z=x^y;
	log2(z)=y*log2(x);
	z = 2^(y*log2(x))
*/
	double dResult = power2(y * log2(x));
	return dResult;
}


//���������v�Z����B
///@author junjunn @date update:2005/08/20
double squareroot(double x)
{
	if (x<0)	return 0;

    double dResult;
#ifdef _COMPILER_VISUALC
	__asm
	{
		fld	x
		fsqrt
		fstp	qword ptr dResult
	}
#else
//@author HigePon
    asm volatile ("fsqrt" : "=t"(dResult) : "0"(num));
#endif
    return dResult;
}

//�T�C�����v�Z����B
///@author junjunn @date update:2005/08/20
double sin(double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld	x
		fsin
		fstp	qword ptr dResult
	}
#else
//@author HigePon
    asm volatile ("fsin" : "=t"(dResult) : "0"(x));
#endif

	return dResult;
}

//�R�T�C�����v�Z����B
///@author junjunn @date update:2005/08/20
double cos(double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld	x
		fcos
		fstp	qword ptr dResult
	}
#else
//@author HigePon
    asm volatile ("fcos" : "=t"(dResult) : "0"(x));
#endif

	return dResult;
}

//�^���W�F���g���v�Z����B
///@author junjunn @date update:2005/08/20
double tan(double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld	x
		fptan
		fstp	st					//sin�Ƃ��ƈႢ���ʂ�st(1)�ɓ����Ă���̂�st�͐؂�̂�
		fstp	qword ptr dResult
	}
#else
//@author HigePon
    asm volatile ("fptan" : "=t"(dResult) : "0"(x));
#endif

	return dResult;
}

//�A�[�N�^���W�F���g���v�Z����B
///@author junjunn @date update:2005/08/20
double atan(double y,double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld	y
		fld	x
		fpatan
		fstp	qword ptr dResult
	}
#else
//@author HigePon
    asm volatile("fld1; fpatan" : "=t"(dResult) : "0" (x) : "st(1)");
#endif

	return dResult;
}

double atan(double x)
{
	return atan(x,1);
}

//�A�[�N�T�C�����v�Z����B
///@author junjunn @date update:2005/08/20
double asin(double x)
{
	if (absolute(x) > 1)	return 0;
/*
			1=sin(x)^2+cos(x)^2
	������	tan(x)=sin(x)/cos(x)	�Ȃ̂�
	��		1=(sin(x)^2+(sin(x)/tan(x))^2
	��		tan(x) = ��(sin(x)^2 / (1-sin(x)^2))

	������	sin(y)=x;
	��		tan(y) = ��(sin(y)^2 / (1-sin(y)^2))
	��		tan(y) = ��(x^2 / (1-x^2))
	��		y = atan(��(x^2 / (1-x^2))
*/

	double d = x*x;
	double dResult = atan(squareroot(d / (1-d)));

	return (x>0)?dResult:-dResult;
}

//�A�[�N�R�T�C�����v�Z����B
///@author junjunn @date update:2005/08/20
double acos(double x)
{
	if (absolute(x) > 1)	return 0;
	if (x==-1)	return PI;
/*
			1=sin(x)^2+cos(x)^2
	������	tan(x)=sin(x)/cos(x)	�Ȃ̂�
	��		1=(tan(x)cos(x))^2+cos(x)^2
	��		tan(x) = ��((1-cos(x)^2)/cos(x)^2)
	��		tan(x) = ��(1/cos(x)^2 - 1)

	������	cos(y)=x;
	��		tan(y) = ��(1/cos(y)^2 - 1)
	��		tan(y) = ��(1/x^2 - 1)
	��		y = atan(��(1/x^2 - 1))
*/

	double d = x;
	double dResult = atan(squareroot(1.0/(d*d) -1));

	return (x>0)?dResult:(PI-dResult);
}

//2^x���v�Z�B
///@author junjunn @date update:2005/08/20
double SCPowerOf2::get(double x)
{
//CPU�̖��ߏ㏬���Ɛ�������[�킯�ĕʁX�Ɍv�Z����B
	int iIntPart;
	double dFloatPart;
	divide(x,1,&iIntPart,&dFloatPart);
	double dResultFloat	= getFloat(dFloatPart);
	double dResultInt	= getInt(iIntPart);
	double dResult = dResultInt * dResultFloat;
	return dResult;
}

//2^f���v�Z�B-1<f<1����
///@author junjunn @date update:2005/08/20
double SCPowerOf2::getFloat(double x)
{
	double dResult;

//2^f-1
#ifdef _COMPILER_VISUALC
	__asm
	{
		fld x
		f2xm1
		fstp dResult
	}
#else
	ASSERT(0);
#endif

	return dResult+1;
}

//2^f���v�Z�Bf�͐����ɐ؂�̂Ă���B
///@author junjunn @date update:2005/08/20
double SCPowerOf2::getInt(double x)
{
	double dResult;

#ifdef _COMPILER_VISUALC
//st(0) * 2^(st(1)���v�Z����B
	__asm
	{
		fld x
		fld1
		fscale
		fstp st(1)		//���ʂ�st(0)�ɂ���̂����ǂ���st(1)����菜���K�v������̂�st(1)�Ɉړ��B
		fstp dResult
	}
#else
	ASSERT(0);
#endif

	return dResult;
}

void initRandom(int iSeed)
{
	g_KnuthRandom.init(iSeed);
}

int getRandom(uint nRange)
{
	int r = g_KnuthRandom.getInt();

	return ((int) (r/g_KnuthRandom.getRange()*nRange));
}

//KnuthRandom////////////////
KnuthRandom::KnuthRandom()
{
	m_iCurPos=0;
	m_fRange = (float)iRANDOM_RANGE;
}

void KnuthRandom::init(long lSeed)
{
	m_aiBuffer[iTABLE_SIZE] = lSeed;
	long r = 1;
	for (int i=1;i<iTABLE_SIZE;i++) 
	{
		int iPos = (iTABLE_SEED * i) % iTABLE_SIZE;
		m_aiBuffer[iPos] = r;
		r = lSeed - r;
		if (r < 0) r += iRANDOM_RANGE;
		lSeed = m_aiBuffer[iPos];
	}

//�ŏ��ɓ]�����B
	for (i=0;i<3;i++)		randomize();
	m_iCurPos = iTABLE_SIZE;
}

void KnuthRandom::randomize()
{
	int i;
	for (i = 1; i <= iTABLE_MID_SIZE; i++) 
	{
		int r = m_aiBuffer[i] - m_aiBuffer[i + iTABLE_MID_SIZE+7];
		if (r < 0) r += iRANDOM_RANGE;
		m_aiBuffer[i] = r;
	}
	for (i = iTABLE_MID_SIZE+1; i <= iTABLE_SIZE; i++) 
	{
		int r = m_aiBuffer[i] - m_aiBuffer[i - iTABLE_MID_SIZE];
		if (r < 0) r += iRANDOM_RANGE;
		m_aiBuffer[i] = r;
	}
}

long KnuthRandom::getInt()
{
	if (++m_iCurPos > iTABLE_SIZE) 
	{
		randomize();
		m_iCurPos = 1;  
	}
	return m_aiBuffer[m_iCurPos];
}

double KnuthRandom::getFloat()
{
	return (1.0 / iRANDOM_RANGE) * getInt();
}



}		//namespace monapi2

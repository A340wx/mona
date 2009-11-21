/**
	@file	Math.cpp
	@brief	���w�֘A

	���w�֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Math.h"
#include "Debug.h"

namespace monapi2
{
//�����Ɏg���I�u�W�F�N�g
KnuthRandom g_KnuthRandom;

const double g_cd1overLn2	= 1.4426950408890;	// 1/ln2
const double g_cdLn2		= 0.69314718055995;	// ln2



/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void divide(int iNumerator,int iDenominator,int* piQuotient,int* piRemainder)
{
	*piQuotient = iNumerator / iDenominator;
	*piRemainder = iNumerator - iDenominator * *piQuotient;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void divide(double dNumerator,double dDenominator,int* piQuotient,double* pdRemainder)
{
	*piQuotient = (int)(dNumerator / dDenominator);
	*pdRemainder = dNumerator - dDenominator * *piQuotient;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
float convertLinearUnit(float fTarget,float fValue1From,float fValue1To,float fValue2From,float fValue2To)
{
	return (fValue2To - fValue1To) / (fValue2From - fValue1From) * (fTarget-fValue1From)+ fValue1To;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void putBetween(int* piTarget,int iMin,int iMax)
{
	*piTarget=getMin(*piTarget,iMax);
	*piTarget=getMax(*piTarget,iMin);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
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

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int mod(int iTarget,int iModule)
{
	int i=iTarget % iModule;
	return i;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double mod(double dTarget,double dModule)
{
	int iQuotient;
	double dRemainder;
	divide(dTarget,dModule,&iQuotient,&dRemainder);

	return dRemainder;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double floor(double x)
{
	return (x>=0)?(int)x:(int)x-1;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double ceil(double x)
{
	return (x>=0)?(int)x+1:(int)x;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double round(double x)
{
	return (x>=0)?floor(x+0.5):ceil(x-0.5);	//0.5�𑫂��Đ؂�̂Ă͌ÓT�I�ȃg���b�N�B
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double log2(double x)
{
	if (x < 0)	return 0;

	double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld1
		fld		x
		fyl2x
		fstp	dResult
	}
#else
	asm volatile ("fld1");
    asm volatile ("fyl2x" : "=t"(dResult) : "0"(x));
#endif

	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double log10(double x)
{
/*
		10^y=x;			���߂鎮�B
		10=2^z;			z�𓱓����Ă����u���B
	��	(2^z)^y=x;
	��	2^(z*y)=x;
	��	z*y=log2(x);
	��	y=log2(x)/z;
*/

//��L��1/z�Bz�Ŋ�����1/z�����������CPU�I�ɑ����̂ł����u���Ƃ��B
	const double cd1overLog2of10 = 0.30102999566398;
	double dResult = log2(x) * cd1overLog2of10;
	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double log(double x)
{
/*
		e^y=x;			���߂鎮�B
		e=2^z;			z�𓱓����Ă����u���B
	��	(2^z)^y=x;
	��	2^(z*y)=x;
	��	z*y=log2(x);
	��	y=log2(x)/z;
*/
	double dResult = log2(x) * g_cdLn2;
	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double exponential(double x)
{
//�A�Z���u����
#if 1
	{
/*
		y=e^x;			���߂鎮�B
		e=2^z;			z�𓱓����Ă����u���B
	��	y=(2^z)^x;
	��	y=2^(z*x);
*/
		return SCPowerOf2::get(g_cd1overLn2 * x);	//���ʂ̒�����L��z*x
	}
//�����W�J��
#else
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
		double dProduct = 1;
		double iFactorial=1;
		for (int i=1;i<10;i++)	//10�񂮂炢��double�̐��x���o��݂����B����ȏ�͖��ʁB
		{
			dExponentialFloat2Result += dProduct/iFactorial;
			iFactorial*=i;
			dProduct *= (dXFloat2);
		}

		return dExponentialIntegerResult * adExponentialDecimal1[iDecimal1+9] * dExponentialFloat2Result;
	}
#endif	//if 1
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
uint power(uint x, uint y)
{
	uint nResult=1;
	for (uint n=0;n<y;n++)
	{
		nResult*=x;
	}
	return nResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double power2(double x)
{
	return SCPowerOf2::get(x);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double power(double x, double y)
{
/*
		z=x^y;					���߂鎮�B
	��	log2(z)=y*log2(x);
	��	z = 2^(y*log2(x))
*/
	double dResult = power2(y * log2(x));
	return dResult;
}


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double squareroot(double x)
{
	if (x<0)	return 0;

    double dResult;
#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		x
		fsqrt
		fstp	dResult
	}
#else
//@author Higepon
    asm volatile ("fsqrt" : "=t"(dResult) : "0"(x));
#endif
    return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double sin(double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		x
		fsin
		fstp	dResult
	}
#else
//@author Higepon
    asm volatile ("fsin" : "=t"(dResult) : "0"(x));
#endif

	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double cos(double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		x
		fcos
		fstp	dResult
	}
#else
//@author Higepon
    asm volatile ("fcos" : "=t"(dResult) : "0"(x));
#endif

	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double tan(double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		x
		fptan
		fstp	st					//sin�Ƃ��ƈႢ���ʂ�st(1)�ɓ����Ă���̂�st�͐؂�̂�
		fstp	dResult
	}
#else
    asm volatile ("fptan" : "=t"(dResult),"=u"(dResult) : "0"(x));
#endif

	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double atan(double y,double x)
{
    double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		y
		fld		x
		fpatan
		fstp	dResult
	}
#else
//@author Higepon
    asm volatile("fpatan" : "=t" (dResult) : "0" (x), "u" (y) : "st(1)");
#endif

	return dResult;
}

double atan(double x)
{
	return atan(x,1);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double asin(double x)
{
	if (absolute(x) > 1)	return 0;
/*
			1=sin(x)^2+cos(x)^2
	������	tan(x)=sin(x)/cos(x)	�Ȃ̂�
	��		1=(sin(x)^2+(sin(x)/tan(x))^2
	��		tan(x) = ��(sin(x)^2 / (1-sin(x)^2))

	�����Ŗ���ɂ��	sin(y)=x;
	��		tan(y) = ��(sin(y)^2 / (1-sin(y)^2))
	��		tan(y) = ��(x^2 / (1-x^2))
	��		y = atan(��(x^2 / (1-x^2))
*/

	double d = x*x;
	double dResult = atan(squareroot(d / (1-d)));

	return (x>0)?dResult:-dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
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

	�����Ŗ���ɂ��	cos(y)=x;
	��		tan(y) = ��(1/cos(y)^2 - 1)
	��		tan(y) = ��(1/x^2 - 1)
	��		y = atan(��(1/x^2 - 1))
*/

	double d = x;
	double dResult = atan(squareroot(1.0/(d*d) -1));

	return (x>0)?dResult:(PI-dResult);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
double SCPowerOf2::get(double x)
{
//CPU�̖��ߏ㏬���Ɛ������킯�ĕʁX�Ɍv�Z����B
	int iIntPart;
	double dFloatPart;
	divide(x,1,&iIntPart,&dFloatPart);
	double dResultFloat	= getFloat(dFloatPart);
	double dResultInt	= getInt(iIntPart);
	double dResult = dResultInt * dResultFloat;
	return dResult;
}

/**
	@brief	2^f���v�Z�B-1<f<1����B
	@date	2005/08/20	junjunn �쐬
*/
double SCPowerOf2::getFloat(double x)
{
	double dResult;

//2^f-1
#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		x
		f2xm1
		fstp	dResult
	}
#else
    asm volatile ("f2xm1" : "=t"(dResult) : "0"(x));
#endif

	return dResult+1;
}

/**
	@brief	2^f���v�Z�Bf�͐����ɐ؂�̂Ă���B
	@date	2005/08/20	junjunn �쐬
*/
//st(0) * 2^(st(1)���v�Z����B
double SCPowerOf2::getInt(double x)
{
	double dResult;

#ifdef _COMPILER_VISUALC
	__asm
	{
		fld		x
		fld1
		fscale
		fstp	st(1)	//���ʂ�st(0)�ɂ���̂����ǂ���st(1)���|�b�v����K�v������̂�st(1)�Ɉړ��B
		fstp	dResult
	}
#else
  	asm volatile ("fld %0"::"f"(x));
  	asm volatile ("fld1");
	asm volatile ("fscale;" : "=t"(dResult));
#endif

	return dResult;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void initRandom(int iSeed)
{
	g_KnuthRandom.init(iSeed);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int getRandom(uint nRange)
{
	int r = g_KnuthRandom.getInt();

	return ((int) (r/g_KnuthRandom.getRange()*nRange));
}

//KnuthRandom////////////////
/**
	@brief	�R���X�g���N�^
	@date	2005/08/20	junjunn �쐬
*/
KnuthRandom::KnuthRandom()
{
	m_iCurPos=0;
	m_fRange = (float)iRANDOM_RANGE;
}

/**
	@brief	������
	@date	2005/08/20	junjunn �쐬
*/
void KnuthRandom::init(long lSeed)
{
	m_aiBuffer[iTABLE_SIZE] = lSeed;
	long r = 1;
	int i;
	for (i=1;i<iTABLE_SIZE;i++) 
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

/**
	@brief	�����_������
	@date	2005/08/20	junjunn �쐬
*/
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

/**
	@brief	int�����o���B
	@date	2005/08/20	junjunn �쐬
*/
long KnuthRandom::getInt()
{
	if (++m_iCurPos > iTABLE_SIZE) 
	{
		randomize();
		m_iCurPos = 1;  
	}
	return m_aiBuffer[m_iCurPos];
}

/**
	@brief	float�����o���B
	@date	2005/08/20	junjunn �쐬
*/
double KnuthRandom::getFloat()
{
	return (1.0 / iRANDOM_RANGE) * getInt();
}

}		//namespace monapi2

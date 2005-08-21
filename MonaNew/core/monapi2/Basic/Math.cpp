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
		double f1OverLn2=1.442695041;	//��L��z�B1/ln2

		return getPowerOf2(x * f1OverLn2);	//���ʂ̒�����L��z*x
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

	return dResult;
#else
//@author HigePon
    asm volatile ("fsin" : "=t"(dResult) : "0"(x));
    return dResult;
#endif
}

//2^x���v�Z�B
///@author junjunn @date update:2005/08/20
double getPowerOf2(double x)
{
//CPU�̖��ߏ㏬���Ɛ�������[�킯�ĕʁX�Ɍv�Z����B
	int iIntPart;
	double dFloatPart;
	divide(x,1,&iIntPart,&dFloatPart);
	double dResultFloat	= getPowerOf2Float(dFloatPart);
	double dResultInt	= getPowerOf2Int(iIntPart);
	return dResultInt * dResultFloat;
}

//getPowerOf2�̃T�u���[�`���B2^f���v�Z�B-1<f<1����
///@author junjunn @date update:2005/08/20
double getPowerOf2Float(double x)
{
	double dResult;

//2^f-1
	__asm
	{
		fld x
		f2xm1
		fstp dResult
	}

	return dResult+1;
}

//getPowerOf2�̃T�u���[�`���B2^f���v�Z�Bf�͐����ɐ؂�̂Ă���B
///@author junjunn @date update:2005/08/20
double getPowerOf2Int(double x)
{
	double dResult;
	__asm
	{
		fld x
		fld1
		fscale
		fstp dResult
	}

	return dResult;
}

}		//namespace monapi2

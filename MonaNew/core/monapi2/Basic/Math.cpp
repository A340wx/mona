/**
	@file	Math.h
	@brief	���w�֘A

	���w�֘A

	License=Mona License
    \version $Revision$
    \date	$Date$
*/
#include "Math.h"

using namespace monapi2;

///@author junjunn @date update:2005/08/20
void MathFn::divide(int iNumerator,int iDenominator,int* plQuotient,int* plRemainder)
{
	*plQuotient = iNumerator / iDenominator;
	*plRemainder = iNumerator - iDenominator * *plQuotient;
}

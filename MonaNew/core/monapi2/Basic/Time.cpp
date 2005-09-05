/**
	@file	Time.h
	@brief	�����E���Ԋ֘A

	�����E���Ԋ֘A

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Debug.h"
#include "Time.h"
#include "Math.h"

namespace monapi2
{

//���ꂼ��̌��Ɏ���܂ł̑�����
//31.28.31.30.31.30.31.31,30.31.30.31
int g_aiCumulativeMonthDayCount[] = {0,31,59,90,120,151,181,212,243,273,304,334,365};


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Time::init()
{
	m_iYear		= 0;
	m_iMonth	= 0;
	m_iDay		= 0;
	m_iDayOfWeek= 0;
	m_iHour		= 0;
	m_iMinute	= 0;
	m_iSecond	= 0;
	m_iDayCountInYear =0;
	m_iSecondCount	= 0;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool Time::isEqual(const Time* cpTime)
{
	return (
	m_iYear		== cpTime->getYear()				&&
	m_iMonth	== cpTime->getMonth()				&&
	m_iDay		== cpTime->getDay()					&&
	m_iDayOfWeek== cpTime->getDayOfWeek()			&&
	m_iHour		== cpTime->getHour()				&&
	m_iMinute	== cpTime->getMinute()				&&
	m_iSecond	== cpTime->getSecond()				&&
	m_iDayCountInYear ==cpTime->m_iDayCountInYear	&&
	m_iSecondCount	== cpTime->getSecondCount());
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int Time::getCurrentSecondCount()
{
	return 0;
}

/**
	@brief	1970�N1��1��0��0������̑��b����N���������b�ɒ����BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Time::set(int iSecondCount)
{
//���Ή�
	if (iSecondCount<0)
	{
		init();
		return;
	}

//�b���J�E���g�Z�b�g�B
	m_iSecondCount = iSecondCount;

//���ꂼ��̒P�ʂ̕b���ϊ��Ȃǂ�����Ă����B
	const uint cnMinuteSecond	= 60;
	const uint cnHourSecond		= cnMinuteSecond * 60;
	const uint cnDaySecond		= cnHourSecond * 24;
	const uint cn4YearDay		= 365 * 4+ 1;

//���͖����̓����ɂ΂�������邵�N�͉[�N������B����čŏ��͂܂��m���ȑ����������߂�B
	int iDayCount;
	divide(iSecondCount,cnDaySecond	,&iDayCount,&iSecondCount);

//����������͗j�������߂��B
	m_iDayOfWeek = iDayCount%7 + 4;
	if (m_iDayOfWeek>=7)	m_iDayOfWeek-=7;

//�[�N���̂���4�N�P�ʂ̑傫�������߂�B
	int i4YearCount;	//4�N�̉񐔁B
	int iDayIn4Year;	//i4YearCount��mod��������Ƃ��Ɏc������B
	divide(iDayCount,cn4YearDay		,&i4YearCount,&iDayIn4Year);

//4�N�̒��ŉ��N�������߂�B
	int iYearIn4Year=3;
	m_iDayCountInYear = iDayIn4Year;
	int aiYearDiv[] = {0,365,730,1096,1461};	//���ꂼ��̔N�ɒB����܂ł̑������B1970�N����̃J�E���g�Ȃ̂�3�N�ڂɉ[�N�����Ă�B
	for (int i=0;i<4;i++)
	{
		if (iDayIn4Year<aiYearDiv[i+1])			//���������ꂼ��̔N�̑������ɗ������甲����B
		{
			iYearIn4Year = i;
			m_iDayCountInYear = iDayIn4Year - aiYearDiv[i];
			break;
		}
	}

//�N�����߂�B
	m_iYear = 1970 + i4YearCount*4 + iYearIn4Year;

//�[�N�B4�N�Ɉ��B������100�Ŋ���؂��N�͂Ȃ��Ȃ�B�����������400�Ŋ���؂��N�͗L���ɂȂ�B
	bool bLeapYear=false;
	if (m_iYear%4==0)
	{
		bLeapYear = true;
		if (m_iYear%100==0)
		{
			bLeapYear = false;
			if (m_iYear%400==0)
			{
				bLeapYear = true;
			}
		}
	}

//1�N�̒��̑��������猎�Ɠ��������߂�B
	const int cnLeapDay = 59;	//2��29���̓����J�E���g�B
//�[���𒼌���������B
	if (bLeapYear && m_iDayCountInYear==cnLeapDay)
	{
		m_iMonth=1;
		m_iDay=28;
	}
	else
	{
//�[�N������菜�����������B
		int iDayCountInYearNoLeap = m_iDayCountInYear;
		if (bLeapYear && m_iDayCountInYear>cnLeapDay)	iDayCountInYearNoLeap--;

		getMonthAndDay(iDayCountInYearNoLeap,&m_iMonth,&m_iDay);
	}

//�c��̕b�����ƕ��ƕb�ɂ킯��B
	divide(iSecondCount,cnHourSecond	,&m_iHour,&iSecondCount);
	divide(iSecondCount,cnMinuteSecond	,&m_iMinute,&m_iSecond);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Time::set(const Time* cpTime)
{
	m_iYear		= cpTime->getYear();
	m_iMonth	= cpTime->getMonth();
	m_iDay		= cpTime->getDay();
	m_iDayOfWeek= cpTime->getDayOfWeek();
	m_iHour		= cpTime->getHour();
	m_iMinute	= cpTime->getMinute();
	m_iSecond	= cpTime->getSecond();
	m_iDayCountInYear =cpTime->m_iDayCountInYear;
	m_iSecondCount	= cpTime->getSecondCount();
}

/**
	@brief �����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void Time::set(int iYear,int iMonth,int iDay,int iHour,int iMinute,int iSecond)
{
//1970�N����[�N���N�����񐔂����߂�B
	int iLeapYearCount = getLeapYearCountSince1970(iYear,iMonth);

//�N�̒��̓����{���̒��̓����{�����{�[�N�␳
	int iDayCount = (iYear-1970)*365 + g_aiCumulativeMonthDayCount[iMonth] + iDay + iLeapYearCount;

//�����̒��̕b�{���̒��̕b�{���̒��̕b�{�b�B
	int iSecondCount = iSecond + 60*(iMinute + 60*(iHour + 24*iDayCount));

//�b����Z�b�g�B
//@memo �����_�ł͂�����x�N���������b�����߂閳�ʂȍ�Ƃ�����E�E
	set(iSecondCount);
}


//protected///////
/**
	@date	2005/08/20	junjunn �쐬
*/
void Time::getMonthAndDay(int m_iDayCountInYear,int* piMonth,int* piDay)
{
	for (int i=0;i<12;i++)
	{
		if (m_iDayCountInYear < g_aiCumulativeMonthDayCount[i+1])
		{
			*piMonth = i;
			*piDay = m_iDayCountInYear - g_aiCumulativeMonthDayCount[i];
			return;
		}
	}

	ASSERT(0);		//�����ɂ͗��Ȃ��͂��B
}

/**
	@date	2005/08/20	junjunn �쐬
*/
int Time::getLeapYearCountSince1970(int iYear,int iMonth)
{
//0�`iYear�N�܂ł̉[�N�C�x���g�B
	int i4YearCount		= iYear/4;		//4�Ŋ���؂��N�͉[�N�B
	int i100YearCount	= iYear/100;	//������100�Ŋ���؂��N�͗�O�Ŗ����B
	int i400YearCount	= iYear/400;	//������400�Ŋ���؂��N�͂���ɗ�O�ł��̏ォ��L���ɂȂ�B

//0�`1970�N�܂ł̉[�N�J�E���g�B
	const int ciLeapYearCountUntil1970 = 477;

//1970�N�ȍ~�̉[�N�̉񐔁B
	int iLeapYearCount = (i4YearCount-i100YearCount+i400YearCount) - ciLeapYearCountUntil1970;

//���N�̕��B�܂��[�N���N����O�̓��Ȃ̂Ɋ܂߂Ă��܂����P�[�X���C������B
	if (iYear%4==0 && iMonth<2)		iLeapYearCount--;

	return iLeapYearCount;
}

}		//namespace monapi2

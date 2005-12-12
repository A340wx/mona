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
#ifndef _MONAPI2_BASIC_TIME_H
#define _MONAPI2_BASIC_TIME_H

#include "Switch.h"
#include "Type.h"

namespace monapi2	{

/**
	@brief	���ԁE��������舵���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class Time
{
public:
//�\�z
	Time()						{init();}
	Time(const Time* cpTime)	{set(cpTime);}
	Time(int iSecondCount)		{set(iSecondCount);}
	Time(int iYear,int iMonth,int iDay,int iHour,int iMinute,int iSecond)	{set(iYear,iMonth,iDay,iHour,iMinute,iSecond);}

//�擾
	static int getCurrentSecondCount();

	int getYear()		const{return m_iYear;}			///<�N�𓾂�
	int getMonth()		const{return m_iMonth;}			///<���𓾂�
	int getDay()		const{return m_iDay;}			///<���𓾂�
	int getHour()		const{return m_iHour;}			///<���𓾂�
	int getMinute()		const{return m_iMinute;}		///<���𓾂�
	int getSecond()		const{return m_iSecond;}		///<�b�𓾂�
	int getDayOfWeek()	const{return m_iDayOfWeek;}		///<���j�����B0=���j���B
	int getSecondCount()const{return m_iSecondCount;}	///<���b���𓾂�

	bool isEqual(const Time* cpTime);
	bool operator ==(const Time& crefTime)	{return isEqual(&crefTime);}
	bool operator !=(const Time& crefTime)	{return ! (isEqual(&crefTime));}
	bool isBefore(const Time* cpTime,bool bAllowEqual=false)	{return  (bAllowEqual)?((getSecondCount()) <= (cpTime->getSecondCount())):(getSecondCount() < cpTime->getSecondCount());}
	bool operator <(const Time& crefTime)	{return isBefore(&crefTime,false);}
	bool operator <=(const Time& crefTime)	{return isBefore(&crefTime,true);}
	bool isAfter(const Time* cpTime,bool bAllowEqual=false)		{return  (bAllowEqual)?(getSecondCount() >= cpTime->getSecondCount()):(getSecondCount() > cpTime->getSecondCount());}
	bool operator >(const Time& crefTime)	{return isAfter(&crefTime,false);}
	bool operator >=(const Time& crefTime)	{return isAfter(&crefTime,true);}
	int compare(const Time* cpTime)			{return getSecondCount() - cpTime->getSecondCount();}

	Time add(int iSecondCount)			{return Time(getSecondCount()+iSecondCount);}
	Time operator +(int iSecondCount)	{return add(iSecondCount);}
	Time subtract(int iSecondCount)		{return Time(getSecondCount()-iSecondCount);}
	Time operator -(int iSecondCount)	{return subtract(iSecondCount);}

//����
	void set(int iSecondCount);						///<�b���J�E���g���Z�b�g��YMDhms�����ɕϊ��B
	void operator =(int iSecondCount)	{set(iSecondCount);}
	void set(const Time* cpTime);
	void operator = (const Time& crefTime)	{set(&crefTime);}
	void set(int iYear,int iMonth,int iDay,int iHour,int iMinute,int iSecond);

	void addSelf(int iSecondCount)		{set(getSecondCount()+iSecondCount);}
	void operator +=(int iSecondCount)	{addSelf(iSecondCount);}
	void subtractSelf(int iSecondCount)	{set(getSecondCount()-iSecondCount);}
	void operator -=(int iSecondCount)	{subtractSelf(iSecondCount);}

protected:
///��N�̒��̓����J�E���g���猎�Ɠ������߂�B
	void getMonthAndDay(int iDayInYear,int* piMonth,int* piDay);

///1970����iYear,iMonth�܂ł̉[�N�̉񐔂����߂�B
	int getLeapYearCountSince1970(int iYear,int iMonth);

///������
	void init();

protected:
	int m_iYear;
	int m_iMonth;
	int m_iDay;
	int m_iDayOfWeek;
	int m_iHour;
	int m_iMinute;
	int m_iSecond;
	int m_iDayCountInYear;		//��N�̒��̃g�[�^������
	int m_iSecondCount;			//1970�N1��1������̑��b���B
};

/**
	@brief	��_�Ԃ̎������v���BMonapi2���t�@�����X���Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
class TimeMeasure
{
public:
	void start();
	uint finish();

protected:
	uint m_nTick;
};

}	//namespace monapi2

#endif

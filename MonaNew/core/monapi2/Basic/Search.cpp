/**
	@file	Search.cpp
	@brief	�\�[�g�E�T��

	�\�[�g�E�T��

	License=Mona License
	@version $Revision$
	@date	$Date$
*/
//�o�O�C�������鎞�͊֐��{�̐�����@date�����ɓ��t�Ɩ��O�ƍ�Ɠ��e��t�������Ă����Ă��������B
//�܂�.h�t�@�C���ɂ���N���X�����Ȃǂ�@date���𕔕��ɂ����l�̎������Ă����Ă��������B
#include "Search.h"
#include "CollectionList.h"

namespace monapi2
{

//QuickSort�̃I�v�V�����B�p�t�H�[�}���X�����̂��߂ŕ��ʂ�define���Ă����ق�����Α����Ȃ�B
#define QSORTOPTION_SMARTPIVOT
#define QSORTOPTION_PRESORTCHECK


/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void quicksort(void* pavArray,uint iArrayMemberCount,uint nArrayMemberWidth,FnQSortCompare pfnCompare)
{
	CQuickSort QuickSort;
	QuickSort.Sort(pavArray,0,iArrayMemberCount,nArrayMemberWidth,pfnCompare);
}


//CQuickSort/////////////
/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void CQuickSort::Sort(void* pavArray,int iStart,int iCount,uint nArrayMemberWidth,FnQSortCompare pfnCompare)
{
//�`���[���p�Ɏ��Ԃ��v��
#ifdef _PERFORMANCETEST
	DWORD dwTickStart = GetTickCount();
#endif

	m_iStart	= iStart;
	m_iCount	= iCount;
	m_pavArray	= pavArray;
	m_nArrayMemberWidth = nArrayMemberWidth;
	m_pfnCompare= pfnCompare;

//���łɃ\�[�g����Ă��邩�`�F�b�N
#ifdef QSORTOPTION_PRESORTCHECK
	if (isSorted())
	{
#ifdef _PERFORMANCETEST
		m_nTimeTaken = GetTickCount() - dwTickStart;
#endif
		return;
	}
#endif

	m_pSwapBuffer = new char[m_nArrayMemberWidth];

	int iLeft = iStart;
	int iRight = iStart+iCount-1;


	Stack<int> stack;

//QuickSort�ɂ͍ċA����菜���X�^�b�N�Ŏ��������o�[�W�������g���B
//�ċA�����ǂ�OS�I�Ɏ��s����X�^�b�N�Ȃ̂�
//�ċA�I�ɌĂяo����@��肩�͂������ăv���O�������Ŏ����ŃX�^�b�N����������1�֐��ɔ[�߂����
//�X�s�[�h�I�ɂ��������I�ɂ��L���Ō����悭�`���[���A�b�v�ł���B
	for (;;)
	{
		while (iRight>iLeft)
		{
//��������s���I�����iPivot��荶�͑S��pavArray[iPivot]���<=�ŁA�E�͑S��>=�ȗv�f�����Ԃ悤�\�[�g����Ă���B
			int iPivot = Partition(iLeft,iRight);

//�E�ƍ��̂ǂ��炪�v�f����������r�B
			if (iPivot-iLeft > iRight-iPivot)
			{
				stack.push(iLeft);
				stack.push(iPivot-1);
				iLeft=iPivot+1;
			}
			else
			{
				stack.push(iPivot+1);
				stack.push(iRight);
				iRight=iPivot-1;
			}
		}

		if (stack.isEmpty()) break;
		iRight=stack.pop();
		iLeft=stack.pop();
	}

	delete m_pSwapBuffer;

#ifdef _PERFORMANCETEST
	m_nTimeTaken = GetTickCount() - dwTickStart;
#endif


//�\�[�g���������s��ꂽ�����Z
#ifdef _DEBUG
//	assert(IsSorted());
#endif

}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
int CQuickSort::Partition(int iLeft,int iRight)
{
//�X�}�[�g�s�{�b�g
#ifdef QSORTOPTION_SMARTPIVOT
/*
�ςȘb����QuickSort�͂��炩���߃\�[�g����Ă���f�[�^��芮�S�Ƀ����_���ȃf�[�^�̃\�[�g�̕���
ꡂ��ɑ����B
�iQuickSort�̓s�{�b�g�Ńf�[�^�����܂�2�������ꂽ�����݂��̔�r�񐔂������čō��̃X�s�[�h���o��B
�@���炩���߃\�[�g����Ă���f�[�^�͂��傤�ǂ��̋t�ŕ������S�������Ȃ��ň��ɒx���Ȃ�B�j
���̍ň��P�[�X�������ׂɂ�����Ƃ������ёւ����s���Ă����B

��̓I�ɂ͂܂��ŏ��A�Ō�A���Ԃ�3�̒l���璆���l��T���o��������s�{�b�g�ɗ��p����B
�i�[�̐������s�{�b�g�ɂȂ�̂��ň��Ȃ̂Łj�B
*/
	int iMiddle = (iLeft+iRight)/2;
//�s�{�b�g��T���āA���łɕ��ёւ����s���Ă����B
	sortTriplet(iLeft,iMiddle,iRight);

//�^�񒆂̒l��iRight-1�Ɏ����Ă��ăs�{�b�g�Ƃ��ė��p����B
	swap(iMiddle,iRight-1);

//���ł�SortTriplet�ō��E���[�͒����l�ɑ΂��\�[�g����Ă鎖���킩���Ă���̂Ŕ͈͂����߂Ă���
	iRight--;
	iLeft++;
#endif

//��������Partition�̃��C��
	void* pvPivot= getElementAddress(iRight);
	int iSwapLeft=iLeft-1;
	int iSwapRight=iRight;

#ifdef QSORTOPTION_SMARTPIVOT
	if (iSwapLeft>=iSwapRight)	return iSwapLeft;
	if (iRight==0)				return iSwapLeft;
#endif

	for(;;)
	{
		while (compare(getElementAddress(++iSwapLeft)	,pvPivot)<0);	//�ň�pvPivot�Ŏ~�܂�̂�while���[�v�͖��Ȃ��B
		while (compare(getElementAddress(--iSwapRight)	,pvPivot)>0);	//�������ň�pvPivot�Ŏ~�܂�̂Ŗ��Ȃ��B
		if (iSwapLeft>=iSwapRight)	break;
		swap(iSwapLeft,iSwapRight);
	}

	swap(iSwapLeft,iRight);

	return iSwapLeft;
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void CQuickSort::swap(int i1,int i2)
{
	set(m_pSwapBuffer,getElementAddress(i1));
	set(getElementAddress(i1),getElementAddress(i2));
	set(getElementAddress(i2),m_pSwapBuffer);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
void CQuickSort::sortTriplet(int iLeft,int iMiddle,int iRight)
{
	if (isSwapRequired(getElementAddress(iLeft),getElementAddress(iMiddle)))	swap(iLeft,iMiddle);
	if (isSwapRequired(getElementAddress(iLeft),getElementAddress(iRight)))		swap(iLeft,iRight);
	if (isSwapRequired(getElementAddress(iMiddle),getElementAddress(iRight)))	swap(iMiddle,iRight);
}

/**
	@brief	�����A�����A�߂�l��Monapi2���t�@�����X�Q�ƁB
	@date	2005/08/20	junjunn �쐬
*/
bool CQuickSort::isSorted()
{
	for (int i=m_iStart;i<m_iStart+m_iCount-1;i++)
	{
		if (isSwapRequired(getElementAddress(i),getElementAddress(i+1)))
			return false;
	}
	return true;
}

/*
void CQuickSort::SmallSort(int iStart,int iCount)
{
	InsertionSort(iStart,iCount);
}

void CQuickSort::InsertionSort(int iStart,int iCount)
{
	for (int i=iStart;i<iStart+iCount;i++)
	{
		void* pvPivot=getElementAddress(i);
		int j=i;
		while (isSwapRequired(getElementAddress(j-1),pvPivot) && j>=iStart)	//@todo �ԕ����g���Ȃǂł����͌������ł��邩���B
		{
			set(getElementAddress(j),getElementAddress(j-1));
			j--;
		}

		set(getElementAddress(j),pvPivot);
	}
}
*/

///���̑�/////////////
#ifdef _PERFORMANCETEST
/**
	@brief	���x�𑪂�B
	@date	2005/08/20	junjunn �쐬
*/
void TestQSort()
{
//int�e�X�g
	{
		int iTestCount = 100000;	//�\�[�g����v�f��

		UINT nTimeRandom;			//���S�����_�����\�[�g����̂ɂ����鎞��
		UINT nTimeSorted;			//���łɊ��S�Ƀ\�[�g����Ă���̂ɂ�����x�\�[�g�������炩���鎞��
		UINT nTimeSortedReverse;	//���łɊ��S�ɋt���\�[�g����Ă���̂��\�[�g����ɂ����鎞��
		UINT nTimeSortedAlmost;	//�قڊ��S�Ƀ\�[�g�����A�ꕔ�ɔ�\�[�g���������Ă�f�[�^���\�[�g����̂ɂ����鎞��

		CQuickSort QuickSort;
		srand(time(NULL));

		int* paiArray = new int[iTestCount];

		for (int i=0;i<iTestCount;i++)		paiArray[i] = SCMath::GetRandom(iTestCount);
		QuickSort.Sort(paiArray,0,iTestCount,sizeof(int),CompareInt);
		nTimeRandom = QuickSort.m_nTimeTaken;

		for (i=0;i<iTestCount;i++)		paiArray[i] = i;
		QuickSort.Sort(paiArray,0,iTestCount,sizeof(int),CompareInt);
		nTimeSorted = QuickSort.m_nTimeTaken;

		for (i=0;i<iTestCount;i++)		paiArray[i] = iTestCount-i;
		QuickSort.Sort(paiArray,0,iTestCount,sizeof(int),CompareInt);
		nTimeSortedReverse = QuickSort.m_nTimeTaken;

		for (i=0;i<iTestCount;i++)		paiArray[i] = i;
		for (i=1;i<=4;i++)	paiArray[SCMath::GetRandom(iTestCount)] = iTestCount / 5 * (i);
		QuickSort.Sort(paiArray,0,iTestCount,sizeof(int),CompareInt);
		nTimeSortedAlmost = QuickSort.m_nTimeTaken;

		delete paiArray;

		::CString strReport;
		strReport.Format("Random-	%d\nSorted-	%d\nSortedReverse-	%d\nSortedAlmost-	%d",nTimeRandom ,nTimeSorted ,nTimeSortedReverse ,nTimeSortedAlmost);
		SCWinFile::Dump((PCSTR1)(PCSSTR1)strReport);


		int aiArray[]={1,5,3,9,7,2,6,10,4,8};
		QuickSort.Sort(aiArray,0,10,sizeof(int),CompareInt);

/*
�������ʁB

iTestCount = 100000�̃\�[�g�ɂ�������Tick����(CPU�FAthlon64 3000+)�B
���ꂼ��̎�����3��s�����ς�����Ă���B
Windows��Tick���\�̈����Ŋe���l�ɍő�20���炢�̌덷���o�Ă���ۂ���
�D����ׂ���x�͂͂�����o�Ă�̂�(߃��)�ƼŲ

���X�^�b�N�E�~�X�}�[�g�s�{�b�g�E�~�\�[�g�`�F�b�N�E�~SmallSort
	Random-	141
	Sorted-	48625
	SortedReverse-	48472
	SortedAlmost-	31563
�����炩���߃\�[�g����Ă�f�[�^�ɑ΂��Ă̓A�z�݂����ɐ��\��������E�E�E


���X�^�b�N�E���X�}�[�g�s�{�b�g�E�~�\�[�g�`�F�b�N�E�~SmallSort
	Random-	125
	Sorted-	83
	SortedReverse-	78
	SortedAlmost-	67
���\�[�g�f�[�^�n�Ɉ��|�I�ȉ��P�B


���X�^�b�N�E���X�}�[�g�s�{�b�g�E���\�[�g�`�F�b�N�E�~SmallSort
	Random-	125
	Sorted-	0
	SortedReverse-	99
	SortedAlmost-	67
��SortedReverse�����������������Sorted��0�ɁB
SortedReverse���g���@��͏��Ȃ����낤����Sorted�̃����b�g�ɑ΂����̃��X�N�͍̎Z����Ǝv���B
Random�̎��͈�u�Ń\�[�g�`�F�b�N���I���̂ŃI�[�o�[�w�b�h�����Ȃ��Ǝv���B


�Ȃ�������int�Ɍ�����pFnCompare�̑���ɒ���< >��r���𖄂ߍ���Ń\�[�g�����
�����͈ȉ��̒ʂ�ɂȂ����B
���X�^�b�N�E�~�X�}�[�g�s�{�b�g�E�~�\�[�g�`�F�b�N�E�~SmallSort
	Random-	62
���X�^�b�N�E���X�}�[�g�s�{�b�g�E�~�\�[�g�`�F�b�N�E�~SmallSort
	Random-	63
���X�^�b�N�E���X�}�[�g�s�{�b�g�E���\�[�g�`�F�b�N�E�~SmallSort
  	Random-	62

�S�̓I�ɔ{���炢�����Ȃ��B
���R�ƌ����Γ��R����int�Ȃǂ̒P���f�[�^�^�ɂ�qsort�ł͂Ȃ�
���ꂼ��ɍœK�������\�[�g��p�ӂ��Ă����ƍ����ɂȂ��B


@Memo QuickSort���P��
�܂�SmallSort�͖��C���v�������g�B
�œK���͋Â�o���ƃL�����Ȃ��̂ő��̍�Ƃ����邵���͂�����Ő؂�グ��B
*/
	}

//������e�X�g
	{
		srand(time(NULL));
		int iTestCharCount = 10;
		char** paszArray = new char*[iTestCharCount];

		for (int i=0;i<iTestCharCount;i++)
		{
			paszArray[i] = new char[11];
			for (int j=0;j<10;j++)
			{
				paszArray[i][j] = (char)('a' + SCMath::GetRandom(26));
			}
			paszArray[i][10] = '\0';
		}

		CQuickSort QuickSort;
		QuickSort.Sort(paszArray,0,iTestCharCount,sizeof(char*),CompareString);

		for (i=0;i<iTestCharCount;i++)	{delete paszArray[i];}
		delete paszArray;


		char* aszArray[]={"Zonu","Mona","Nida","Sii","Morara","Giko","Siraneeyo",};
		QuickSort.Sort(aszArray,0,7,sizeof(char*),CompareString);
	}
}
#endif


}	//namespace monapi2

/*
	Geometry Class Library
					Ver1.00 Release 000
					Wild Anarchy YU-kA (kouiti@lt.sakura.ne.jp)


�ȉ��̃N���X����\�������B
	�s�񉉎Z(Matrix)
	�S�������Z(Quaternion)
	�x�N�g�����Z(Vector)

�����̃N���X�́A�Q�[���Ŏg�p���邱�Ƃ�ړI�ɐ݌v���Ă��邽�߁A
�قƂ�ǂ̊֐��͓W�J����Ă���B
���Ƃ��΁A+= ���Z�q�͒ʏ� = �� + ��g�ݍ��킹�Đ������邪�A
�����̃N���X�ł͋ɗ͓W�J�����������Ă���B�i���ɗǂ��g���Ǝv���镔�����j
�\�[�X�R�[�h����剻���ĉ��������x���҂����߂ł���B
�i����ł��܂��܂��������̗]�n�͎c���Ă���Ƃ͎v���j

�����̃N���X�́A�݂��ɉ��Z���邱�Ƃ��o����B

	�s�񓯎m�̌v�Z
		Matrix = Matrix * Matrix
		Matrix *= Matrix

	�s��ɂ����W�ϊ�
		Vector = Vector * Matrix

	�S�������m�̌v�Z
		Quaternion = Quaternion * Quaternion
		Quaternion *= Quaternion
		Quaternion = Quaternion + Quaternion
		Quaternion += Quaternion
		~Quaternion		(Quaternion^-1 , Quaternion�̋t��)
	�������A�S�������m�̏�Z�́A�s��̏�Z�̋t�ɂȂ�_�ɒ��ӁB
	�܂�A
		(m1 == q1)
		(m2 == q2)
	�̎��A
		m = m1 * m2;
		q = q2 * q1;
	�Ƃ�������
		(m == q)
	�ƂȂ�B


	�S�����ɂ����W�ϊ�(��])
		Quaternion = Quaternion * VectorQuaternion * Quaternion^-1
		Vector = Quaternion * Vector * Quaternion^-1

�����̉��Z�����Z�q�i�܂��͊֐��j�ōs����B


�s��́Am1 , m2 �̏��ɍ��W�ϊ��������ꍇ�Am1 * m2 �Ƃ��邪�A
�S�����́Aq1 , q2 �̏��ɍ��W�ϊ��������ꍇ q2 * q1 �Ƌt�ɂȂ�_�ɒ��ӁB
�i����̓o�O�ł͂Ȃ��A�S�����̓����̂悤���j

Geometry.h ���ĂԑO�ɁAd3dtypes.h ���ĂԂ�Vector�N���X��
LPD3DVECTOR�̂����ɓn����B
���l��LPD3DMATRIX�ɂ�Matrix�N���X��n�����Ƃ��o����B
�܂��AD3DRMMATRIX4D(double [4][4])�ɑ΂��ẮAMatrix::m��
���ړn���Ηǂ��B


�ȉ��̊֐�(operator=)�́ANick Bobic���̃A���S���Y�����g�p�B
	�s�񂩂�S�����֕ϊ�
		Quaternion&	operator=(Matrix &src);


�Q�l����
	�u�b����ɂ��ŐV�A���S���Y�����T�v���� ���F ���i�Z�p�]�_�Ёj
		���̎�̃A���S���Y���{�̒��ł͍ŗD�ǖ{�ł���A�Ǝv���B
		���p�I�ȃA���S���Y���������f�ڂ���Ă���B
		�������A�ǂݎ�ɂ���Ȃ�̒m�����v�������B
		C/C++�v���O���}�Ȃ�A�j���q�ƈꏏ�ɂP�������Ă��đ��͖����B
		�i�ނ��뎄�͂j���q���́A�������̕����d�v���Ɗm�M���Ă���j

	�u�����f������v�I�D�L�D�K�p�~�������A�@�D�R�D�R���|���t���r�~�y�{���r��
					��� �m �Ė�E�}�� �v�O ��i�X�k�o�Ŋ�����Ёj
		�S�����ɊԂ���m�����F�������������ǂ�ŗ����ł��邭�炢�킩��₷��
		���������Ă���B
		�S�����̉������Ă��邽�����Q�P�y�[�W�����ǂ�łȂ����A
		�Q�U�O�O�~�͗ǂ��������������B
		�i�P�y�[�W���g�����ɂȂ�Ȃ��{���������݂���j


�]�ځA���ύĔz�z�ɂ���
	GPL�����ł��g�p������΁A��薳���ł��B
	�܂��A�A�Z���u�����ōœK�����ꂽ������������Ⴂ�܂�����A
	���ɂ����������B�i��
	�o����΁AE-3DNow��]�ł��B �������܂���


����
00/05/29	Matrix::SetOrientation()�Ƀo�O�B�C���B > Ver1.00��01
00/05/30	Matrix �� =Quaternion�ǉ� > Ver1.00��02
00/06/23	�ו����C��
			Matrix����ړ��x�N�g����Vector�ɃR�s�[�A�����Z����operator�ǉ��B
			SetOrientation()��Vector�̈������|�C���^����A�h���X���Z�q�ɕύX�B
			������SetRotate()��Vector�̈������C���B
			Matrix::Invert()��ǉ��B�i�t�s������߂�j
00/06/24	Quaternion&	operator=(Matrix &src);�Ƀo�O�����������ߏC��
			Quaternion::SetOrientation(),Matrix::SetOrientation()�̃o�O�C���B
			Matrix::Invert()������������œ��삵�Ȃ��������ߏC���B
00/06/25	Matrix::SetMagnification()�ǉ�
00/06/27	Quaternion * Matrix , Matrix * Quaternion �̎����L���ɂȂ����B
00/06/27	Quaternion::Quaternion&	operator= (Vector &src) ���폜�B
			���R��Matrix�̏ꍇ�Ɠ��삪�قȂ��Ă��܂����߁B
00/07/03	Vector�N���X�ɓ��ρA�O�ς̉��Z�֐���ǉ��B
00/07/05	�ו����C��

*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

//#include <float.h>

#ifndef PI
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define PI			M_PI
#define PI2			M_PI_2
#endif

//#define float double

// 0�ɋ߂��l��0�Ɋۂ߂�B
#define DBL_EPSILON 2.2204460492503131E-16
#define NearZero(d)	((d<DBL_EPSILON && d>-DBL_EPSILON) ? 0 : d)
#define IsZero(d)	((d<DBL_EPSILON && d>-DBL_EPSILON) ? 1 : 0)

class Vector;
class Quaternion;

class Matrix
{
public:
					Matrix();
	virtual			~Matrix();

	float			m[4][4];

	void			put();

// X,Y,Z�A���ꂼ��̎��ɑ΂��āAr������]����s��𐶐�
	void			SetXrotate(float r);
	void			SetYrotate(float r);
	void			SetZrotate(float r);
// X,Y,Z�A���ꂼ��̎��ɑ΂��āAr������]����s��𐶐�
	void			SetXrotate(float s,float c);
	void			SetYrotate(float s,float c);
	void			SetZrotate(float s,float c);
// 'F'��first,fast�̈ӁBthis�������������
// ����ꍇ�i�R���X�g���N�g���㓙�j�̂ݗL��
// �i�ŏ�����(first)�g�p�ł��A����(fast)�j
	void			SetXrotateF(float r);
	void			SetYrotateF(float r);
	void			SetZrotateF(float r);

// �g��k������s�񐶐�
	void			SetMagnification(float src);
	void			SetMagnification(float x,float y,float z);
	void			SetMagnification(Vector &src);

// z�x�N�g��������(x,y,z)�������Ay�x�N�g��������(ix,iy,iz)�������ϊ����s���s��𐶐�
	void			SetOrientation(float x,float y,float z,float ix,float iy,float iz);
	void			SetOrientation(Vector &vz,Vector &vy);

	Matrix&			Invert();
// �ړ��x�N�g���Z�b�g
	void			SetVector(float x=0,float y=0,float z=0);

	float&			operator()(int y, int x) { return m[y][x]; };
	Matrix&			operator= (Matrix src);
// �S��������s��֕ϊ�
	Matrix&			operator= (Quaternion &src);
// �ړ����W�����A�����Z(m[3][0],m[3][1],m[3][2]��������������)
	Matrix&			operator= (Vector &src);
	Matrix&			operator+=(Vector &src);
	Matrix&			operator-=(Vector &src);
// �s��̏�Z
	Matrix&			operator*=(Matrix &src);
	Matrix			operator* (Matrix &src);
// �s�� * �S����
	Matrix			operator* (Quaternion &src);
	Matrix&			operator*=(Quaternion &src);

// (x,y,z)���ꗥsrc�{����s��ɂ���
	Matrix&			operator*=(float src);
	Matrix			operator* (float src);
// �e������src�{����s��ɂ���
	Matrix&			operator*=(Vector &src);
	Matrix			operator* (Vector &src);
// �t�s��
	Matrix			operator~();

#ifdef _D3DTYPES_H_
	operator D3DMATRIX*() {return (D3DMATRIX*)m;};
#endif
};

class Quaternion
{
public:
					Quaternion();
	virtual			~Quaternion();

// q = a + bi + cj + dk (b,c,d�͂��ꂼ��x,y,z�ɑΉ�����)
	float			a,b,c,d;

// �l����
	Quaternion&		set(float ina,float inb,float inc,float ind);
// a �� 0 �ɂȂ�B
	Quaternion&		set(float inb,float inc,float ind);
// �f�o�b�O�p
	void			put();
// �S�����̋t��
	Quaternion&		Invert();

	void			SetXrotate(float r);
	void			SetYrotate(float r);
	void			SetZrotate(float r);

	Quaternion&		operator= (Quaternion src);
// �s�񂩂�S�����֕ϊ�
	Quaternion&		operator= (Matrix &src);
// �x�N�g���̃R�s�[�B�������� 0 �ŏ����������
//	Quaternion&		operator= (Vector &src);
// �S�����̉��Z
	Quaternion		operator+ (Quaternion &src);
	Quaternion&		operator+=(Quaternion &src);
// �S�����̏�Z
	Quaternion		operator* (Quaternion &src);
	Quaternion&		operator*=(Quaternion &src);
// �S���� * �s��
	Quaternion		operator* (Matrix &src);
	Quaternion&		operator*=(Matrix &src);

// �S�����̋t��
	Quaternion		operator~();
// �����Ƃ̏揜�Z
	Quaternion		operator* (float src);
	Quaternion&		operator*=(float src);
	Quaternion		operator/ (float src);
	Quaternion&		operator/=(float src);
// �����Ƃ̉��Z�́A�������ł��� a �ɉ��Z���邾���Ȃ̂ŏȗ��i�������g��Ȃ��j

// *this �� b,c,d ���x�N�g���Ƃ��āA���̉��� r ������]����S���������B
// ��]�́A������W�n�̂Ƃ��A�x�N�g���ɑ΂��č����i�����v���j�ł���B
// �܂��ASetRotate()���Ă�ł��x�N�g�������͕ς��Ȃ����A����������ŌĂ񂾏ꍇ
// (b=c=d=0�̎���) ���퓮�삵�Ȃ����ߊ�{�I�ɂ͖���x�N�g���l�����Ȃ����B
//	Quaternion&		SetRotate(float r);
// �x�N�g���l�������ɃZ�b�g����B
	Quaternion&		SetRotate(float inb,float inc,float ind,float r);
	Quaternion&		SetRotate(Vector &v,float r);
	Quaternion&		SetRotate(Quaternion &q,float r);
// SetRotate() ��ɌĂԂƁAsrc ����]�������x�N�g���S������Ԃ��B
	Quaternion		CalcRotate(Quaternion &src);

// Matrix�ƌ݊��B�ڂ�����Matrix::SetOrientation()�Q��
	void			SetOrientation(float x,float y,float z,float ix,float iy,float iz);
	void			SetOrientation(Vector &vz,Vector &vy);

protected:
	Quaternion&		SetRotate(float r);
	Quaternion&		operator= (Vector &src);
};

class Vector
{
public:
					Vector();
					Vector(float inx,float iny,float inz);
	virtual			~Vector();

	float			x,y,z;

	Vector&			set(float inx=0,float iny=0,float inz=0);
// �f�o�b�O�p
	void			put();

// �@���ɂ���B x*x + y*y + z*z == 1 �ɂȂ�B
	Vector&			Normal();
// ��Βl�����߂�Bsqrt(x*x + y*y + z*z)��Ԃ�
	float			Absolute();
// 2�_�Ԃ̋��������߂�
	float			Distance(Vector &src);

// ����(�Q�x�N�g���̐����p�x)��Ԃ�
	float			InnerProduct(Vector &src);
	float			operator*(Vector &src);
// ����(��(v1)(this)(v2)�̐����p�x)��Ԃ�
	float			InnerProduct(Vector &src1,Vector &src2);
// this, v1, v2 �̏��ŊO�ς����߁Athis�Ɋi�[����B
	Vector&			OuterProduct(Vector &v1,Vector &v2);
// this, v1, v2 �̏��ŊO�ς����߁A���ʂ�Vector��Ԃ��B
	Vector			CalcOuterProduct(Vector &v1,Vector &v2);

	Vector&			operator= (Vector src);
// �x�N�g�����m�̉����Z
	Vector			operator+ (Vector &src);
	Vector&			operator+=(Vector &src);
	Vector			operator-(Vector &src);
	Vector&			operator-=(Vector &src);
// �x�N�g���Ǝ����̏揜�Z
	Vector			operator* (float d);
	Vector&			operator*=(float d);
	Vector			operator/ (float d);
	Vector&			operator/=(float d);

// ���W�ϊ��B�P���ɍs�񉉎Z���s������
	Vector&			operator*=(Matrix &src);
	Vector			operator* (Matrix &src);
// �ړ��x�N�g�����R�s�[
	Vector&			operator= (Matrix &src);

// �x�N�g���̃R�s�[�B�������͐؂�̂�
	Vector&			operator= (Quaternion &src);

// ���W�ϊ��B�S�����̊|�Z�Ƃ͑S���̕ʕ��B���ۂ� q * v * ~q ���s���Ă���B
// �������v����
	Vector			operator* (Quaternion &src);
	Vector&			operator*=(Quaternion &src);

#ifdef _D3DTYPES_H_
	Vector&			operator= (D3DVECTOR src){x=src.x; y=src.y; z=src.z; return *this;};
	operator D3DVECTOR*() {return (D3DVECTOR*)this;};
#endif
};


// �s��A�S�������݂̊K�w�N���X�̃e�X�g���f��
// ���ۂ͂S��������s��ւ̕ϊ��͍����ɍs���A
// �s��ŏo���邱�Ƃ͂����Ă��S�����ŏo���A
// �X��4�������m�̏�Z�͍����Ȃ���
// ���������͂��ׂ� Quaternion + Vector �ɂ��āA
// ��ʂ̒��_�̍��W���Z���s���ꍇ�����s��ƒ��_�̏�Z���s���悤�ɂ��������ǂ��B

class HierarchyQ;
class HierarchyM;
class Hierarchy
{
public:
friend class HierarchyQ;
friend class HierarchyM;
						Hierarchy(int inID=0);
	virtual				~Hierarchy();

	int					ID;

	Vector				v;		// ���g�̃x�N�g��
	Vector				sv;		// �e����̑S�Ă����������W

	int					vnum;	// ���_��
	Vector				*vlist;	// ���_�̔z��

	virtual void		Calc();

	virtual Hierarchy	*Search(int searchID);

// �q����ǉ�
	virtual HierarchyQ	*AddChildQ();
	virtual HierarchyM	*AddChildM();


// ��{�I�Ɉꎟ�����X�g�ł���B
// �����͎q����m��Ȃ��B���̂����e��m���Ă���̂ō��W�ϊ����s����B
// �܂��A�e�̓��X�g�̒��Ŏ������O�ɂ��Ȃ���΂Ȃ�Ȃ��B
// �܂�A���݂ɐe�Ƃ��Ďw���Ă���\���̓G���[�ł���B
	Hierarchy			*parent,*prev,*next;

protected:
	virtual void		DoCalc(){};
	virtual void		DoCalcChild(HierarchyQ *child){};
	virtual void		DoCalcChild(HierarchyM *child){};
};

class HierarchyQ : public Hierarchy
{
public:
						HierarchyQ(int inID=0);
						~HierarchyQ();
	Quaternion			q;		// ���g�̕ϊ�
	Quaternion			sq;		// �e����̑S�Ă̕ϊ��������S����
protected:
	void				DoCalc();
	void				DoCalcChild(HierarchyQ *child);
	void				DoCalcChild(HierarchyM *child);
};

class HierarchyM : public Hierarchy
{
public:
						HierarchyM(int inID=0);
						~HierarchyM();
	Matrix				m;		// ���g�̕ϊ�
	Matrix				sm;		// �e����̑S�Ă̕ϊ��������s��
protected:
	void				DoCalc();
	void				DoCalcChild(HierarchyM *child);
	void				DoCalcChild(HierarchyQ *child);
};


//�Ɨ��֐�
Vector CrossProduct(Vector &v1,Vector &v2);

#endif

/*
// Geometry �T���v��
int main()
{
// �S�����T���v��
	Quaternion q;		// ��
	Vector v;			// ��]��������W�_

// (1,1,0)�̃x�N�g���ɑ΂��āA�x�N�g�� v ��������90�x��]������B
	q.set(1,1,0);		// ���ɂ���x�N�g����ݒ�
	q.SetRotate(PI2);	// ��]����p�x��ݒ�
	v.set(1,0,0);		// ��]������x�N�g����ݒ�
	v*=q;				// �x�N�g������]������
	v.put();			// ���ʕ\��

// �������A(1,1,0)�̃x�N�g���ɑ΂��āA�x�N�g�� v ��������180�x��]������B
	q.set(1,1,0);
	q.SetRotate(PI);	// ��]����p�x���Đݒ�
	v.set(1,0,0);
	v*=q;
	v.put();


// �s�񉉎Z�T���v��
	Matrix m,m2;

	m.SetYrotate(PI2);	// (z,x)���ʂɑ΂��āAPI2������]����s��
	v.set(1,0,0);
	v*=m;				// �s��ƃx�N�g���i�L���Ӗ��ł�����s��j�̏�Z
	v.put();

	m2.SetXrotate(PI2);	// (y,z)���ʂɑ΂��āAPI2������]����s��
	m*=m2;				// �s��̏�Z
	v.set(1,0,0);
	v*=m;
	v.put();

// �s�� �� �S���� �T���v��

	m=q;				// q�Ɗ��S�ɓ����ϊ����s��m�𐶐��B
	v.set(1,1,1);
	v*=q;
	v.put();			// �c�@
	v.set(1,1,1);
	v*=m;
	v.put();			// �@�Ɠ������ʂ�������B

	m.SetOrientation(1,2,3, 1,1.5,1.2);
	q=m;				// m�Ɗ��S�ɓ����ϊ����s��q�𐶐��B
	v.set(1,1,1);
	v*=q;
	v.put();			// �c�A
	v.set(1,1,1);
	v*=m;
	v.put();			// �A�Ɠ������ʂ�������B


	return 0;
}
*/

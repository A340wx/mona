Mesa-6.2.1��Mona�p�ɃR���p�C�����邽�߂̃R���p�C���ݒ�t�@�C����Makefile

�K�v�Ȃ���
Mona��CVS�\�[�X
MesaLib-6.2.1.tar.bz2
tmpmonalibc-3.tar.gz

�C���X�g�[�����@
export MONADIR=Mona�̃\�[�X�c���[�̏ꏊ
mkdir work
cd work
tar xjvf Mesa-6.2.1.tar.bz2
tar xzvf MesaForMona-3.tar.gz
tar xzvf tmpmonalibc-3.tar.gz
cd MesaForMona
cp -r * ../Mesa-6.2.1
cd ../Mesa-6.2.1

1. �ÓI���C�u����
make mona-static
lib/libOSMesa.a, libGLU.a
���ł���B

2. ���I���C�u����
make mona
lib/OSMESA.DLL, libOSMesa-imp.a, GLU.DLL, libGLU-imp.a
���ł���B

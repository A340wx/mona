
monaSq 1.0


������

�v���O�������� Squirrel �� MonaOS �Ŏ��s����v���O�����ł��B
MonaOS 0.3.0 alpha5 �ɂē���m�F���܂����B



��Squirrel �ɂ���

Squirrel �� C ����Ɏ����\�������� Lua ����̉e�����󂯂��A
������ LightWegight �ȑg�ݍ��ݗp�X�N���v�g����ł��B

�I�u�W�F�N�g�w���A��O�A�K�x�[�W�R���N�V�����A�N���[�W���A�}�C�N���X���b�h�Ȃǂ�
�T�|�[�g���Ă��܂��B
�ڂ����́A�ȉ��̂t�q�k���Q�Ƃ��Ă��������B

Squirrel �����y�[�W�i�p��j
http://squirrel-lang.org/

Squirrel 2.1 ���t�@�����X�}�j���A���i���{��j
http://muffin.cias.osakafu-u.ac.jp/~matumoto/cgi-bin/xt.cgi?prog/squirrel_lang


Squirrel �́w�X�N�C�����x�܂��́w�X�N�C�[���x�Ɠǂ݁A�p��Ń��X���Ӗ����܂��B
�\�[�X�t�@�C���g���q�� ".nut" �i�؂̎��̈ӁB".sq"�ł͂Ȃ����Ƃɒ��Ӂj�A
�o�C�g�R�[�h�R���p�C���ς݃t�@�C���g���q�� ".cnut"�ł��B



��������@

MonaSq �̃E�C���h�E�́A�{�^���A���̓G���A�A�o�̓G���A��
�R�ɕ�����Ă��܂��B

���̓G���A�ɃX�N���v�g����͂��āA
�w���s�x�{�^�����N���b�N���邩�wAlt+Enter�x�L�[��������
�X�N���v�g�����s����܂��B


�{�^������F

  ���{�^��      �O�̃X�N���v�g���s������\�����܂��B

  ���{�^��      ���̃X�N���v�g���s������\�����܂��B

  ���͗��N���A  ���̓G���A�̓��e���������܂��B

  �o�͗��N���A  �o�̓G���A�̓��e���������܂��B

  ���s          ���̓G���A�̃X�N���v�g�����s���܂��B
                ���s���́u��~�v�{�^���ɂȂ�A
                �N���b�N����ƃX�N���v�g�̎��s���~���܂��B

�L�[����F

  Alt+Enter     ���̓G���A�̃X�N���v�g�����s���܂��B

  Ctrl+Enter    ���̓G���A�̌��ݍs�̃X�N���v�g�����Ƃ��ĕ]�����āA
                �o�̓G���A�Ɍ��ʂ�\�����܂��B
                ��F
                  1 + 1 <Ctrl+Enter>
                �o�́F
                  2

  Ctrl+Tab      ���̓G���A�����o�̓G���A�ԂŃJ�[�\�����s�������܂��B

  Alt+��        �O�̗�����\�����܂��B
  
  Alt+��        ���̗�����\�����܂��B



MonaSq �́A�N�����Ɉ�x���� Squirrel ���s�������������܂��B
�X�N���v�g�͎��s�{�^�����������тɎ��s����܂����A
��x��`�����O���[�o���ϐ���֐��͎��̎��s���ɂ��Q�Ƃ��邱�Ƃ��ł��܂��B

�X�N���v�g�����ɂ́A��x���s�����X�N���v�g���ۑ�����܂��B
�N������́A���炩���ߗp�ӂ��ꂽ�T���v���X�N���v�g�������ɓ����Ă��܂��B
���͂����X�N���v�g���t�@�C���Ȃǂɕۑ�����@�\�͂���܂���B



���r���h���@

MonaADK (Mona Application Development Kit) ���g�p���Ă��܂��B
�r���h�̍ۂ́AMonaADK �� z_tools �t�H���_�Ɠ����f�B���N�g����
���̃v���W�F�N�g�̃t�H���_��u���āA�R�}���h�v�����v�g���N�����Ă��������B


�r���h�����s�菇
  make
  make run

�f�o�b�O�ł̃r���h�����s�菇
  make DEBUG=TRUE
  make run

�I�u�W�F�N�g�t�@�C���̍폜
  make clean


�f�o�b�O�ł͊J���p�ł��B
�R���\�[���G���A�ɗ]�v�ȃf�o�b�O��񂪕\������܂��B



���t�@�C���\��

�����̃\�[�X�R�[�h���C�Z���X�����݂��Ă��܂��B
���p�����Ă�������\�[�X�R�[�h���ŁAMonaSq �p�ɉ��ς���������
#if defined( MONASQ )
#endif
�ň͂�ł���܂��B


monasq.cpp
monasq.h
monasq_base.h
monasq_baygui.cpp
monasq_monapi.cpp
init_script.cpp
  ���̃v���O�����̃��C�����[�`���B
  MIT Licence �ł��B

doc/
  Squirrel ����� Squirrel �W�����C�u�����̃}�j���A���i�p��j�B

sq/
  Squirrel �̃\�[�X�R�[�h�B
  zlib/libpng licence �ł��B
    squirrel 2.1.1 stable
    http://squirrel-lang.org/

sqplus/
  Squirrel �p�̃w���p�[���C�u�����B
  ���C�Z���X�͕�����܂��񂪁Asqplus.h �ɁuFree for any use�v�Ƃ���܂��B
    SQUIRREL2_1_1_sqplus_23
    http://wiki.squirrel-lang.org/default.aspx/SquirrelWiki/SqPlus.html

misc/setjmp.h
misc/setjmp.cpp
  monalibc �� longjmp() �֐����Ăяo����
  �n���O�A�b�v���錻�ۂɑ����������߁A�Ǝ��ɒ�`���Ă���܂��B
  �ȉ�����q�؂��āAgcc�ŃR���p�C�����ʂ�悤�ɏC�����܂����B
  ���̂Q�t�@�C���� �C�� BSD licence �ł��B
    Sanos Operating System Kernel
    http://www.jbox.dk/sanos/index.htm

misc/vsprintf.cpp
misc/fcvt.cpp
  monalibc �� vsprintf() �͏������ꕔ���Ή��Ȃ̂�
  �Ǝ��ɒ�`���Ă���܂��B
  �ȉ�����q�؂��܂����B
  ���̂Q�t�@�C���� �C�� BSD licence �ł��B
    Sanos Operating System Kernel
    http://www.jbox.dk/sanos/index.htm

misc/TextArea.h
misc/TextArea.cpp
  baygui/TextArea.h ���C���N���[�h���Ă�
  �����J�ɎQ�Ƃ�������Ȃ��Ɠ{���錻�ۂɑ����������߁A
  �Ǝ��ɒ�`���Ă���܂��i���݂� libbaygui.a �ɂ͊܂܂�Ă��Ȃ����ۂ��H�j�B
  �ȉ������ɁA�������ς��Ă���܂��B
    /trunk/contrib/Graphics/libbaygui/awt/TextArea.cpp
    Revision 3120



���o�O

�E�n���O�A�b�v�o�O
  ���ہF
    baygui�R���|�[�l���g���g�p���Ȃ̂ɔj������邱�Ƃ�����
  �ڍׁF
    MonaSq ���Q�ƃJ�E���g���l�����Ă��Ȃ����߁A
    Squirrel �ϐ����X�R�[�v���o��� baygui�R���|�[�l���g�ł����Ă�
    GC �ɉ������Ă��܂��܂��B���̌��ʁA�����ȃ|�C���^��
    �΂���A�N�Z�X�������� MonaSq �̓n���O�A�b�v���܂��B
  �Ώ����@�F
    �D��I�ł����Abaygui�R���|�[�l���g�͎g�p���Ԉȏ�̕ϐ��X�R�[�v��
    �ێ�����悤�ɂ��Ă��������B



��MonaOS 0.3.0 alpha5 ��ł̃A�v���J�����̖��_�Ƃ��̑΍�

monaSq ���J�������Ŕ��������A
����� MonaOS �ŗL�Ǝv������_�Ƃ��̑΍�ɂ��Ẵ����ł��B


�Estdout, stdin ������`
  ���Ƃ肠���� NULL �ő�p

�E�t�@���N�V�����L�[��BREAK�L�[�Ȃǂ������Ă��Ȃ�
  �����߂đ��̃L�[�ő�p

�ECheckBox::CheckBox() �Ăяo���������N�ł��Ȃ�
  CheckBox::CheckBox("") �Ȃ�Ăяo����̂ł�����ő�p

�EC++��O���g���Ȃ�
  �����̏�� exit(-1) ���Ă��܂����A�G���[�𖳎�����悤�ɏC��

�Eplacement new �̃f�t�H���g�n���h��������`
  ����`���đΉ�
  ��sq/squirrel/sqpcheader.h ���Q��

�Esetjmp / longjmp �̓n���O�A�b�v���邱�Ƃ�����
  ������n�̃v���O�����ł͒v���I�Ȃ̂ŁA�ʂ� setjmp �������ؗp���đ�p

�Eprintf �n�֐��� %f �� %x �̂悤�ȏ��������������
  ��monalibc �Ή��҂��̂��肾�������A���łȂ̂� setjmp �ƂƂ��Ɏؗp
    �i�A�����̎����ɂ� snprintf() �n���Ȃ��j

�ETextArea �N���X�������N�ł��Ȃ�
  �������s�e�L�X�g���g���Ȃ��Ƃ��̃A�v�������藧���Ȃ��̂ŁA
    MonaOS �̃��|�W�g������\�[�X���ؗp���đ�p


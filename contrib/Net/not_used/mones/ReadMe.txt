
Code:Mones Mona�ɂ킩�l�b�g���[�N�Ή� Ver0.32

�ˑ�:Mona�R�A Ver0.30
     contrib_0.3/Sysutils/libPci

1.�r���h���@�B
 (1)���O�ɁAMona�R�A���r���h����B
    MonaNew(��) ���ACVS����Ƃ��Ă���Ȃ肵�āA�K���ȏꏊ�ɒu��
    
    export MONADIR=/usr/local/mona
    cd MonaNew
    make

 (2)mones�̃r���h
    cygwin�ŁA���̃t�@�C���̂���f�B���N�g���Ɉړ���
    make
 
 (3)ISO�C���[�W�̍쐬
    MonaNew/tools/mkimg  �ֈړ���
    make



2.�c���[����

yamami_mones  Mones:���[�g
 +--Makefile
 |  
 +--monesoc  :Mona Socket���C�u���� (UDP�̂݃T�|�[�g) 
 |   
 |  
 +--netprot  :�l�b�g���[�N�v���g�R���T�[�o(�ˑ�:nicDriver,monesoc)
 |           EtherNet
 |           ARP
 |           ICMP
 |           IP
 |           UDP
 |           TCP (������)
 |                 2006/03/23 �ǋL Code:Mones Rewrite2006 lwip���ڐA�Ƀ����C�g�\��
 |  
 +--nicdrv  :NIC�h���C�o (�ˑ�:pci)
 |   |  
 |   +--AbstractMonic.cpp  :����NIC�h���C�o
 |   |  
 |   +--MonesLoader.cpp   : NIC�h���C�o���[�_
 |   |  
 |   +--ne2000 :NE2000�h���C�o
 |       |  
 |       +--Ne2000MoNic.cpp
 |       |  
 |       +--Ne2000MoNic.h
 |    
 |    �E�E�EAbstractMonic(���ۃN���X) �̃C���^�[�t�F�[�X�����ŁAMones�Ƃ��Ă͓��삷��B
 |  
 |  
 +--sampleApp  : Mones�T���v���A�v��
 |   |  
 |   +--yamami : Yamami Mones�����p�A�v��
 |       |  
 |       |  
 |       +--main.cpp
 



3.���삳������@

 2005/08/09���݁B�Ή�NIC��NE2000�݊��A�_�v�^�݂̂Ȃ̂�
 ������A�G�~�����[�^��QEMU �� Bochs �݂̂ł̓���ƂȂ�܂��B
  (NE2000�݊��A�_�v�^�̎��@�Ȃ�ʂł����A�������肻��������)
 
 �ڍׂ́AYamami��Wiki
 Mona���쏊/�l�b�g���[�N�Ή�/Mones�ݒ���@ 
 http://f38.aaa.livedoor.jp/~yamami/pukiwiki/pukiwiki.php?%5B%5BMona%C0%BD%BA%EE%BD%EA%2F%A5%CD%A5%C3%A5%C8%A5%EF%A1%BC%A5%AF%C2%D0%B1%FE%2FMones%C0%DF%C4%EA%CA%FD%CB%A1%5D%5D
 
 �Ƃ肠����Mona���Aping�������炢�͂��܂��B


/*
Copyright (c) 2004 bayside
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(_SCROLLBAR_H_INCLUDED_)
#define _SCROLLBAR_H_INCLUDED_

class Scrollbar : public Control {
public:
	/** �����X�N���[���o�[ */
	static const int HORIZONTAL = 0;
	/** �����X�N���[���o�[ */
	static const int VERTICAL   = 1;
	
private:
	/** �X�N���[���o�[�̎�� */
	int orientation;
	/** �ŏ��l */
	int minimum;
	/** �ő�l */
	int maximum;
	/** ��x�ɑ�������� */
	int blocksize;
	/** ���݂̒l */
	int value;
	/** �u���b�N�C�x���g */
	Event blockEvent;
	
public:
	/** �f�t�H���g�R���X�g���N�^ */
	Scrollbar();

	/** �R���X�g���N�^ */
	Scrollbar(int orientation);

	/** �f�X�g���N�^ */
	virtual ~Scrollbar();

	/** �ŏ��l�𓾂� */
	inline int getMinimum() { return this->minimum; }

	/** �ő�l�𓾂� */
	inline int getMaximum() { return this->maximum; }

	/** ��x�ɑ�������ʂ𓾂� */
	inline int getBlocksize() { return this->blocksize; }

	/** �l�𓾂� */
	inline int getValue() { return this->value; }

	/** �ŏ��l��ݒ肷�� */
	inline void setMinimum(int n) { this->minimum = n; }

	/** �ő�l��ݒ肷�� */
	inline void setMaximum(int n) { this->maximum = n; }

	/** ��x�ɑ�������ʂ�ݒ肷�� */
	inline void setBlocksize(int n) { this->blocksize = n; }

	/** �l��ݒ肷�� */
	virtual void setValue(int value);

	/**
	 ���i�̑傫����ݒ肷��.
	 �����X�N���[���o�[�̎��͕�16�Œ�A�����X�N���[���o�[�̂Ƃ��͍���16�Œ�B
	 ����ȊO�̒l��ݒ肵�Ă�16�ɂȂ�B
	*/
	virtual void setRect(int x, int y, int w, int h);

	/** �`��n���h�� */
	virtual void onPaint(Graphics *g);

	/** �C�x���g�n���h�� */
	virtual void onEvent(Event *event);
};

#endif /* _SCROLLBAR_H_INCLUDED_ */

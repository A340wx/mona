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

#if !defined(_LABEL_H_INCLUDED_)
#define _LABEL_H_INCLUDED_

/**
 ���x���N���X
*/
class Label : public Control {
private:
	/** �\���ʒu�i���񂹁A�����񂹁A�E�񂹁j*/
	int align;
	/** �\�������� */
	String text;
	
public:
	/**
	 �R���X�g���N�^.
	 �`��ʒu�� ALIGN_LEFT�B
	 @param text ���x��
	 */
	Label(char *text);
	
	/**
	 �R���X�g���N�^
	 @param text ���x��
	 @param align �`��ʒu (ALIGN_LEFT / ALIGN_CENTER / ALIGN_RIGHT)
	 */
	Label(char *text, int align);
	
	/** �f�X�g���N�^ */
	virtual ~Label();
	
	/**
	 �e�L�X�g�ݒ�
	 @param text
	 */
	virtual void setText(char *text);
	
	/** �e�L�X�g�𓾂� */
	inline  char *getText() { return this->text.getBytes(); }
	
	/** �`��n���h�� */
	virtual void onPaint(Graphics *g);
};

#endif // _LABEL_H_INCLUDED_

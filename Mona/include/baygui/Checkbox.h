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

#if !defined(_CHECKBOX_H_INCLUDED_)
#define _CHECKBOX_H_INCLUDED_

/**
 �`�F�b�N�{�b�N�X�N���X
*/
class Checkbox : public Control {
private:
	/** �`�F�b�N���ꂽ���ǂ��� */
	bool checked;
	/** �{�^���̃��x�� */
	String label;
	
public:
	/**
	 �R���X�g���N�^
	 @param label ���x��
	 */
	Checkbox(char *label);
	
	/** �f�X�g���N�^ */
	virtual ~Checkbox();
	
	/**
	 �`�F�b�N���ꂽ���ǂ�����ݒ肷��
	 @param checked �t���O (true / false)
	 */
	virtual void setChecked(bool checked);
	
	/**
	 ���x����ݒ肷��
	 @param label ���x��
	 */
	virtual void setLabel(char *label);
	
	/** �`�F�b�N���ꂽ���ǂ����𓾂� */
	inline bool getChecked() { return this->checked; }
	
	/** ���x���𓾂� */
	inline char *getLabel() { return this->label.getBytes(); }
	
	/** �`��n���h�� */
	virtual void onPaint(Graphics *g);
	
	/** �C�x���g�n���h�� */
	virtual void onEvent(Event *event);
};

#endif // _CHECKBOX_H_INCLUDED_

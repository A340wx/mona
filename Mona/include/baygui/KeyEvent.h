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
IN NO KEYEVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(_KEYEVENT_H_INCLUDED_)
#define _KEYEVENT_H_INCLUDED_

/**
 �L�[�C�x���g�N���X
*/
class KeyEvent : public Event {
private:
	/** �L�[�R�[�h */
	int keycode;
	/** �C���L�[ */
	int modifiers;
	
public:
	/** �f�t�H���g�R���X�g���N�^ */
	KeyEvent() {
		setType(KEY_PRESSED);
		setSource(NULL);
		this->keycode = 0;
		this->modifiers = 0;
	}
	
	/**
	 �R���X�g���N�^
	 @param type type �C�x���g�^�C�v
	 @param source �C�x���g������
	 @param keycode �L�[�R�[�h
	 @param modifiers �C���L�[
	 */
	KeyEvent(int type, Control *source, int keycode, int modifiers) {
		setType(type);
		setSource(source);
		this->keycode = keycode;
		this->modifiers = modifiers;
	}
	
	/** �f�X�g���N�^ */
	virtual ~KeyEvent() {}
	
	/** �L�[�R�[�h�𓾂� */
	inline int getKeycode() { return this->keycode; }
	
	/** �L�[�R�[�h��ݒ肷�� */
	inline void setKeycode(int keycode) { this->keycode = keycode; }
	
	/** �C���L�[�𓾂� */
	inline int getModifiers() { return this->modifiers; }
	
	/** �C���L�[��ݒ肷�� */
	inline void setModifiers(int modifiers) { this->modifiers = modifiers; }
};

#endif // _KEYEVENT_H_INCLUDED_

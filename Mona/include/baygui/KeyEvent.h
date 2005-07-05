/*
Copyright (c) 2005 bayside

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation files 
(the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

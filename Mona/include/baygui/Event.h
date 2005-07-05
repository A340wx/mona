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

#if !defined(_EVENT_H_INCLUDED_)
#define _EVENT_H_INCLUDED_

class Control;

/**
 �C�x���g���N���X
*/
class Event : public Object {
public:
	//
	// �C�x���g�^�C�v�ꗗ
	//
	/** �L�[���� */
	static const int KEY_PRESSED     = 100;
	/** �L�[�����[�X */
	static const int KEY_RELEASED    = 101;
	/** �}�E�X�N���b�N */
	static const int MOUSE_PRESSED   = 200;
	/** �}�E�X�����[�X */
	static const int MOUSE_RELEASED  = 201;
	/** �}�E�X�h���b�O */
	static const int MOUSE_DRAGGED   = 202;
	/** �}�E�X�ړ� */
	static const int MOUSE_MOVED     = 203;
	/** �t�H�[�J�X�C�� */
	static const int FOCUS_IN        = 300;
	/** �t�H�[�J�X�A�E�g */
	static const int FOCUS_OUT       = 301;
	/** �^�C�}�[ */
	static const int TIMER           = 302;
	/** �e�L�X�g�m�� */
	static const int TEXT_CHANGED    = 303;
	/** ���ڑI�� */
	static const int ITEM_SELECTED   = 304;
	/** �u���b�N���� */
	static const int BLOCK_INCLEMENT = 305;
	/** �u���b�N���� */
	static const int BLOCK_DECLEMENT = 306;
	/** �J�X�^���C�x���g */
	static const int CUSTOM_EVENT    = 400;
	
	//
	// �L�[�R�[�h
	//
	/** Escape */
	static const int VKEY_ESC       =  0;
	/** BackSpace */
	static const int VKEY_BACKSPACE = 14;
	/** Tab */
	static const int VKEY_TAB       = 15;
	/** Enter */
	static const int VKEY_ENTER     = 28;
	/** PageUp */
	static const int VKEY_PGUP      = 354;
	/** PageDown */
	static const int VKEY_PGDOWN    = 355;
	/** Insert */
	static const int VKEY_INSERT    = 356;
	/** Delete */
	static const int VKEY_DELETE    = 357;
	/** �� */
	static const int VKEY_UP        = 358;
	/** �� */
	static const int VKEY_LEFT      = 359;
	/** ��  */
	static const int VKEY_RIGHT     = 360;
	/** �� */
	static const int VKEY_DOWN      = 361;
	/** Home */
	static const int VKEY_HOME      = 362;
	/** End */
	static const int VKEY_END       = 363;
	/** F11 */
	static const int VKEY_F11       = 382;
	/** F12 */
	static const int VKEY_F12       = 383;
	/** F1 */
	static const int VKEY_F1        = 398;
	/** F2 */
	static const int VKEY_F2        = 399;
	/** F3 */
	static const int VKEY_F3        = 400;
	/** F4 */
	static const int VKEY_F4        = 401;
	/** F5 */
	static const int VKEY_F5        = 402;
	/** F6 */
	static const int VKEY_F6        = 403;
	/** F7 */
	static const int VKEY_F7        = 404;
	/** F8 */
	static const int VKEY_F8        = 405;
	/** F9 */
	static const int VKEY_F9        = 406;
	/** F10 */
	static const int VKEY_F10       = 407;
	/** ���V�t�g */
	static const int VKEY_LSHIFT    = 412;
	/** Alt */
	static const int VKEY_ALT       = 415;
	/** Ctrl */
	static const int VKEY_CTRL      = 416;
	/** �E���j���[ */
	static const int VKEY_RMENU     = 424;
	/** �����j���[ */
	static const int VKEY_LMENU     = 425;
	/** �E�V�t�g */
	static const int VKEY_RSHIFT    = 427;
	
private:
	/** �C�x���g�^�C�v */
	int type;
	/** �C�x���g������ */
	Control *source;

#ifdef MONA
public:
	/** �w�b�_�[ */
	unsigned int header;
	/** ����(1) */
	unsigned int arg1;
	/** ����(2) */
	unsigned int arg2;
	/** ����(3) */
	unsigned int arg3;
	/** ���b�Z�[�W������ */
	unsigned int from;
	/** ������ */
	char str[128];
	/** ������̒��� */
	int length;
#endif

public:
	/** �f�t�H���g�R���X�g���N�^ */
	Event() {
		this->type = CUSTOM_EVENT;
		this->source = NULL;
	}
	
	/**
	 �R���X�g���N�^
	 @param type �C�x���g�^�C�v
	 @param source �C�x���g���������i
	 */
	Event(int type, Control *source) {
		this->type = type;
		this->source = source;
	}
	
	/** �f�X�g���N�^ */
	virtual ~Event() {}
	
	/** �C�x���g�^�C�v�𓾂� */
	inline int getType() { return this->type; }
	
	/** �C�x���g�^�C�v��ݒ肷�� */
	inline void setType(int type) { this->type = type; }
	
	/** �C�x���g�̔������i�𓾂� */
	inline Control* getSource() { return this->source; }
	
	/** �C�x���g�̔������i��ݒ肷�� */
	inline void setSource(Control *c) { this->source = c; }
};

#endif // _EVENT_H_INCLUDED_

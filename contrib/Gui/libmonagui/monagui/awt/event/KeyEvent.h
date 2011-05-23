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

namespace monagui {
	/**
	 �L�[�C�x���g�N���X
	*/
	class KeyEvent : public Event {
	public:
		//
		// �L�[�R�[�h
		//
		/** Escape */
		static const int VKEY_ESC       = 0;
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
		KeyEvent(int type, Component* source, int keycode, int modifiers) {
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
}

#endif // _KEYEVENT_H_INCLUDED_

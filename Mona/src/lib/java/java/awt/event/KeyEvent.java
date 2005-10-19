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

package java.awt.event;

/**
 �L�[�C�x���g�N���X
*/
public class KeyEvent extends java.awt.AWTEvent {
	//
	// �L�[�R�[�h
	//
	/** Escape */
	public static final int VKEY_ESC       = 0;
	/** BackSpace */
	public static final int VKEY_BACKSPACE = 14;
	/** Tab */
	public static final int VKEY_TAB       = 15;
	/** Enter */
	public static final int VKEY_ENTER     = 28;
	/** PageUp */
	public static final int VKEY_PGUP      = 354;
	/** PageDown */
	public static final int VKEY_PGDOWN    = 355;
	/** Insert */
	public static final int VKEY_INSERT    = 356;
	/** Delete */
	public static final int VKEY_DELETE    = 357;
	/** �� */
	public static final int VKEY_UP        = 358;
	/** �� */
	public static final int VKEY_LEFT      = 359;
	/** ��  */
	public static final int VKEY_RIGHT     = 360;
	/** �� */
	public static final int VKEY_DOWN      = 361;
	/** Home */
	public static final int VKEY_HOME      = 362;
	/** End */
	public static final int VKEY_END       = 363;
	/** F11 */
	public static final int VKEY_F11       = 382;
	/** F12 */
	public static final int VKEY_F12       = 383;
	/** F1 */
	public static final int VKEY_F1        = 398;
	/** F2 */
	public static final int VKEY_F2        = 399;
	/** F3 */
	public static final int VKEY_F3        = 400;
	/** F4 */
	public static final int VKEY_F4        = 401;
	/** F5 */
	public static final int VKEY_F5        = 402;
	/** F6 */
	public static final int VKEY_F6        = 403;
	/** F7 */
	public static final int VKEY_F7        = 404;
	/** F8 */
	public static final int VKEY_F8        = 405;
	/** F9 */
	public static final int VKEY_F9        = 406;
	/** F10 */
	public static final int VKEY_F10       = 407;
	/** ���V�t�g */
	public static final int VKEY_LSHIFT    = 412;
	/** Alt */
	public static final int VKEY_ALT       = 415;
	/** Ctrl */
	public static final int VKEY_CTRL      = 416;
	/** �E���j���[ */
	public static final int VKEY_RMENU     = 424;
	/** �����j���[ */
	public static final int VKEY_LMENU     = 425;
	/** �E�V�t�g */
	public static final int VKEY_RSHIFT    = 427;

	/** �L�[�R�[�h */
	private int keycode;
	/** �C���L�[ */
	private int modifiers;
	
	/** �f�t�H���g�R���X�g���N�^ */
	public KeyEvent() {
		super(KEY_PRESSED, null);
		this.keycode = 0;
		this.modifiers = 0;
	}
	
	/**
	 �R���X�g���N�^
	 @param type type �C�x���g�^�C�v
	 @param source �C�x���g������
	 @param keycode �L�[�R�[�h
	 @param modifiers �C���L�[
	 */
	public KeyEvent(int type, Object source, int keycode, int modifiers) {
		super(type, source);
		this.keycode = keycode;
		this.modifiers = modifiers;
	}
	
	/** �L�[�R�[�h�𓾂� */
	public int getKeycode() { return this.keycode; }
	
	/** �L�[�R�[�h��ݒ肷�� */
	public void setKeycode(int keycode) { this.keycode = keycode; }
	
	/** �C���L�[�𓾂� */
	public int getModifiers() { return this.modifiers; }
	
	/** �C���L�[��ݒ肷�� */
	public void setModifiers(int modifiers) { this.modifiers = modifiers; }
}

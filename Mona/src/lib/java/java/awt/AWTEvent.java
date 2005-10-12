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

package java.awt;

/**
 �C�x���g���N���X
*/
public class AWTEvent {
	//
	// �C�x���g�^�C�v�ꗗ
	//
	/** �L�[���� */
	public static final int KEY_PRESSED      = 100;
	/** �L�[�����[�X */
	public static final int KEY_RELEASED     = 101;
	/** �}�E�X�N���b�N */
	public static final int MOUSE_PRESSED    = 200;
	/** �}�E�X�����[�X */
	public static final int MOUSE_RELEASED   = 201;
	/** �}�E�X�h���b�O */
	public static final int MOUSE_DRAGGED    = 202;
	/** �}�E�X�ړ� */
	public static final int MOUSE_MOVED      = 203;
	/** �t�H�[�J�X�C�� */
	public static final int FOCUS_IN         = 300;
	/** �t�H�[�J�X�A�E�g */
	public static final int FOCUS_OUT        = 301;
	/** �^�C�}�[ */
	public static final int TIMER            = 302;
	/** �e�L�X�g�m�� */
	public static final int TEXT_CHANGED     = 303;
	/** ���ڑI�� */
	public static final int ITEM_SELECTED    = 304;
	/** �u���b�N���� */
	public static final int BLOCK_INCLEMENT  = 305;
	/** �u���b�N���� */
	public static final int BLOCK_DECLEMENT  = 306;
	/** �{�^������ */
	public static final int ACTION_PERFORMED = 307;
	/** �J�X�^���C�x���g */
	public static final int CUSTOM_EVENT     = 400;
	
	/** �C�x���g�^�C�v */
	private int type;
	/** �C�x���g������ */
	private Component source;

	//
	// Mona�p�C�x���g
	//
	/** �w�b�_�[ */
	public int header;
	/** ����(1) */
	public int arg1;
	/** ����(2) */
	public int arg2;
	/** ����(3) */
	public int arg3;
	/** ���b�Z�[�W������ */
	public int from;
	/** ������ */
	public char str[]; //128
	/** ������̒��� */
	public int length;

	/** �f�t�H���g�R���X�g���N�^ */
	public AWTEvent() {
		this.type = CUSTOM_EVENT;
		this.source = NULL;
	}
	
	/**
	 �R���X�g���N�^
	 @param type �C�x���g�^�C�v
	 @param source �C�x���g���������i
	 */
	public AWTEvent(int type, Component source) {
		this.type = type;
		this.source = source;
	}
	
	/** �C�x���g�^�C�v�𓾂� */
	public int getType() { return this.type; }
	
	/** �C�x���g�^�C�v��ݒ肷�� */
	public void setType(int type) { this.type = type; }
	
	/** �C�x���g�̔������i�𓾂� */
	public Component getSource() { return this.source; }
	
	/** �C�x���g�̔������i��ݒ肷�� */
	public void setSource(Component c) { this.source = c; }
}

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
 �}�E�X�C�x���g�N���X
*/
public class MouseEvent extends java.awt.AWTEvent {
	public static final int BUTTON_LEFT = 1;
	public static final int BUTTON_RIGHT = 2;
	public static final int BUTTON_MIDDLE = 3;
	
	/** X���W */
	private int x;
	/** Y���W */
	private int y;
	/** �{�^����� */
	private int button;
	
	/** �f�t�H���g�R���X�g���N�^ */
	public MouseEvent() {
		setType(MOUSE_PRESSED);
		setSource(null);
		this.x = this.y = 0;
		this.button = 0;
	}
	
	/**
	 �R���X�g���N�^.
	 x, y �̓��C���E�B���h�E�̓����̈�̍���ɑ΂��鑊�΍��W�ł���B
	 @param type type �C�x���g�^�C�v
	 @param source �C�x���g������
	 @param x X���W�i��΍��W�j
	 @param y Y���W�i��΍��W�j
	*/
	public MouseEvent(int type, java.awt.Component source, int x, int y) {
		setType(type);
		setSource(source);
		this.x = x;
		this.y = y;
	}
	
	/** X���W�𓾂� */
	public int getX() { return this.x; }
	
	/** X���W��ݒ肷�� */
	public void setX(int x) { this.x = x; }
	
	/** Y���W�𓾂� */
	public int getY() { return this.y; }
	
	/** Y���W��ݒ肷�� */
	public void setY(int y) { this.y = y; }
	
	/** �{�^����ʂ𓾂� */
	public int getButton() { return this.button; }
	
	/** �{�^����ʂ�ݒ肷�� */
	public void setButton(int button) { this.button = button; }
}

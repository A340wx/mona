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

import java.awt.event.FocusEvent;

public class Component {
	/** �e���i */
	private Container parent;
	/** �����E�񊈐� */
	private boolean enabled;
	/** �t�H�[�J�X�L�� */
	private boolean focused;
	/** �\���E��\�� */
	private boolean visible;
	/** x�i��΍��W�j */
	private int x;
	/** y�i��΍��W�j */
	private int y;
	/** ���� */
	private int height;
	/** �� */
	private int width;
	/** �w�i�F */
	private int backColor;
	/** �O�i�F */
	private int foreColor;
	/** �t�H���g�X�^�C�� */
	private int fontStyle;
	/** ���i�̑傫�� */
	private Rectangle bounds;
	/** �`��̈� */
	private Graphics graphics;
	/** �`��o�b�t�@�[ */
	private Image image;
	/** �t�H���g��� */
	private FontMetrics metrics;

	/** �t�H�[�J�X�C�x���g */
	protected AWTEvent focusEvent;
	
	/** �R���X�g���N�^ */
	public Component() {
		this.parent = null;
		this.enabled = true;
		this.focused = false;
		this.visible = true;
		this.x = this.y = this.height = this.width = 10;
		this.backColor = Color.lightGray;
		this.foreColor = Color.black;
		this.fontStyle = Font.PLAIN;
		this.bounds = new Rectangle();
		this.graphics = null;
		this.image = null;
		this.metrics = new FontMetrics();
		this.focusEvent = new FocusEvent();
		this.focusEvent.setType(FocusEvent.FOCUS_IN);
		this.focusEvent.setSource(this);
	}

	/**
	 ���i�����n���h��.
	 ���removeNotify()�ĂԂƍď������ł���B
	 */
	public void addNotify() {
		if (this.image != null) return;

		// �����o�b�t�@�[�A�`��I�u�W�F�N�g�̐���
		this.image = new Image(width, height);
		this.graphics = new Graphics(this.image);
	}

	/**
	 ���i�j���n���h��.
	 ���addNotify()���ĂԂƍď������ł���B
	*/
	public void removeNotify() {
		//delete(image);
		//delete(graphics);
		//delete(metrics);
	}

	/** �C�x���g�n���h�� */
	public void processEvent(AWTEvent event) {
	}

	/** �`��n���h�� */
	public void paint(Graphics g) {
	}

	/** �C�x���g���� */
	public void dispatchEvent(AWTEvent event) {
		processEvent(event);
		// �e���i�ɃC�x���g�𓊂���
		if (getParent() != null) {
			getParent().processEvent(event);
		}
	}

	/** �ĕ`�� */
	public void repaint() {
		if (this.image == null) return;
		setFontStyle(this.fontStyle);
		paint(this.graphics);
		update();
	}

	/** ���i�X�V */
	public void update() {
		update(getX(), getY(), getWidth(), getHeight());
	}

	/** ���i�����X�V */
	public void update(int x, int y, int w, int h) {
		/*Frame c = (Frame)getMainWindow();
		c.getGraphics().drawImage(this.image, getX(), getY());
		c.update(c.getX() + c.getInsets().left + x, c.getY() + c.getInsets().top + y, w, h);*/
	}

	/** �e���i�𓾂� */
	public Container getParent() { return this.parent; }
	
	/** �����E�񊈐��𓾂� */
	public boolean getEnabled() { return this.enabled; }
	
	/** �t�H�[�J�X��Ԃ𓾂� */
	public boolean getFocused() { return this.focused; }
	
	/** �\���E��\���𓾂� */
	public boolean getVisible() { return this.visible; }
	
	/** X���W�𓾂� */
	public int getX() { return this.x; }
	
	/** Y���W�𓾂� */
	public int getY() { return this.y; }
	
	/** ���𓾂� */
	public int getWidth() { return this.width; }
	
	/** �����𓾂� */
	public int getHeight() { return this.height; }
	
	/** ���i�̑傫�� */
	public Rectangle getBounds() { return this.bounds; }
	
	/** �w�i�F�𓾂� */
	public int getBackground() { return this.backColor; }
	
	/** �O�i�F�𓾂� */
	public int getForeground() { return this.foreColor; }
	
	/** �t�H���g�X�^�C���𓾂� */
	public int getFontStyle() { return this.fontStyle; }
	
	/** �`��I�u�W�F�N�g�𓾂� */
	public Graphics getGraphics() { return this.graphics; }
	
	/**
	 �����o�b�t�@�[�𓾂�.
	 VRAM�̂悤�ɒ��ڕ`�悵�����Ƃ��ɗp����B
	 Graphics�N���X�������Ă���悤�ȕ֗��ȃ��\�b�h�͂Ȃ��B
	 �`���update()���ĂԂ��ƂŎ��ۂ̕`�悪�����B
	 */
	public Image getBuffer() { return this.image; }
	
	/** �t�H���g���𓾂� */
	public FontMetrics getFontMetrics() { return this.metrics; }
	
	/**
	 ���C���E�B���h�E�𓾂�.
	 ���C���E�B���h�E�Ƃ͑S�Ă̕��i������Ă����ԉ��̃E�B���h�E�B
	 ���C���E�B���h�E�͊e�A�v���P�[�V�������ƂɕK���P���݂��Ă���B
	 */
	public Component getMainWindow() {
		return (this.parent == null) ? this : this.parent.getMainWindow();
	}

	/**
	 ������Ԃ�ݒ肷��
	 @param enabled ������� (true / false)
	 */
	public void setEnabled(boolean enabled) {
		this.enabled = enabled;
	}

	/**
	 �t�H�[�J�X��Ԃ�ݒ肷��.
	 ���̃��\�b�h���ĂԂƊY�����i��FOCUS_IN�܂���FOCUS_OUT�C�x���g����������B
	 @param focused �t�H�[�J�X��� (true / false)
	 */
	public void setFocused(boolean focused) {
		if (this.focused == true && focused == false) {
			//syscall_print("FOCUS_OUT,");
			this.focused = focused;
			this.focusEvent.setType(FocusEvent.FOCUS_OUT);
			dispatchEvent(this.focusEvent);
		} else if (this.focused == false && focused == true) {
			//syscall_print("FOCUS_IN,");
			this.focused = focused;
			this.focusEvent.setType(FocusEvent.FOCUS_IN);
			dispatchEvent(this.focusEvent);
		}
	}

	/**
	 �\����Ԃ�ݒ肷��
	 @param visible �\����� (true / false)
	 */
	public void setVisible(boolean visible) {
		this.visible = visible;
	}

	/**
	 �傫����ݒ肷��
	 @param x x���W
	 @param y y���W
	 @param width ��
	 @param height ����
	*/
	public void setBounds(int x, int y, int width, int height) {
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.bounds.setBounds(x, y, width, height);
	}

	/**
	 �ʒu��ύX����
	 @param x X���W
	 @param y Y���W
	*/
	public void setLocation(int x, int y) {
		if (this.x == x && this.y == y) return;
		
		this.x = x;
		this.y = y;
		this.bounds.setLocation(x, y);
	}

	/**
	 �e���i��ݒ肷��
	 @param parent �e���i
	*/
	public void setParent(Container parent) {
		this.parent = parent;
	}

	/** �w�i�F��ݒ肷�� */
	public void setBackground(int backColor) {
		this.backColor = backColor;
	}

	/** �O�i�F��ݒ肷�� */
	public void setForeground(int foreColor) {
		this.foreColor = foreColor;
	}

	/**
	 �t�H���g�X�^�C���i�ʏ�A�����A�Ύ��A�Œ蕝�j��ݒ肷��.
	 �e�X�^�C����"|"�őg�ݍ��킹�邱�Ƃ��\�B
	 @param style �t�H���g�X�^�C�� (Font.PLAIN / Font.BOLD / Font.ITALIC / Font.FIXED )
	*/
	public void setFontStyle(int style) {
		if (this.metrics != null) {
			this.metrics.setFontStyle(style);
		}
		if (this.graphics != null) {
			this.graphics.setFontStyle(style);
		}
		this.fontStyle = style;
	}
}

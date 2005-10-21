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

import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.TimerEvent;

/**
 �E�B���h�E�N���X
*/
public class Window extends Container {
	//
	// �E�B���h�E�̏��
	//
	/** �ʏ펞 */
	public static final int STATE_NORMAL = 0;
	/** �E�B���h�E�ړ��� */
	public static final int STATE_MOVING = 1;
	
	/** �C���L�[ */
	private int modifiers;
	/** �E�B���h�E�̏�� */
	private int state;
	/** �ȑO�̃}�E�X��X���W */
	private int preX;
	/** �ȑO�̃}�E�X��Y���W */
	private int preY;
	/** �I�t�Z�b�gX */
	private int offsetX;
	/** �I�t�Z�b�gY */
	private int offsetY;
	/** �I�[�o�[���b�v�E�B���h�E�̏�� */
	private int overlap;
	/** ���s���t���O */
	private boolean isRunning;
	/** �^�C�}�[ID */
	private int timerID;
	/** �J�X�^���C�x���g */
	private AWTEvent customEvent;
	/** �L�[�C�x���g */
	private KeyEvent keyEvent;
	/** �}�E�X�C�x���g */
	private MouseEvent mouseEvent;
	/** �^�C�}�[�C�x���g */
	private TimerEvent timerEvent;

	/** �t�`�̏�� */
	protected int border;
	/** �z�u�ʒu */
	protected Insets insets;
	/** �`��̈� */
	protected Graphics _g;
	/** �`��o�b�t�@�[ */
	protected Image _buffer;
	/** �����`��̈� */
	protected Graphics __g;
	/** �����`��o�b�t�@�[ */
	protected Image __buffer;
	/** GUI�T�[�o�[ID */
	//protected int guisvrID;
	/** GUI�T�[�o�[��̃E�B���h�E�I�u�W�F�N�g */
	//protected guiserver_window* _window;

	/** ����{�^�����N���b�N���ꂽ���ǂ��� */
	protected boolean getCloseButtonClicked(int px, int py) {
		return false;
	}
	
	/** �^�C�g���o�[���N���b�N���ꂽ���ǂ��� */
	protected boolean getTitlebarClicked(int px, int py) {
		return (0 <= px && px < getWidth() && 0 <= py && py < getHeight()) ? true : false;
	}

	/** �R���X�g���N�^ */
	public Window() {
		System.out.println("hoge");
		this.modifiers = this.state = this.preX = this.preY = this.offsetX = this.offsetY = this.overlap = 0;
		this.border = 0;//WINDOWFLAGS_NOBORDER;
		this.isRunning = false;
		this.timerID = 0;
		this._g = null;
		this.__g = null;
		this._buffer = null;
		this.__buffer = null;
		this.insets = new Insets();
		this.insets.top = this.insets.bottom = this.insets.left = this.insets.right = 0;
		this.keyEvent = new KeyEvent(KeyEvent.KEY_PRESSED, this, 0, 0);
		this.mouseEvent = new MouseEvent(MouseEvent.MOUSE_PRESSED, this, 0, 0);
		this.timerEvent = new TimerEvent(TimerEvent.TIMER, this);
		this.customEvent = new AWTEvent(AWTEvent.CUSTOM_EVENT, this);
		System.out.println("fuga");
	}
	
	/**
	 ���i�������n���h��.
	 Window.run()�ŌĂ΂��B
	 �Ǝ��̏�����t�^�������Ƃ���Window.addNotify()���ɌĂԂ��ƁB
	*/
	public void addNotify() {
		if (this._buffer != null) return;
		
		/* �`��o�b�t�@�[�A�`��I�u�W�F�N�g�̐��� */
		this._buffer = new Image
			(getWidth() - getInsets().left - getInsets().right, getHeight() - getInsets().top - getInsets().bottom);
		this._g = new Graphics(this._buffer);
		this.__buffer = new Image(getWidth(), getHeight());
		this.__g = new Graphics(this.__buffer);
		
		/* �E�B���h�E���A�N�e�B�u�ɂ��� */
		setFocused(true);
	}
	
	/**
	 ���i�j���n���h��.
	 �f�X�g���N�^���ŌĂ΂��B
	 �Ǝ��̏�����t�^�������Ƃ���Window.removeNotify()����ŌĂԂ��ƁB
	 */
	public void removeNotify() {
		setVisible(false);
	}

	/** �n���h���𓾂� */
	//public int getHandle() { return (this._window != null) ? this._window.Handle : 0; }
	
	/** �z�u�ʒu�𓾂� */
	public Insets getInsets() {
		return this.insets;
	}
	
	/** �`��I�u�W�F�N�g�𓾂� */
	public Graphics getGraphics() {
		return this._g;
	}
	
	/** �����o�b�t�@�[�𓾂� */
	public Image getBuffer() {
		return this._buffer;
	}
	
	/**
	 �\����Ԃ�ݒ肷��
	 @param visible �\����� (true / false)
	 */
	public void setVisible(boolean visible) {
		super.setVisible(visible);
		update();
	}
	
	/**
	 �ʒu��ύX����
	 @param x X���W
	 @param y Y���W
	*/
	public void setLocation(int x, int y) {
		super.setLocation(x, y);
		update();
	}
	
	/**
	 �^�C�}�[���Z�b�g����
	 @param duration �^�C�}�[�C�x���g����������܂ł̎���[ms]
	 */
	public void setTimer(int duration) {
		/* �񊈐��̂Ƃ��̓^�C�}�[�𔭐������Ȃ� */
		if (getEnabled() == false) return;
	}
	
	/** �ĕ`�� */
	public void repaint() {
		if (this.__g == null) return;
		super.repaint();
	}
	
	/** ���i�X�V */
	public void update() {
		update(this.getX(), this.getY(), this.getWidth(), this.getHeight());
	}
	
	/** ���i�����X�V */
	public void update(int x, int y, int w, int h) {
	}
	
	/** �C�x���g���� */
	public void dispatchEvent(AWTEvent event) {
		if (event.getType() >= MouseEvent.MOUSE_PRESSED && event.getType() <= MouseEvent.MOUSE_MOVED) {
			MouseEvent me = (MouseEvent)event;
			int px = me.getX() - getX();
			int py = me.getY() - getY();
			if (event.getType() == MouseEvent.MOUSE_PRESSED) {
				/* ����{�^���N���b�N */
				if (getCloseButtonClicked(px, py)) {
					stop();
					return;
				/* �^�C�g���o�[�N���b�N */
				} else if (getTitlebarClicked(px, py)) {
					this.state = STATE_MOVING;
					/* �L���v�`���[�v���ƃE�B���h�E�ړ��p�I�u�W�F�N�g�쐬�v�� */
					/*MessageInfo info;
					MonAPI.Message.sendReceive(null, this.guisvrID, MSG_GUISERVER_MOUSECAPTURE, 
						getHandle(), 1);
					MonAPI.Message.sendReceive(&info, this.guisvrID, MSG_GUISERVER_CREATEOVERLAP, 
						getX(), getY(), MAKE_DWORD(getWidth(), getHeight()));
					this.overlap = info.arg2;*/
					this.preX = px;
					this.preY = py;
				/* �E�B���h�E���N���b�N */
				} else {
					/* ��΍��W�����΍��W */
					me.setX(px - getInsets().left);
					me.setY(py - getInsets().top);
					super.dispatchEvent(me);
				}
			} else if (event.getType() == MouseEvent.MOUSE_RELEASED) {
				/* �^�C�g���o�[�����[�X */
				if (this.state == STATE_MOVING) {
					this.state = STATE_NORMAL;
					/* �L���v�`���[�j���v���ƃE�B���h�E�ړ��p�I�u�W�F�N�g�j���v�� */
					/*MonAPI.Message.sendReceive(null, this.guisvrID, MSG_GUISERVER_DISPOSEOVERLAP, 
						this.overlap);
					MonAPI.Message.sendReceive(null, this.guisvrID, MSG_GUISERVER_MOUSECAPTURE, 
						getHandle(), 0);*/
					this.overlap = 0;
					/* �E�B���h�E�����ۂɈړ������� */
					setLocation(me.getX() - this.preX, me.getY() - this.preY);
				/* �E�B���h�E�������[�X */
				} else {
					/* ��΍��W�����΍��W */
					me.setX(px - getInsets().left);
					me.setY(py - getInsets().top);
					super.dispatchEvent(me);
				}
			} else if (event.getType() == MouseEvent.MOUSE_DRAGGED) {
				/* �E�B���h�E�ړ� */
				if (this.state == STATE_MOVING) {
					/* �E�B���h�E�ړ��p�I�u�W�F�N�g�̈ړ� */
					/*MonAPI.Message.sendReceive(null, this.guisvrID, MSG_GUISERVER_MOVEOVERLAP, this.overlap,
						MAKE_DWORD(me.getX() - this.preX, me.getY() - this.preY), 
						MAKE_DWORD(getWidth(), getHeight()));*/
				/* �E�B���h�E���ړ� */
				} else {
					/* ��΍��W�����΍��W */
					me.setX(px - getInsets().left);
					me.setY(py - getInsets().top);
					super.dispatchEvent(me);
				}
			} else {
				/* ��΍��W�����΍��W */
				me.setX(px - getInsets().left);
				me.setY(py - getInsets().top);
				super.dispatchEvent(me);
			}
		} else {
			/* �L�[�C�x���g�A�^�C�}�[�C�x���g���͂��̂܂܃X���[ */
			super.dispatchEvent(event);
		}
	}
	
	/** �A�v���P�[�V�������[�v */
	public void start() {
		/* �\���J�n */
		addNotify();
		
		/* �ĕ`�� */
		repaint();
		
		/* ���s�J�n */
		this.isRunning = true;
	}
	
	/** �A�v���P�[�V�������[�v�𔲂��� */
	public void stop() {
		this.isRunning = false;
	}
}

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
import java.awt.event.KeyEvent;
import java.awt.event.TextEvent;

/**
 �e�L�X�g�{�b�N�X�N���X
*/
public class TextField extends Component {
	/** �e�L�X�g�I���ʒu */
	private int dataPtr;
	/** �e�L�X�g�̒��� */
	private int dataLen;
	/** �I�t�Z�b�gX���W */
	private int offx;
	/** �I�t�Z�b�gY���W */
	private int offy;
	/** �e�L�X�g */
	private char[] data;
	/** IME�C�x���g */
	private TextEvent textEvent;
	/** �o�b�t�@�[�f�t�H���g�� */
	private static final int BUFFER_SIZE = 16;
	
	/** �R���X�g���N�^ */
	public TextField() {
		this.dataPtr = -1;
		this.dataLen = 0;
		this.offx = 3;
		this.offy = 3;
		this.data = new char [BUFFER_SIZE];
		this.textEvent = new TextEvent(TextEvent.TEXT_CHANGED, this);
		setBackground(Color.white);
	}
	
	/** 1�����}������ */
	private void insertCharacter(char c) {
		// �z��g��
		if (this.dataLen == this.data.length) {
			char[] new_text = new char[this.data.length * 2];
			for (int i = 0; i < this.dataLen; i++) {
				new_text[i] = this.data[i];
			}
			this.data = new_text;
		}
		// 1�����}��
		if (this.dataPtr >= 0) {
			for (int i = this.dataLen; i > this.dataPtr; i--) {
				this.data[i] = this.data[i - 1];
			}
		}
		this.data[++this.dataPtr] = c;
		this.dataLen++;
	}
	
	/** �ꕶ���폜���� */
	private void deleteCharacter() {
		int i = 0;
		for (i = this.dataPtr; i < this.dataLen - 1; i++) {
			this.data[i] = this.data[i + 1];
		}
		data[i] = '\0';
		this.dataPtr--;
		this.dataLen--;
	}
	
	/**
	 �e�L�X�g��ݒ肷��
	 @param text
	 */
	public void setText(String text) {
		for (int i = 0; i < this.data.length; i++) {
			this.data[i] = '\0';
		}
		this.dataPtr = -1;
		this.dataLen = 0;
		for (int i = 0; i < text.length(); i++) {
			insertCharacter(text.charAt(i));
		}
	}
	
	/** �e�L�X�g�𓾂� */
	public String getText() { return new String(this.data, 0, this.dataLen); }
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int w = getWidth();
		int h = getHeight();

		// �O�g
		if (getFocused() == true && getEnabled() == true) {
			g.setColor(0, 128, 255);
			g.drawRect(0, 0, w, h);
		} else {
			if (getParent() != null) {
				g.setColor(getParent().getBackground());
			} else {
				g.setColor(Color.lightGray);
			}
			g.drawRect(0, 0, w, h);
		}
		
		// ���g
		g.setColor(getBackground());
		g.fillRect(1, 1, w - 2, h - 2);
		g.setColor(getForeground());
		g.drawRect(1, 1, w - 2, h - 2);

		// ����
		int fh = getFontMetrics().getHeight(getText());
		if (getEnabled() == true) {
			g.setColor(getForeground());
		} else {
			g.setColor(Color.gray);
		}
		g.drawString(getText(), this.offx, (h - fh) / 2);

		// �L�����b�g
		if (getFocused() == true && getEnabled() == true) {
			int fw = 0;
			for (int i = 0; i <= this.dataPtr; i++) {
				fw += getFontMetrics().getCharWidth(this.data[i]);
			}
			g.drawLine(offx + fw, (h - fh) / 2, offx + fw, (h - fh) / 2 + fh);
		}
	}
	
	/** �C�x���g�n���h�� */
	public void processEvent(AWTEvent event) {
		// �񊈐��̎��̓C�x���g���󂯕t���Ȃ�
		if (getEnabled() == false) return;
		
		// �L�[����
		if (event.getType() == KeyEvent.KEY_PRESSED) {
			int keycode = ((KeyEvent)event).getKeycode();
			if (keycode == KeyEvent.VKEY_BACKSPACE) {
				if (this.dataPtr >= 0) {
					// �o�b�N�X�y�[�X
					deleteCharacter();
					repaint();
				}
			} else if (keycode == KeyEvent.VKEY_LEFT) {
				// ���ړ�
				if (this.dataPtr >= 0) {
					this.dataPtr--;
					repaint();
				}
			} else if (keycode == KeyEvent.VKEY_RIGHT) {
				// ���ړ�
				if (this.dataPtr < this.dataLen - 1) {
					this.dataPtr++;
					repaint();
				}
			} else if (keycode == KeyEvent.VKEY_ENTER) {
				// �m��
				if (getParent() != null) {
					getParent().processEvent(this.textEvent);
				}
				return;
			} else if (keycode < 128) {
				// 1�����}��
				insertCharacter((char)keycode);
				repaint();
			}
		// �t�H�[�J�X��ԕύX
		} else if (event.getType() == FocusEvent.FOCUS_IN || event.getType() == FocusEvent.FOCUS_OUT) {
			repaint();
			if (getParent() != null) {
				getParent().processEvent(this.focusEvent);
			}
		}
	}
}

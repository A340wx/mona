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

import java.awt.event.TextEvent;

/**
 �e�L�X�g�{�b�N�X�N���X
*/
public class TextField extends Component {
	/** �e�L�X�g�t�B�[���h������ő咷 */
	private static final int MAX_TEXT_LEN  = 128;
	/** �e�L�X�g�I���ʒu */
	private int textPtr;
	/** �e�L�X�g�̒��� */
	private int textLen;
	/** �I�t�Z�b�gX���W */
	private int offx;
	/** �I�t�Z�b�gY���W */
	private int offy;
	/** �e�L�X�g */
	private char[] text;
	/** IME�C�x���g */
	private TextEvent textEvent;
	
	/** 1�����}������ */
	private void insertCharacter(char c) {
	}
	
	/** �ꕶ���폜���� */
	private void deleteCharacter() {
	}

	/** �R���X�g���N�^ */
	public TextField() {
		this.text = new char [MAX_TEXT_LEN];
	}
	
	/**
	 �e�L�X�g��ݒ肷��
	 @param text
	 */
	public void setText(String text) {
		for (int i = 0; i < this.textLen; i++) {
			this.text[i] = '\0';
		}
		int I = text.length() > this.textLen ? this.textLen : text.length();
		for (int i = 0; i < I; i++) {
			this.text[i] = text.charAt(i);
		}
		this.textLen = I;
	}
	
	/** �e�L�X�g�𓾂� */
	public String getText() { return new String(this.text, 0, this.textLen); }
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
	}
	
	/** �C�x���g�n���h�� */
	public void processEvent(AWTEvent event) {
	}
}

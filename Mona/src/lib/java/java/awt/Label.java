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
 ���x���N���X
*/
public class Label extends Component {
	/** ���� */
	public static final int LEFT   = 1;
	/** ������ */
	public static final int CENTER = 2;
	/** �E�� */
	public static final int RIGHT  = 3;

	/** �\���ʒu�i���񂹁A�����񂹁A�E�񂹁j*/
	private int align;
	/** �\�������� */
	private String text;
	
	/** �f�t�H���g�R���X�g���N�^ */
	public Label() {
		this.align = Label.LEFT;
		this.text = "Label";
	}
	
	/**
	 �R���X�g���N�^.
	 �`��ʒu�� ALIGN_LEFT�B
	 @param text ���x��
	 */
	public Label(String text) {
		this.align = Label.LEFT;
		this.text = text;
	}
	
	/**
	 �R���X�g���N�^
	 @param text ���x��
	 @param align �`��ʒu (ALIGN_LEFT / ALIGN_CENTER / ALIGN_RIGHT)
	 */
	public Label(String text, int align) {
		this.align = align;
		this.text = text;
	}
	
	/**
	 �e�L�X�g�ݒ�
	 @param text
	 */
	public void setText(String text) {
		this.text = text;
		repaint();
	}
	
	/** �e�L�X�g�𓾂� */
	public String getText() { return this.text; }
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int w = getWidth();
		int h = getHeight();
		
		// �h��Ԃ�
		g.setColor(getBackground());
		g.fillRect(0, 0, w, h);

		// ����
		int fw = getFontMetrics().getWidth(getText());
		int fh = getFontMetrics().getHeight(getText());
		if (getEnabled() == true) {
			g.setColor(getForeground());
		} else {
			g.setColor(Color.gray);
		}
		if (this.align == Label.RIGHT) {
			g.drawString(getText(), (w - fw), (h - fh) / 2);
		} else if (this.align == Label.CENTER) {
			g.drawString(getText(), (w - fw) / 2, (h - fh) / 2);
		} else {
			g.drawString(getText(), 0, (h - fh) / 2);
		}
	}
}

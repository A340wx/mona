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

import java.util.Vector;
import java.awt.event.FocusEvent;
import java.awt.event.ItemEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

/**
 ���X�g�{�b�N�X�N���X
*/
public class ListBox extends Component {
	/** �I���ʒu */
	private int selectedIndex;
	/** �\���J�n�ʒu */
	private int offsetIndex;
	/** �\���\�s�� */
	private int visibleRows;
	/** �f�[�^���X�g */
	private Vector dataList;
	/** �I���C�x���g */
	private ItemEvent itemEvent;

	/** �R���X�g���N�^ */
	public ListBox() {
		this.selectedIndex = -1;
		this.offsetIndex = 0;
		this.visibleRows = 0;
		this.dataList = new Vector();
		this.itemEvent = new ItemEvent(ItemEvent.ITEM_SELECTED, this);
		setBackground(Color.white);
	}
	
	/** �I���ʒu�𓾂� */
	public int getSelectedIndex() { return this.selectedIndex; }
	
	/** �I�����ڂ𓾂� */
	public String getSelectedItem() {
		return dataList.get(this.selectedIndex).toString();
	}
	
	/** index �Ԗڂ�I������ */
	public void select(int index) {
		if (0 <= index && index < this.dataList.size()) {
			this.selectedIndex = index;
			repaint();
		}
	}
	
	/** ���ڂ�ǉ����� */
	public void add(String item) {
		this.dataList.add(item);
	}
	
	/** index �Ԗڂ̍��ڂ��폜���� */
	public void remove(int index) {
		this.dataList.remove(index);
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int w = getWidth();
		int h = getHeight();
		
		this.visibleRows = (h - 2) / 16;
		
		// �O�g
		if (getFocused() == true && getEnabled() == true) {
			g.setColor(0,128,255);
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
		int I = this.dataList.size();
		for (int i = 0; i < visibleRows; i++) {
			if ((this.offsetIndex + i) < I) {
				if (selectedIndex == i && getEnabled() == true) {
					g.setColor(0, 128, 255);
					g.fillRect(3, (16 * i) + 3, w - 6, 16);
					g.setColor(getBackground());
					g.drawString((String)this.dataList.get(this.offsetIndex + i), 4, (16 * i) + 6);
				} else {
					g.setColor(getForeground());
					g.drawString((String)this.dataList.get(this.offsetIndex + i), 4, (16 * i) + 6);
				}
			}
		}
	}
	
	/** �C�x���g�n���h�� */
	public void processEvent(AWTEvent event) {
		// �񊈐��̎��̓C�x���g���󂯕t���Ȃ�
		if (getEnabled() == false) return;

		// �L�[����
		if (event.getType() == KeyEvent.KEY_PRESSED) {
			int keycode = ((KeyEvent)event).getKeycode();
			if (keycode == KeyEvent.VKEY_UP) {
				if (this.selectedIndex > 0) {
					this.selectedIndex--;
					repaint();
					if (getParent() != null) {
						getParent().processEvent(this.itemEvent);
					}
				}
			} else if (keycode == KeyEvent.VKEY_DOWN) {
				if (this.selectedIndex < this.dataList.size() - 1 && 
					this.selectedIndex < ((getHeight() - 22) / 16))
				{
					this.selectedIndex++;
					repaint();
					if (getParent() != null) {
						getParent().processEvent(this.itemEvent);
					}
				}
			} else if (keycode == KeyEvent.VKEY_ENTER) {
				getParent().processEvent(this.itemEvent);
			}
		// �}�E�X����
		} else if (event.getType() == MouseEvent.MOUSE_PRESSED) {
			int my = ((MouseEvent)event).getY();
			//printf("y = %d,", my);
			select((my - 3) / 16);
			if (getParent() != null) {
				getParent().processEvent(this.itemEvent);
			}
		// �t�H�[�J�X��ԕύX
		} else if (event.getType() == FocusEvent.FOCUS_IN || event.getType() == FocusEvent.FOCUS_OUT) {
			repaint();
			if (getParent() != null) {
				getParent().processEvent(this.itemEvent);
			}
		}
	}
}

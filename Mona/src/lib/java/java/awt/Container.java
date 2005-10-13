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
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

/**
 �R���e�i�[�N���X
*/
public class Container extends Component {
	/** ���i�ꗗ */
	private Vector componentList;

	/** �R���X�g���N�^ */
	public Container() {
		this.componentList = new Vector();
	}
	
	/**
	 �������i�𓾂�
	 @return �������i�i�Ȃ����null�j
	*/
	public Component getComponent() {
		// null�`�F�b�N
		int I = this.componentList.size();
		if (I == 0) return null;

		// ��납��`�F�b�N���Ă���
		for (int i = I - 1; i >= 0; i--) {
			Component c = (Component)this.componentList.get(i);
			if (c.getFocused() == true) return c;
		}
		return null;
	}
	
	/**
	 ���i�𓾂�
	 @param x �w�肷��X���W
	 @param y �w�肷��Y���W
	 */
	public Component getComponentAt(int x, int y) {
		// null�`�F�b�N
		int I = this.componentList.size();
		if (I == 0) return null;
		
		// ��납��`�F�b�N���Ă���
		for (int i = I - 1; i >= 0; i--) {
			Component c = (Component)this.componentList.get(i);
			Rectangle bounds = c.getBounds();
			// �}�E�X�J�[�\��������͈͂ɕ��i�����邩�ǂ����`�F�b�N
			if (bounds.x <= x && x <= bounds.x + bounds.width && 
				bounds.y <= y && y <= bounds.y + bounds.height)
			{
				return c;
			}
		}
		return null;
	}
	
	/**
	 �w�肵�����i��ǉ�����
	 @param component �w�肷�镔�i
	 */
	public void add(Component component) {
		component.setParent(this);
		component.addNotify();
		this.componentList.add(component);
	}
	
	/**
	 �w�肵�����i���폜����
	 @param component �w�肷�镔�i
	 @return �폜���ꂽ���i�i�Ȃ����null�j
	 */
	public void remove(Component component) {
		this.componentList.remove(component);
	}
	
	/** �C�x���g���� */
	public void dispatchEvent(AWTEvent event) {
		// �񊈐��̎��̓C�x���g���󂯕t���Ȃ�
		if (getEnabled() == false) return;

		// �������i�ɃL�[�C�x���g�𓊂���
		if (event.getType() == KeyEvent.KEY_PRESSED || event.getType() == KeyEvent.KEY_RELEASED) {
			Component component = getComponent();
			// ���i�ŃC�x���g���N������
			if (component != null) {
				event.setSource(component);
				component.processEvent(event);
			}
			// ���i�ȊO�ŃC�x���g���N������
			processEvent(event);
		// �}�E�X�N���b�N
		} else if (event.getType() == MouseEvent.MOUSE_PRESSED) {
			MouseEvent me = (MouseEvent)event;
			// �}�E�X�C�x���g���N���������i��T��
			Component component = getComponentAt(me.getX(), me.getY());
			// ���i�ŃC�x���g���N������
			if (component != null) {
				// �C�x���g���N���������i�ȊO���t�H�[�J�X�A�E�g��Ԃɂ���
				int I = this.componentList.size();
				for (int i = 0; i < I; i++) {
					Component c = (Component)this.componentList.get(i);
					if (c != component) {
						c.setFocused(false);
					}
				}
				component.setFocused(true);
				event.setSource(component);
				Rectangle bounds = component.getBounds();
				me.setX(me.getX() - bounds.x);
				me.setY(me.getY() - bounds.y);
				//syscall_print("MOUSE_PRESSED,");
				component.processEvent(event);
			// ���i�ȊO�ŃC�x���g���N������
			} else {
				// ���i���t�H�[�J�X�A�E�g��Ԃɂ���
				int I = this.componentList.size();
				for (int i = 0; i < I; i++) {
					Component c = (Component)this.componentList.get(i);
					c.setFocused(false);
				}
				processEvent(event);
			}
		// �}�E�X�N���b�N�ȊO�̃}�E�X�C�x���g
		} else if (event.getType() == MouseEvent.MOUSE_RELEASED || 
					event.getType() == MouseEvent.MOUSE_DRAGGED || 
					event.getType() == MouseEvent.MOUSE_MOVED)
		{
			MouseEvent me = (MouseEvent)event;
			// �}�E�X�C�x���g���N���������i��T��
			Component component = getComponentAt(me.getX(), me.getY());
			// ���i�ŃC�x���g���N������
			if (component != null) {
				event.setSource(component);
				Rectangle bounds = component.getBounds();
				me.setX(me.getX() - bounds.x);
				me.setY(me.getY() - bounds.y);
				component.processEvent(event);
			// ���i�ȊO�ŃC�x���g���N������
			} else {
				processEvent(event);
			}
		} else {
			processEvent(event);
		}
	}
	
	/** �ĕ`�� */
	public void repaint() {
		if (getBuffer() == null) return;
		
		paint(getGraphics());

		// �����̗̈���X�V����
		update();

		// �q���i���ĕ`�悷��
		int I = this.componentList.size();
		for(int i = 0; i < I; i++) {
			Component component = (Component)this.componentList.get(i);
			component.repaint();
		}
	}
}

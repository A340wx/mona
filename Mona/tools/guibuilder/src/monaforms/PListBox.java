package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 ���X�g���i
 */
public class PListBox extends PBase {
	/** ���i�ʂ��ԍ� */
	private static int count = 0;
	
	/** �R���X�g���N�^ */
	public PListBox() {
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int w = getWidth();
		int h = getHeight();
		
		// ��x�w�i�F�ŃN���A
		g.setColor(COLOR_WHITE);
		g.fillRect(0, 0, w, h);
		
		// �g��`��
		if (isEnabled() == true) {
			g.setColor(new Color(0xff0080ff, true));
		} else {
			g.setColor(getBackground());
		}
		g.drawRect(0, 0, w - 1, h - 1);
		g.setColor(COLOR_BLACK);
		g.drawRect(1, 1, w - 3, h - 3);
		
		// �I��g
		if (isEnabled() == true) {
			g.setColor(new Color(0xff0080ff, true));
			g.fillRect(3, 3, w - 6, 12);
		}
		
		// ����
		FontMetrics metrics = getFontMetrics(getFont());
		int fw = metrics.stringWidth(getCaption());
		int fh = metrics.getAscent() - metrics.getDescent();
		if (isEnabled() == true) {
			g.setColor(COLOR_WHITE);
		} else {
			g.setColor(COLOR_BLACK);
		}
		g.drawString(getCaption(), 3, 3 + fh);
	}
	
	//
	// IParts
	//
	
	/** ���i�������ɌĂ΂�� */
	public void create() {
		setBounds(INSETS_LEFT, INSETS_TOP, 100, 100);
		setForeground(DEFAULT_FORECOLOR);
		setBackground(DEFAULT_BACKCOLOR);
		enableEvents(AWTEvent.MOUSE_EVENT_MASK);
		setName("list" + (count + 1));
		setCaption("list" + (count + 1));
		setFontStyle("FONT_PLAIN");
		count++;
	}
	
	/** ���i�폜���ɌĂ΂�� */
	public void dispose() {
		this.count = 0;
	}
	
	/** �N���X���𓾂� */
	public String getClassName() {
		return "ListBox";
	}
	
	/** �}�E�X�C�x���g */
	public void processMouseEvent(MouseEvent e) {
		if (e.getID() == MouseEvent.MOUSE_PRESSED) {
			System.out.println("PListBox: source = " + e.getSource());
			((ApplicationWindow)getParent().getParent()).update(this);
		}
		super.processMouseEvent(e);
	}
}

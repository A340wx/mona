package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 ���x�����i
 */
public class PLabel extends PBase {
	/** ���i�ʂ��ԍ� */
	private static int count = 0;
	
	/** �R���X�g���N�^ */
	public PLabel() {
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int w = getWidth();
		int h = getHeight();
		
		// ��x�w�i�F�ŃN���A
		g.setColor(getBackground());
		g.fillRect(0, 0, w, h);
		
		// ����
		FontMetrics metrics = getFontMetrics(getFont());
		int fw = metrics.stringWidth(getCaption());
		int fh = metrics.getAscent() - metrics.getDescent();
		if (isEnabled() == true) {
			g.setColor(getForeground());
		} else {
			g.setColor(COLOR_GRAY);
		}
		g.drawString(getCaption(), (w - fw) / 2, (h + fh) / 2);
	}
	
	//
	// IParts
	//
	
	/** ���i�������ɌĂ΂�� */
	public void create() {
		setBounds(INSETS_LEFT, INSETS_TOP, 80, 20);
		setForeground(DEFAULT_FORECOLOR);
		setBackground(DEFAULT_BACKCOLOR);
		enableEvents(AWTEvent.MOUSE_EVENT_MASK);
		setName("label" + (count + 1));
		setCaption("label" + (count + 1));
		setFontStyle("FONT_PLAIN");
		count++;
	}
	
	/** ���i�폜���ɌĂ΂�� */
	public void dispose() {
		this.count = 0;
	}
	
	/** �N���X���𓾂� */
	public String getClassName() {
		return "Label";
	}
	
	/** �R���X�g���N�^�ɓn�������𓾂� */
	public String getArgs() {
		return "\"" + getCaption() + "\"";
	}
	
	/** �}�E�X�C�x���g */
	public void processMouseEvent(MouseEvent e) {
		if (e.getID() == MouseEvent.MOUSE_PRESSED) {
			System.out.println("PLabel: source = " + e.getSource());
			((ApplicationWindow)getParent().getParent()).update(this);
		}
		super.processMouseEvent(e);
	}
}

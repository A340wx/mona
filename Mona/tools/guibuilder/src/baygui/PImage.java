package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 �摜���i
 */
public class PImage extends PBase {
	/** ���i�ʂ��ԍ� */
	private static int count = 0;
	
	/** �R���X�g���N�^ */
	public PImage() {
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int w = getWidth();
		int h = getHeight();
		
		// ��x�w�i�F�ŃN���A
		g.setColor(COLOR_WHITE);
		g.fillRect(0, 0, w, h);
		
		// �g��`��
		g.setColor(COLOR_BLACK);
		g.drawRect(0, 0, w - 1, h - 1);
		
		// ����
		FontMetrics metrics = getFontMetrics(getFont());
		int fw = metrics.stringWidth(getCaption());
		int fh = - metrics.getAscent() + metrics.getDescent();
		if (isEnabled() == true) {
			g.setColor(getForeground());
		} else {
			g.setColor(COLOR_GRAY);
		}
		g.drawString(getCaption(), (w - fw) / 2, (h - fh) / 2);
	}
	
	//
	// IParts
	//
	
	/** ���i�쐬���ɌĂ΂�� */
	public void create() {
		setBounds(INSETS_LEFT, INSETS_TOP, 80, 80);
		setForeground(DEFAULT_FORECOLOR);
		setBackground(DEFAULT_BACKCOLOR);
		enableEvents(AWTEvent.MOUSE_EVENT_MASK);
		setName("image" + (count + 1));
		setCaption("image" + (count + 1));
		setFontStyle("FONT_PLAIN");
		count++;
	}
	
	/** ���i�폜���ɌĂ΂�� */
	public void dispose() {
		this.count = 0;
	}
	
	/** �N���X���𓾂� */
	public String getClassName() {
		return "Image";
	}
	
	/** �w�肵���C�x���g���T�|�[�g����Ă��邩�ǂ����𓾂� */
	public boolean getSupported(int eventType) {
		return false;
	}
	
	/** �R���X�g���N�^�ɓn�������𓾂� */
	public String getArgs() {
		return "\"" + getCaption() + "\"";
	}
	
	/** �}�E�X�C�x���g */
	public void processMouseEvent(MouseEvent e) {
		if (e.getID() == MouseEvent.MOUSE_PRESSED) {
			System.out.println("PImage: source = " + e.getSource());
			((ApplicationWindow)getParent().getParent()).update(this);
		}
		super.processMouseEvent(e);
	}
}

package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 �x�[�X���i�B
 ���i���Ƃɋ��ʉ��ł�����̂͑S�ċ��ʉ����ăR�[�h�ʂ��팸����B
 */
public class PBase extends Container implements IParts {
	/** �L���v�V���� */
	private String caption   = "";
	/** �t�H���g�X�^�C�� */
	private String fontStyle = "";
	/** �e�C�x���g�̃t���O */
	private boolean[] eventList = null;
	
	/** �R���X�g���N�^ */
	public PBase() {
		eventList = new boolean[eventName.length];
		setLayout(null);
	}
	
	/** ���i�������ɌĂ΂�� */
	public void create() {
	}
	
	/** ���i�폜���ɌĂ΂�� */
	public void dispose() {
	}
	
	/** �N���X���𓾂� */
	public String getClassName() {
		return "";
	}
	
	/** �L���v�V�����𓾂� */
	public String getCaption() {
		return caption;
	}
	
	/** �L���v�V������ݒ肷�� */
	public void setCaption(String caption) {
		this.caption = caption;
	}
	
	/** �t�H���g�X�^�C���𓾂� */
	public String getFontStyle() {
		return fontStyle;
	}
	
	/** �t�H���g�X�^�C����ݒ肷�� */
	public void setFontStyle(String fontStyle) {
		this.fontStyle = fontStyle;
	}
	
	/** �w�i�F�i0xffffff�j�𓾂� */
	public String getBackcolor() {
		Color  c = getBackground();
		String s = Integer.toHexString
			((c.getRed() << 16 | c.getGreen() << 8 | c.getBlue()) | 0xff000000);
		return s;
	}
	
	/** �w�i�F��ݒ肷�� */
	public void setBackcolor(String color) {
		// Java�ɂ�unsigned���Ȃ�����int���Ɩ�肪����
		setBackground(new Color((int)(Long.parseLong(color, 16)) | 0xff000000, true));
	}
	
	/** �O�i�F�i0xffffffff�j�𓾂� */
	public String getForecolor() {
		Color  c = getForeground();
		String s = Integer.toHexString
			((c.getRed() << 16 | c.getGreen() << 8 | c.getBlue()) | 0xff000000);
		return s;
	}
	
	/** �O�i�F��ݒ肷�� */
	public void setForecolor(String color) {
		// Java�ɂ�unsigned���Ȃ�����int���Ɩ�肪����
		setForeground(new Color((int)(Long.parseLong(color, 16)) | 0xff000000, true));
	}
	
	/** �w�肵���C�x���g���T�|�[�g����Ă��邩�ǂ����𓾂� */
	public boolean getSupported(int eventType) {
		return true;
	}
	
	/** �w�肵���C�x���g�̃t���O�𓾂� */
	public boolean getEvent(int eventType) {
		return eventList[eventType];
	}
	
	/** �w�肵���C�x���g�̃t���O��ݒ肷�� */
	public void setEvent(int eventType, boolean flag) {
		eventList[eventType] = flag;
	}
	
	/** �R���X�g���N�^�ɓn���l�𓾂�i�f�t�H���g�͋󕶎��j*/
	public String getArgs() {
		return "";
	}
	
	/** �}�E�X�C�x���g */
	public void processMouseEvent(MouseEvent e) {
	}
}

package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 �A�v���P�[�V�����v���p�e�B�o�[�B
 �����ł̑���͍����̕��i�ɔ��f�����B
 */
public class ApplicationPropertybar extends Panel implements ItemListener, ActionListener {
	/** ����Ώ� */
	private IParts target;
	/** ���x�����X�g */
	private Label[] lList;
	/** �e�L�X�g���X�g */
	private TextField[] tList;
	/** �`�F�b�N�{�b�N�X���X�g */
	private Checkbox[] cList;
	
	/** �R���X�g���N�^ */
	public ApplicationPropertybar() {
	}
	
	/** ���i�������ɌĂ΂�� */
	public void create() {
		setBounds(getParent().getWidth() - getParent().getInsets().right - 167, 
			getParent().getInsets().top + 31, 165, 410);
		setForeground(IParts.COLOR_BLACK);
		setBackground(IParts.WINDOWS_LIGHTGRAY);
		setLayout(null);
		
		lList = new Label[10];
		tList = new TextField[10];
		cList = new Checkbox[10];
		
		lList[0] = new Label("���i��");
		lList[1] = new Label("�L���v�V����");
		lList[2] = new Label("����");
		lList[3] = new Label("�w");
		lList[4] = new Label("�x");
		lList[5] = new Label("��");
		lList[6] = new Label("����");
		lList[7] = new Label("�t�H���g");
		lList[8] = new Label("�w�i�F");
		lList[9] = new Label("�O�i�F");
		
		for (int i = 0; i < tList.length; i++) {
			tList[i] = new TextField();
		}
		
		for (int i = 0; i < cList.length; i++) {
			cList[i] = new Checkbox(IParts.eventLabel[i]);
		}
		
		lList[0].setBounds(5,  4,75,20);
		lList[1].setBounds(5, 24,75,20);
		lList[2].setBounds(5, 44,75,20);
		lList[3].setBounds(5, 64,75,20);
		lList[4].setBounds(5, 84,75,20);
		lList[5].setBounds(5,104,75,20);
		lList[6].setBounds(5,124,75,20);
		lList[7].setBounds(5,144,75,20);
		lList[8].setBounds(5,164,75,20);
		lList[9].setBounds(5,184,75,20);
		
		tList[0].setBounds(81,  4,80,20);
		tList[1].setBounds(81, 24,80,20);
		tList[2].setBounds(81, 44,80,20);
		tList[3].setBounds(81, 64,80,20);
		tList[4].setBounds(81, 84,80,20);
		tList[5].setBounds(81,104,80,20);
		tList[6].setBounds(81,124,80,20);
		tList[7].setBounds(81,144,80,20);
		tList[8].setBounds(81,164,80,20);
		tList[9].setBounds(81,184,80,20);
		
		cList[0].setBounds(5,204,140,20);
		cList[1].setBounds(5,224,140,20);
		cList[2].setBounds(5,244,140,20);
		cList[3].setBounds(5,264,140,20);
		cList[4].setBounds(5,284,140,20);
		cList[5].setBounds(5,304,140,20);
		cList[6].setBounds(5,324,140,20);
		cList[7].setBounds(5,344,140,20);
		cList[8].setBounds(5,364,140,20);
		cList[9].setBounds(5,384,140,20);
		
		for (int i = 0; i < lList.length; i++) {
			add(lList[i]);
		}
		for (int i = 0; i < tList.length; i++) {
			add(tList[i]);
			tList[i].addActionListener(this);
		}
		for (int i = 0; i < cList.length; i++) {
			add(cList[i]);
			cList[i].addItemListener(this);
		}
	}

	/**
	 �I�����ꂽ���i�̃v���p�e�B�𓾂ăt�B�[���h���X�V����B
	 */
	public void update(IParts parts) {
		this.target = parts;
		tList[0].setText(parts.getName());
		tList[1].setText(parts.getCaption());
		tList[2].setText("" + parts.isEnabled());
		if (parts instanceof PWindow) {
			tList[3].setText("" + parts.getX());
			tList[4].setText("" + parts.getY());
		} else {
			// ��ʕ��i�ł̓t���[���̘g�����l������
			tList[3].setText("" + (parts.getX() - IParts.INSETS_LEFT));
			tList[4].setText("" + (parts.getY() - IParts.INSETS_TOP));
		}
		tList[5].setText("" + parts.getWidth());
		tList[6].setText("" + parts.getHeight());
		tList[7].setText(parts.getFontStyle());
		tList[8].setText(parts.getBackcolor());
		tList[9].setText(parts.getForecolor());
		
		for (int i = 0; i < cList.length; i++) {
			cList[i].setEnabled(parts.getSupported(i));
			cList[i].setState(parts.getEvent(i));
		}
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		int i, j;
		int w = getWidth();
		int h = getHeight();
		
		// �O�g
		//g.setColor(IParts.WINDOWS_LIGHTGRAY);
		//g.fillRect(0, 0, w, h);
		g.setColor(IParts.COLOR_BLACK);
		g.drawRect(0, 0, w - 1, h - 1);
		
		// �g
		g.setColor(IParts.COLOR_WHITE);
		g.drawLine(1, 1, w - 2, 1);
		g.drawLine(1, 1, 1, h - 2);
		g.setColor(IParts.COLOR_GRAY);
		g.drawLine(w - 2, 2, w - 2, h - 2);
		g.drawLine(2, h - 2, w - 2, h - 2);
		
		paintComponents(g);
	}

	//
	// ItemListener
	// 
	public void itemStateChanged(ItemEvent e) {
		if (target == null) return;
		
		for (int i = 0; i < cList.length; i++) {
			if (e.getSource() == cList[i]) {
				System.out.println("setEvent(" + IParts.eventName[i] + ", " + cList[i].getState() + ")");
				target.setEvent(i, cList[i].getState());
			}
		}
	}

	//
	// ActionListener
	//
	public void actionPerformed(ActionEvent e) {
		if (target == null) return;
		
		if (e.getSource() == tList[0]) {
			System.out.println("setName(" + tList[0].getText() + ")");
			target.setName(tList[0].getText());
		} else if (e.getSource() == tList[1]) {
			System.out.println("setCaption(" + tList[1].getText() + ")");
			target.setCaption(tList[1].getText());
		} else if (e.getSource() == tList[2]) {
			System.out.println("setEnabled(" + tList[2].getText() + ")");
			target.setEnabled(tList[2].getText().equals("true"));
		} else if (e.getSource() == tList[3] || e.getSource() == tList[4]) {
			int x0 = Integer.parseInt(tList[3].getText());
			int y0 = Integer.parseInt(tList[4].getText());
			if (target instanceof PWindow) {
				System.out.println("setLocation(" + x0 + "," + y0 + ")");
				target.setLocation(x0, y0);
			// ��ʕ��i�ł̓t���[���̘g�����l������
			} else {
				System.out.println("setLocation(" + (x0 + IParts.INSETS_LEFT) + "," 
					+ (y0 + IParts.INSETS_TOP) + ")");
				target.setLocation(x0 + IParts.INSETS_LEFT, y0 + IParts.INSETS_TOP);
			}
		} else if (e.getSource() == tList[5] || e.getSource() == tList[6]) {
			int w0 = Integer.parseInt(tList[5].getText());
			int h0 = Integer.parseInt(tList[6].getText());
			System.out.println("setSize(" + w0 + "," + h0 + ")");
			target.setSize(w0, h0);
		} else if (e.getSource() == tList[7]) {
			System.out.println("setFontStyle(" + tList[7].getText() + ")");
			target.setFontStyle(tList[7].getText());
		} else if (e.getSource() == tList[8]) {
			System.out.println("setBackcolor(" + tList[8].getText() + ")");
			target.setBackcolor(tList[8].getText());
		} else if (e.getSource() == tList[9]) {
			System.out.println("setForecolor(" + tList[9].getText() + ")");
			target.setForecolor(tList[9].getText());
		}
		target.repaint();
	}
}

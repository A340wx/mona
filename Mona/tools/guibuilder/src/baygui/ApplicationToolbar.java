package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 �A�v���P�[�V�����c�[���o�[�B
 �{�^�����������ƃE�B���h�E�ɕ��i���ǉ������B
 */
public class ApplicationToolbar extends Panel implements ActionListener {
	/** Button */
	private ImageButton b1 = null;
	/** Image */
	private ImageButton b2 = null;
	/** Label */
	private ImageButton b3 = null;
	/** ListBox */
	private ImageButton b4 = null;
	/** TextField */
	private ImageButton b5 = null;
	
	/** �R���X�g���N�^ */
	public ApplicationToolbar() {
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		// ���̓I�Ɍ����邽�߂̐�
		g.setColor(IParts.COLOR_GRAY);
		g.drawLine(0, 0, getWidth() - 1, 0);
		g.setColor(IParts.COLOR_WHITE);
		g.drawLine(0, 1, getWidth() - 1, 1);
		g.setColor(IParts.COLOR_BLACK);
		g.drawLine(0, getHeight() - 1, getWidth() - 1, getHeight() - 1);
		
		paintComponents(g);
	}
	
	/** ���i�������ɌĂ΂�� */
	public void create() {
		setBounds(getParent().getInsets().left, getParent().getInsets().top, 
			640 - getParent().getInsets().right - getParent().getInsets().left, 29);
		setForeground(IParts.COLOR_BLACK);
		setBackground(IParts.WINDOWS_LIGHTGRAY);
		setLayout(null);
		
		b1 = new ImageButton("button");
		b2 = new ImageButton("image");
		b3 = new ImageButton("label");
		b4 = new ImageButton("listbox");
		b5 = new ImageButton("textfield");
		
		b1.setBounds(  1, 2, 26, 26);
		b2.setBounds( 27, 2, 26, 26);
		b3.setBounds( 53, 2, 26, 26);
		b4.setBounds( 79, 2, 26, 26);
		b5.setBounds(105, 2, 26, 26);
		
		b1.addActionListener(this);
		b2.addActionListener(this);
		b3.addActionListener(this);
		b4.addActionListener(this);
		b5.addActionListener(this);
		
		add(b1);
		add(b2);
		add(b3);
		add(b4);
		add(b5);
	}

	//
	// ActionListener
	//
	public void actionPerformed(ActionEvent e) {
		// �A�v���P�[�V�����E�B���h�E�𓾂�
		PWindow pWindow = ((ApplicationWindow)getParent()).getPWindow();
		if (pWindow == null) return;
		if (e.getSource() == b1) {
			// �{�^�����i
			PButton p = new PButton();
			pWindow.add(p, 0);
			p.create();
		} else if (e.getSource() == b2) {
			// �C���[�W���i
			PImage p = new PImage();
			pWindow.add(p, 0);
			p.create();
		} else if (e.getSource() == b3) {
			// ���x�����i
			PLabel p = new PLabel();
			pWindow.add(p, 0);
			p.create();
		} else if (e.getSource() == b4) {
			// ���X�g���i
			PListBox p = new PListBox();
			pWindow.add(p, 0);
			p.create();
		} else if (e.getSource() == b5) {
			// �e�L�X�g���i
			PTextField p = new PTextField();
			pWindow.add(p, 0);
			p.create();
		}
	}
}

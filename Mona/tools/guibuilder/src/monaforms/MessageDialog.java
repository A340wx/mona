package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 ���b�Z�[�W�_�C�A���O�B
 �Q�s�܂ł̃��b�Z�[�W��\���\�B
 */
public class MessageDialog extends Dialog implements WindowListener, ActionListener, KeyListener {
	/** 1�s�ڂ̃��x�� */
	Label  label1 = new Label("", Label.CENTER);
	/** 2�s�ڂ̃��x�� */
	Label  label2 = new Label("", Label.CENTER);
	/** OK�{�^�� */
	Button submit = new Button("OK");
	/** �{�^�����ڂ���p�l�� */
	Panel  bpanel = new Panel();

	/**
	 �R���X�g���N�^
	 @param parent  �e�t���[��
	 @param title   �^�C�g��
	 @param message ���b�Z�[�W�i2�s�܂Łj
	*/
	public MessageDialog(Frame parent, String title, String[] message) {
		super(parent, title);
		setResizable(false);
		bpanel.add(submit);
		
		// 1�s���b�Z�[�W
		if (message.length == 1) {
			setSize(200,80);
			setLocation(parent.getX() + 220, parent.getY() + 200);
			label1.setText(message[0]);
			add(label1, BorderLayout.CENTER);
		
		// 2�s���b�Z�[�W
		} else {
			setSize(200,100);
			setLocation(parent.getX() + 220, parent.getY() + 190);
			label1.setText(message[0]);
			label2.setText(message[1]);
			add(label1, BorderLayout.NORTH);
			add(label2, BorderLayout.CENTER);
		}
		
		add(bpanel, BorderLayout.SOUTH);
		
		// �C�x���g�ݒ�
		addWindowListener(this);
		addKeyListener(this);
		submit.addActionListener(this);
		submit.addKeyListener(this);
	}

	//
	// WindowListener
	//
	public void windowActivated(WindowEvent e) {}
	public void windowClosed(WindowEvent e) {}
	public void windowClosing(WindowEvent e) { dispose(); }
	public void windowDeactivated(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowOpened(WindowEvent e) {}

	//
	// ActionListener
	//
	public void actionPerformed(ActionEvent e) { dispose(); /* �{�^���������ƕ��� */ }

	//
	// KeyListener
	//
	public void keyPressed(KeyEvent e) {}
	public void keyReleased(KeyEvent e) {}
	public void keyTyped(KeyEvent e) { dispose(); /* �����L�[�������ƕ��� */ }
}

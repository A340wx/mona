package guibuilder;

import java.awt.*;
import java.awt.event.*;

/**
 �A�v���P�[�V�����E�B���h�E�B
 ���j���[��c�[���o�[�Ȃǂ������Ă���B
 */
public class ApplicationWindow extends Frame implements WindowListener, ActionListener {
	/** ����Ώ� */
	private IParts target = null;
	/** �E�B���h�E���i */
	private PWindow pWindow = null;
	/** �c�[���o�[ */
	private ApplicationToolbar applitacionToolbar = null;
	/** �v���p�e�B�o�[ */
	private ApplicationPropertybar applitacionPropertybar = null;
	/** �t�@�C���ۑ��N���X */
	private FileMaker fileMaker = null;
	
	/** �R���X�g���N�^ */
	public ApplicationWindow() {
		super(IParts.title);
		setSize(640, 480);
		setResizable(false);
		setVisible(true);
		// ����GIF���A�v���P�[�V�����A�C�R���ɐݒ肵�Ă���
		setIconImage(Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("/resources/mona.gif")));
	}
	
	/** ���i�������ɌĂ΂�� */
	public void create() {
		addWindowListener(this);
		setLayout(null);
		
		// ���j���[�̒�`
		MenuBar menuBar = new MenuBar();
		Menu fileMenu = new Menu("�t�@�C��");
		Menu editMenu = new Menu("�ҏW");
		Menu helpMenu = new Menu("�w���v");
		fileMenu.add(new MenuItem("�V�K", new MenuShortcut(KeyEvent.VK_N, false)));
		fileMenu.add(new MenuItem("�ۑ�", new MenuShortcut(KeyEvent.VK_S, false)));
		fileMenu.add(new MenuItem("�I��", new MenuShortcut(KeyEvent.VK_Q, false)));
		editMenu.add(new MenuItem("�폜", new MenuShortcut(KeyEvent.VK_D, false)));
		helpMenu.add(new MenuItem("�o�[�W����", new MenuShortcut(KeyEvent.VK_V, false)));
		fileMenu.addActionListener(this);
		editMenu.addActionListener(this);
		helpMenu.addActionListener(this);
		menuBar.add(fileMenu);
		menuBar.add(editMenu);
		menuBar.add(helpMenu);
		setMenuBar(menuBar);
		
		// �c�[���o�[
		applitacionToolbar = new ApplicationToolbar();
		add(applitacionToolbar);
		applitacionToolbar.create();
		applitacionToolbar.repaint();
		
		// �v���p�e�B�o�[
		applitacionPropertybar = new ApplicationPropertybar();
		add(applitacionPropertybar);
		applitacionPropertybar.create();
		applitacionPropertybar.repaint();
		
		// �t�@�C���ۑ��N���X
		fileMaker = new FileMaker();
	}

	/** �E�B���h�E���i�𓾂� */
	public PWindow getPWindow() {
		return pWindow;
	}
	
	/** �c�[���o�[�𓾂� */
	public ApplicationToolbar getApplicationToolbar() {
		return applitacionToolbar;
	}
	
	/** �v���p�e�B�o�[�𓾂� */
	public ApplicationPropertybar getApplicationPropertybar() {
		return applitacionPropertybar;
	}
	
	/** ���i�X�V */
	public void update(IParts parts) {
		this.target = parts;
		applitacionPropertybar.update(parts);
	}

	//
	// WindowListener
	//
	public void windowActivated(WindowEvent e) {}
	public void windowClosed(WindowEvent e) {}
	public void windowClosing(WindowEvent e) { System.exit(0); }
	public void windowDeactivated(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowOpened(WindowEvent e) {}

	//
	// ActionListener
	//
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("�V�K")) {
			if (pWindow == null) {
				pWindow = new PWindow();
				add(pWindow);
				pWindow.create();
				pWindow.repaint();
			} else {
				MessageDialog dialog = new MessageDialog(this, "�G���[", 
					new String[] {"���łɃE�B���h�E��", "�쐬����Ă��܂��B"});
				dialog.show();
			}
		} else if (e.getActionCommand().equals("�ۑ�") && pWindow != null) {
			if (pWindow != null) {
				fileMaker.writeFile(pWindow);
				MessageDialog dialog = new MessageDialog(this, "�ۑ�", 
					new String[] {"�ۑ����܂����B"});
				dialog.show();
			}
		} else if (e.getActionCommand().equals("�I��")) {
			System.exit(0);
		} else if (e.getActionCommand().equals("�폜")) {
			if (pWindow != null && target != null) {
				// �E�B���h�E���폜����
				if (target == pWindow) {
					System.out.println("remove(" + target.getName() + ")");
					Component[] list = pWindow.getComponents();
					for (int i = 0; i < pWindow.getComponentCount(); i++) {
						IParts p = (IParts)list[i];
						p.dispose();
					}
					pWindow.dispose();
					remove(pWindow);
					pWindow = null;
				// ���i���폜����
				} else {
					System.out.println("remove(" + target.getName() + ")");
					target.dispose();
					pWindow.remove((Component)target);
				}
				target = null;
				repaint();
			}
		} else if (e.getActionCommand().equals("�o�[�W����")) {
			MessageDialog dialog = new MessageDialog(this, "�o�[�W����", 
				new String[] {IParts.title, "Copyright (C) 2005, bayside."});
			dialog.show();
		}
	}
}

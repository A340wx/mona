package guibuilder;

import java.awt.*;

/**
 �摜���{�^���B
 �{�^�����p�����Ă���̂ŉ����ƈ������ށB
 */
public class ImageButton extends Button {
	/** �摜 */
	private Image image = null;
	
	/**
	 �R���X�g���N�^�B
	 @param name '/resources/' + 'name' + '.gif' �Ƃ������O�̃t�@�C�����J�����B
	 */
	public ImageButton(String name) {
		setName(name);
		image = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("/resources/" + name + ".gif"));
	}
	
	/** �`��n���h�� */
	public void paint(Graphics g) {
		g.drawImage(image, 2, 2, this);
	}
}

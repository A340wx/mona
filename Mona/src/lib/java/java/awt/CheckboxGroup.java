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

/**
 �`�F�b�N�{�b�N�X�O���[�v�N���X
*/
public class CheckboxGroup {
	private Vector checkboxList;
	
	/** �R���X�g���N�^ */
	public CheckboxGroup() {
		this.checkboxList = new Vector();
	}
	
	/** �`�F�b�N�{�b�N�X��ǉ����� */
	public void add(Checkbox check) {
		// null�`�F�b�N
		if (check == null) return;
		check.setCheckboxGroup(this);
		this.checkboxList.add(check);
	}
	
	/** �I�����ꂽ�`�F�b�N�{�b�N�X�𓾂� */
	public Checkbox getSelectedCheckbox() {
		int I = this.checkboxList.size();
		for (int i = 0; i < I; i++) {
			Checkbox check = (Checkbox)(this.checkboxList.get(i));
			if (check.getChecked() == true) return check;
		}
		return null;
	}
	
	/** �C�x���g�n���h�� */
	public void processEvent(AWTEvent event) {
		// �I������Ă���`�F�b�N�{�b�N�X�ȊO�𖢑I���ɂ���
		int I = this.checkboxList.size();
		for (int i = 0; i < I; i++) {
			Checkbox check = (Checkbox)(this.checkboxList.get(i));
			if (event.getSource() != check) {
				check.setChecked(false);
			}
		}
	}
}

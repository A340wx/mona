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

#if !defined(_CHECKBOX_H_INCLUDED_)
#define _CHECKBOX_H_INCLUDED_

namespace monagui {
	class CheckboxGroup;

	/**
	 �`�F�b�N�{�b�N�X�N���X
	*/
	class Checkbox : public Component {
	private:
		/** �`�F�b�N���ꂽ���ǂ��� */
		bool checked;
		/** �{�^���̃��x�� */
		String label;
		/** �I���C�x���g */
		Event itemEvent;
		/** �`�F�b�N�{�b�N�X�O���[�v */
		CheckboxGroup* group;

	public:
		/** �f�t�H���g�R���X�g���N�^ */
		Checkbox();
		
		/**
		 �R���X�g���N�^
		 @param label ���x��
		 */
		Checkbox(const String& label);
		
		/** �f�X�g���N�^ */
		virtual ~Checkbox();
		
		/**
		 �`�F�b�N���ꂽ���ǂ�����ݒ肷��
		 @param checked �t���O (true / false)
		 */
		virtual void setChecked(bool checked);
		
		/** �`�F�b�N�{�b�N�X�O���[�v��ݒ肷�� */
		inline void setCheckboxGroup(CheckboxGroup* group) { this->group = group; }
		
		/**
		 ���x����ݒ肷��
		 @param label ���x��
		 */
		virtual void setLabel(const String& label);
		
		/** �`�F�b�N���ꂽ���ǂ����𓾂� */
		inline bool getChecked() { return this->checked; }
		
		/** �`�F�b�N�{�b�N�X�O���[�v�𓾂� */
		inline CheckboxGroup* getCheckboxGroup() { return this->group; }
		
		/** ���x���𓾂� */
		inline const char* getLabel() { return this->label.getBytes(); }
		
		/** �`��n���h�� */
		virtual void paint(Graphics* g);
		
		/** �C�x���g�n���h�� */
		virtual void processEvent(Event* event);
	};
}

#endif // _CHECKBOX_H_INCLUDED_

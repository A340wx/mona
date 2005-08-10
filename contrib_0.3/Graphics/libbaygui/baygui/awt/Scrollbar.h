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

#if !defined(_SCROLLBAR_H_INCLUDED_)
#define _SCROLLBAR_H_INCLUDED_

namespace baygui {
	/**
	 �����E�����X�N���[���o�[�N���X
	*/
	class Scrollbar : public Component {
	public:
		/** �����X�N���[���o�[ */
		static const int HORIZONTAL = 0;
		/** �����X�N���[���o�[ */
		static const int VERTICAL   = 1;
		
	private:
		/** �X�N���[���o�[�̎�� */
		int orientation;
		/** �ŏ��l */
		int minimum;
		/** �ő�l */
		int maximum;
		/** ��x�ɑ�������� */
		int blocksize;
		/** ��O�̒l */
		int preValue;
		/** ���݂̒l */
		int value;
		/** �u���b�N�C�x���g */
		Event blockEvent;
		
	public:
		/** �f�t�H���g�R���X�g���N�^ */
		Scrollbar();

		/** �R���X�g���N�^ */
		Scrollbar(int orientation);

		/** �f�X�g���N�^ */
		virtual ~Scrollbar();

		/** �ŏ��l�𓾂�i�����l��0�j */
		inline int getMinimum() { return this->minimum; }

		/** �ő�l�𓾂�i�����l��100�j */
		inline int getMaximum() { return this->maximum; }

		/** ��x�ɑ�������ʂ𓾂�i�����l��10�j */
		inline int getBlocksize() { return this->blocksize; }

		/** �l�𓾂� */
		inline int getValue() { return this->value; }

		/** �ŏ��l��ݒ肷�� */
		inline void setMinimum(int n) { this->minimum = n; }

		/** �ő�l��ݒ肷�� */
		inline void setMaximum(int n) { this->maximum = n; }

		/** ��x�ɑ�������ʂ�ݒ肷�� */
		inline void setBlocksize(int n) { this->blocksize = n; }

		/** �l��ݒ肷�� */
		virtual void setValue(int value);

		/**
		 ���i�̑傫����ݒ肷��.
		 �����X�N���[���o�[�̎��͕�16�Œ�A�����X�N���[���o�[�̂Ƃ��͍���16�Œ�B
		 ����ȊO�̒l��ݒ肵�Ă�16�ɂȂ�B
		*/
		virtual void setBounds(int x, int y, int w, int h);

		/** �`��n���h�� */
		virtual void paint(Graphics* g);

		/** �C�x���g�n���h�� */
		virtual void processEvent(Event* event);
	};
}

#endif /* _SCROLLBAR_H_INCLUDED_ */

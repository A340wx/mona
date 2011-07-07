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

#if !defined(_WINDOW_H_INCLUDED_)
#define _WINDOW_H_INCLUDED_

namespace monagui {
	/**
	 �E�B���h�E�N���X
	*/
	class Window : public Container {
	public:
		//
		// �E�B���h�E�̏��
		//
		/** �ʏ펞 */
		static const int STATE_NORMAL = 0;
		/** �E�B���h�E�ړ��� */
		static const int STATE_MOVING = 1;
		
	private:
		/** �C���L�[ */
		int modifiers;
		/** �E�B���h�E�̏�� */
		int state;
		/** �ȑO�̃}�E�X��X���W */
		int preX;
		/** �ȑO�̃}�E�X��Y���W */
		int preY;
		/** �I�t�Z�b�gX */
		int offsetX;
		/** �I�t�Z�b�gY */
		int offsetY;
		/** �I�[�o�[���b�v�E�B���h�E�̏�� */
		dword overlap;
		/** ���s���t���O */
		bool isRunning;
		/** �^�C�}�[ID */
		dword timerID;
		/** �L�[�C�x���g */
		KeyEvent keyEvent;
		/** �}�E�X�C�x���g */
		MouseEvent mouseEvent;
		/** �^�C�}�[�C�x���g */
		Event timerEvent;
		/** �J�X�^���C�x���g */
		Event customEvent;

	protected:
		/** �t�`�̏�� */
		int border;
		/** �z�u�ʒu */
		Insets insets;
		/** �`��̈� */
		Graphics* _g; // �g����������
		/** �`��o�b�t�@�[ */
		Image* _buffer;
		/** �����`��̈� */
		Graphics* __g; // �^�C�g���o�[�Ȃ�
		/** �����`��o�b�t�@�[ */
		Image* __buffer;
		/** GUI�T�[�o�[ID */
		dword guisvrID;
		/** GUI�T�[�o�[��̃E�B���h�E�I�u�W�F�N�g */
		guiserver_window* _window;
	
	protected:
		/** ����{�^�����N���b�N���ꂽ���ǂ��� */
		virtual bool getCloseButtonClicked(int px, int py)
		{
			return false;
		}
		
		/** �^�C�g���o�[���N���b�N���ꂽ���ǂ��� */
		virtual bool getTitlebarClicked(int px, int py)
		{
			return (0 <= px && px < getWidth() && 0 <= py && py < getHeight()) ? true : false;
		}

	public:
		/** �R���X�g���N�^ */
		Window();
		
		/** �f�X�g���N�^ */
		virtual ~Window();

		/**
		 ���i�������n���h��.
		 Window::run()�ŌĂ΂��B
		 �Ǝ��̏�����t�^�������Ƃ���Window::addNotify()���ɌĂԂ��ƁB
		*/
		virtual void addNotify();
		
		/**
		 ���i�j���n���h��.
		 �f�X�g���N�^���ŌĂ΂��B
		 �Ǝ��̏�����t�^�������Ƃ���Window::removeNotify()����ŌĂԂ��ƁB
		 */
		virtual void removeNotify();

		/** �n���h���𓾂� */
		inline dword getHandle() { return (this->_window != NULL) ? this->_window->Handle : 0; }
		
		/** �z�u�ʒu�𓾂� */
		virtual Insets* getInsets();
		
		/** �`��I�u�W�F�N�g�𓾂� */
		virtual Graphics* getGraphics();
		
		/** �����o�b�t�@�[�𓾂� */
		virtual Image* getBuffer();
		
		/**
		 �\����Ԃ�ݒ肷��
		 @param visible �\����� (true / false)
		 */
		virtual void setVisible(bool visible);
		
		/**
		 �ʒu��ύX����
		 @param x X���W
		 @param y Y���W
		*/
		virtual void setLocation(int x, int y);
		
		/**
		 �^�C�}�[���Z�b�g����
		 @param duration �^�C�}�[�C�x���g����������܂ł̎���[ms]
		 */
		virtual void setTimer(int duration);
		
		/** �ĕ`�� */
		virtual void repaint();
		
		/** ���i�X�V */
		virtual void update();
		
		/** ���i�����X�V */
		virtual void update(int x, int y, int w, int h);
		
		/** �C�x���g���� */
		virtual void dispatchEvent(Event* event);
        
	    /** �A�v���P�[�V�������[�v�𔲂��� */
		virtual void stop();
		
		/** �A�v���P�[�V�������[�v */
		virtual void run();
	};
}

#endif // _WINDOW_H_INCLUDED_

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

/**
 �E�B���h�E�N���X
*/
class Window : public Container {
public:
	//
	// �E�B���h�E�I�t�Z�b�g
	//
	/** �E�B���h�E��[ */
	static const int INSETS_TOP       = 22;
	/** �E�B���h�E���[ */
	static const int INSETS_BOTTOM    = 6;
	/** �E�B���h�E���[ */
	static const int INSETS_LEFT      = 6;
	/** �E�B���h�E�E�[ */
	static const int INSETS_RIGHT     = 6;
	
	//
	// �E�B���h�E�̏��
	//
	/** �ʏ펞 */
	static const int STATE_NORMAL     = 0;
	/** �E�B���h�E�ړ��� */
	static const int STATE_MOVING     = 1;

private:
	/** �^�C�g�� */
	String title;
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
	unsigned int overlap;
	/** ���s���t���O */
	bool isRunning;
	/** �^�C�}�[ID */
	unsigned int timerID;
	/** �L�[�C�x���g */
	KeyEvent keyEvent;
	/** �}�E�X�C�x���g */
	MouseEvent mouseEvent;
	/** �^�C�}�[�C�x���g */
	Event timerEvent;
	/** �J�X�^���C�x���g */
	Event customEvent;
	/** �`��̈� */
	Graphics *_g;
	/** �`��o�b�t�@�[ */
	Image *_buffer;
	/** �����`��̈� */
	Graphics *__g;
	/** �����`��o�b�t�@�[ */
	Image *__buffer;
	
#ifdef MONA
protected:
	/** GUI�T�[�o�[��̃E�B���h�E�I�u�W�F�N�g */
	guiserver_window *_window;
#endif

public:
	/** �R���X�g���N�^ */
	Window();
	
	/** �f�X�g���N�^ */
	virtual ~Window();

	/**
	 ���i�������n���h��.
	 Window::run()�ŌĂ΂��B
	 �Ǝ��̏�����t�^�������Ƃ���Window::onStart()���ɌĂԂ��ƁB
	*/
	virtual void onStart();
	
	/**
	 ���i�j���n���h��.
	 �f�X�g���N�^���ŌĂ΂��B
	 �Ǝ��̏�����t�^�������Ƃ���Window::onExit()����ŌĂԂ��ƁB
	 */
	virtual void onExit();

	/** �n���h���𓾂� */
#ifdef MONA
	inline unsigned int getHandle() { return (this->_window != NULL) ? this->_window->Handle : 0; }
#else
	inline unsigned int getHandle() { return 0; }
#endif
	
	/** �`��I�u�W�F�N�g�𓾂� */
	virtual Graphics *getGraphics();
	
	/** �����o�b�t�@�[�𓾂� */
	virtual Image *getBuffer();
	
	/** �^�C�g���𓾂� */
	inline char *getTitle() { return this->title.getBytes(); }
	
	/**
	 �^�C�g���ݒ�
	 @param title �^�C�g��
	 */
	virtual void setTitle(char *title);
	
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
	
	/** �C�x���g���� */
	virtual void postEvent(Event *event);
	
	/** �A�v���P�[�V�������[�v�𔲂��� */
	virtual void stop();
	
	/** �A�v���P�[�V�������[�v */
	virtual void run();
};

#endif // _WINDOW_H_INCLUDED_

/*
Copyright (c) 2004 bayside
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	unsigned int getHandle();
	
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

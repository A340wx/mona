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

#if !defined(_CONTROL_H_INCLUDED_)
#define _CONTROL_H_INCLUDED_

class Container;

/**
 ���i�N���X
 */
class Control : public Object {
public:
	//
	// �z�u
	//
	/** ���� */
	static const int ALIGN_LEFT   = 1;
	/** ������ */
	static const int ALIGN_CENTER = 2;
	/** �E�� */
	static const int ALIGN_RIGHT  = 3;

private:
	/** �e���i */
	Container *parent;
	/** �����E�񊈐� */
	bool enabled;
	/** �t�H�[�J�X�L�� */
	bool focused;
	/** �\���E��\�� */
	bool visible;
	/** x�i��΍��W�j */
	int x;
	/** y�i��΍��W�j */
	int y;
	/** ���� */
	int height;
	/** �� */
	int width;
	/** �w�i�F */
	unsigned int backColor;
	/** �O�i�F */
	unsigned int foreColor;
	/** �t�H���g�X�^�C�� */
	int fontStyle;
	/** ���i�̑傫�� */
	Rect rect;
	/** �`��̈� */
	Graphics *_g;
	/** �`��o�b�t�@�[ */
	Image *_buffer;
	/** �t�H���g��� */
	FontMetrics *_metrics;

protected:
	/** �t�H�[�J�X�C�x���g */
	Event focusEvent;

public:
	/** �R���X�g���N�^ */
	Control();
	
	/** �f�X�g���N�^ */
	virtual ~Control();
	
	/**
	 ���i�����n���h��.
	 ���onExit()�ĂԂƍď������ł���B
	 */
	virtual void onStart();
	
	/**
	 ���i�j���n���h��.
	 ���onStart()���ĂԂƍď������ł���B
	*/
	virtual void onExit();

	/** �C�x���g�n���h�� */
	virtual void onEvent(Event *event);
	
	/** �`��n���h�� */
	virtual void onPaint(Graphics *g);
	
	/** �C�x���g���� */
	virtual void postEvent(Event *event);
	
	/**
	 �ĕ`��.
	 ���̒���onPaint()��update()���ĂԁB
	 */
	virtual void repaint();
	
	/** ���i�X�V */
	virtual void update();
	
	/** �e���i�𓾂� */
	inline Container *getParent() { return this->parent; }
	
	/** �����E�񊈐��𓾂� */
	inline bool getEnabled() { return this->enabled; }
	
	/** �t�H�[�J�X��Ԃ𓾂� */
	inline bool getFocused() { return this->focused; }
	
	/** �\���E��\���𓾂� */
	inline bool getVisible() { return this->visible; }
	
	/** X���W�𓾂� */
	inline int getX() { return this->x; }
	
	/** Y���W�𓾂� */
	inline int getY() { return this->y; }
	
	/** ���𓾂� */
	inline int getWidth() { return this->width; }
	
	/** �����𓾂� */
	inline int getHeight() { return this->height; }
	
	/** ���i�̑傫�� */
	inline Rect *getRect() { return &this->rect; }
	
	/** �w�i�F�𓾂� */
	inline unsigned int getBackground() { return this->backColor; }
	
	/** �O�i�F�𓾂� */
	inline unsigned int getForeground() { return this->foreColor; }
	
	/** �t�H���g�X�^�C���𓾂� */
	inline int getFontStyle() { return this->fontStyle; }
	
	/** �`��I�u�W�F�N�g�𓾂� */
	virtual Graphics *getGraphics() { return this->_g; }
	
	/**
	 �����o�b�t�@�[�𓾂�.
	 VRAM�̂悤�ɒ��ڕ`�悵�����Ƃ��ɗp����B
	 Graphics�N���X�������Ă���悤�ȕ֗��ȃ��\�b�h�͂Ȃ��B
	 �`���update()���ĂԂ��ƂŎ��ۂ̕`�悪�����B
	 */
	virtual Image *getBuffer() { return this->_buffer; }
	
	/** �t�H���g���𓾂� */
	inline FontMetrics *getFontMetrics() { return this->_metrics; }
	
	/**
	 ���C���E�B���h�E�𓾂�.
	 ���C���E�B���h�E�Ƃ͑S�Ă̕��i������Ă����ԉ��̃E�B���h�E�B
	 ���C���E�B���h�E�͊e�A�v���P�[�V�������ƂɕK���P���݂��Ă���B
	 */
	virtual Control *getMainWindow();
	
	/**
	 ������Ԃ�ݒ肷��
	 @param enabled ������� (true / false)
	 */
	virtual void setEnabled(bool enabled);
	
	/**
	 �t�H�[�J�X��Ԃ�ݒ肷��.
	 ���̃��\�b�h���ĂԂƊY�����i��FOCUS_IN�܂���FOCUS_OUT�C�x���g����������B
	 @param focused �t�H�[�J�X��� (true / false)
	 */
	virtual void setFocused(bool focused);
	
	/**
	 �\����Ԃ�ݒ肷��
	 @param visible �\����� (true / false)
	 */
	virtual void setVisible(bool visible);
	
	/**
	 �傫����ݒ肷��
	 @param x x���W
	 @param y y���W
	 @param width ��
	 @param height ����
	*/
	virtual void setRect(int x, int y, int width, int height);
	
	/**
	 �ʒu��ύX����
	 @param x X���W
	 @param y Y���W
	*/
	virtual void setLocation(int x, int y);
	
	/**
	 �e���i��ݒ肷��
	 @param parent �e���i
	*/
	virtual void setParent(Container *parent);
	
	/** �w�i�F��ݒ肷�� */
	virtual void setBackground(unsigned int backColor);
	
	/** �O�i�F��ݒ肷�� */
	virtual void setForeground(unsigned int foreColor);
	
	/**
	 �t�H���g�X�^�C���i�ʏ�A�����A�Ύ��A�Œ蕝�j��ݒ肷��.
	 �e�X�^�C����"|"�őg�ݍ��킹�邱�Ƃ��\�B
	 @param style �t�H���g�X�^�C�� (Font::PLAIN / Font::BOLD / Font::ITALIC / Font::FIXED )
	*/
	virtual void setFontStyle(int style);
};

#endif // _CONTROL_H_INCLUDED_

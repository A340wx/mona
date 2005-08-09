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

#if !defined(_COMPONENT_H_INCLUDED_)
#define _COMPONENT_H_INCLUDED_

namespace baygui {
	class Container;

	/**
	 ���i�N���X
	 */
	class Component : public Object {
	private:
		/** �e���i */
		Container* parent;
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
		dword backColor;
		/** �O�i�F */
		dword foreColor;
		/** �t�H���g�X�^�C�� */
		int fontStyle;
		/** ���i�̑傫�� */
		Rectangle bounds;
		/** �`��̈� */
		Graphics* _g;
		/** �`��o�b�t�@�[ */
		Image* _buffer;
		/** �t�H���g��� */
		FontMetrics* _metrics;

	protected:
		/** �t�H�[�J�X�C�x���g */
		Event focusEvent;

	public:
		/** �R���X�g���N�^ */
		Component();
		
		/** �f�X�g���N�^ */
		virtual ~Component();
		
		/**
		 ���i�����n���h��.
		 ���removeNotify()�ĂԂƍď������ł���B
		 */
		virtual void addNotify();
		
		/**
		 ���i�j���n���h��.
		 ���addNotify()���ĂԂƍď������ł���B
		*/
		virtual void removeNotify();

		/** �C�x���g�n���h�� */
		virtual void processEvent(Event* event);
		
		/** �`��n���h�� */
		virtual void paint(Graphics* g);
		
		/** �C�x���g���� */
		virtual void dispatchEvent(Event* event);
		
		/** �ĕ`�� */
		virtual void repaint();
		
		/** ���i�X�V */
		virtual void update();
		
		/** �e���i�𓾂� */
		inline Container* getParent() { return this->parent; }
		
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
		inline Rectangle* getBounds() { return &this->bounds; }
		
		/** �w�i�F�𓾂� */
		inline dword getBackground() { return this->backColor; }
		
		/** �O�i�F�𓾂� */
		inline dword getForeground() { return this->foreColor; }
		
		/** �t�H���g�X�^�C���𓾂� */
		inline int getFontStyle() { return this->fontStyle; }
		
		/** �`��I�u�W�F�N�g�𓾂� */
		virtual Graphics* getGraphics() { return this->_g; }
		
		/**
		 �����o�b�t�@�[�𓾂�.
		 VRAM�̂悤�ɒ��ڕ`�悵�����Ƃ��ɗp����B
		 Graphics�N���X�������Ă���悤�ȕ֗��ȃ��\�b�h�͂Ȃ��B
		 �`���update()���ĂԂ��ƂŎ��ۂ̕`�悪�����B
		 */
		virtual Image* getBuffer() { return this->_buffer; }
		
		/** �t�H���g���𓾂� */
		inline FontMetrics* getFontMetrics() { return this->_metrics; }
		
		/**
		 ���C���E�B���h�E�𓾂�.
		 ���C���E�B���h�E�Ƃ͑S�Ă̕��i������Ă����ԉ��̃E�B���h�E�B
		 ���C���E�B���h�E�͊e�A�v���P�[�V�������ƂɕK���P���݂��Ă���B
		 */
		virtual Component* getMainWindow();
		
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
		virtual void setBounds(int x, int y, int width, int height);
		
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
		virtual void setParent(Container* parent);
		
		/** �w�i�F��ݒ肷�� */
		virtual void setBackground(dword backColor);
		
		/** �O�i�F��ݒ肷�� */
		virtual void setForeground(dword foreColor);
		
		/**
		 �t�H���g�X�^�C���i�ʏ�A�����A�Ύ��A�Œ蕝�j��ݒ肷��.
		 �e�X�^�C����"|"�őg�ݍ��킹�邱�Ƃ��\�B
		 @param style �t�H���g�X�^�C�� (Font::PLAIN / Font::BOLD / Font::ITALIC / Font::FIXED )
		*/
		virtual void setFontStyle(int style);
	};
}

#endif // _COMPONENT_H_INCLUDED_

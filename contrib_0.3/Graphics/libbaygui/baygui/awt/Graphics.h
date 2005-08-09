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

#if !defined(_GRAPHICS_H_INCLUDED_)
#define _GRAPHICS_H_INCLUDED_

namespace baygui {
	/**
	 �`��N���X
	*/
	class Graphics : public Object {
	private:
		/** �`��J�nX���W */
		int tx;
		/** �`��J�nY���W */
		int ty;
		/** �N���b�s���O�̈�X���W */
		int cx;
		/** �N���b�s���O�̈�Y���W */
		int cy;
		/** �N���b�s���O�̈敝 */
		int cw;
		/** �N���b�s���O�̈捂��*/
		int ch;
		/** �F�i4�o�C�g�j */
		dword rgb24;
		/** �t�H���g�X�^�C�� */
		int fontStyle;
		/** �����o�b�t�@�[ */
		Image* image;

	public:
		/** �R���X�g���N�^ */
		Graphics();

		/**
		 �R���X�g���N�^
		 @param image �����o�b�t�@�[
		*/
		Graphics(Image* image);
		
		/** �f�X�g���N�^ */
		virtual ~Graphics();
		
		/**
		 �_�`��
		 @param x X���W
		 @param y Y���W
		 @param color �`�悷��F
		 */
		void drawPixel(int x, int y, dword color);
		
		/**
		 �C���[�W�`��
		 @param image �C���[�W
		 @param x �`��J�nX���W
		 @param y �`��J�nY���W
		 */
		void drawImage(Image* image, int x, int y);
		
		/**
		 �����`��
		 @param x0 �n�_X
		 @param y0 �n�_Y
		 @param x1 �I�_X
		 @param y1 �I�_Y
		 */
		void drawLine(int x0, int y0, int x1, int y1);
		
		/**
		 ��`�`��
		 @param x �n�_X
		 @param y �n�_Y
		 @param width ��
		 @param height ����
		 */
		void drawRect(int x, int y, int width, int height);
		
		/**
		 �~�`��
		 @param x0 ���SX
		 @param y0 ���SY
		 @param r  ���a
		 */
		void drawCircle(int x0, int y0, int r);
		
		/**
		 ������`��
		 @param str ������i�����s�Ή��j
		 @param x �n�_X
		 @param y �n�_Y
		 */
		void drawString(String str, int x, int y);
		
		/**
		 �~�h��Ԃ��`��
		 @param x0 ���SX
		 @param y0 ���SY
		 @param r  ���a
		 */
		void fillCircle(int x0, int y0, int r);
		
		/**
		 ��`�ʂ�Ԃ��`��
		 @param x �n�_X
		 @param y �n�_Y
		 @param width ��
		 @param height ����
		 */
		void fillRect(int x, int y, int width, int height);
		
		/**
		 ���W�ݒ�
		 @param x �n�_X
		 @param y �n�_Y
		 */
		void translate(int x, int y);
		
		/** �t�H���g�X�^�C���𓾂� */
		inline int getFontStyle() { return this->fontStyle; }
		
		/**
		 �N���b�s���O�̈�ݒ�
		 @param cx �n�_X
		 @param cy �n�_Y
		 @param cw �I�_X
		 @param ch �I�_Y
		 */
		void setClip(int cx, int cy, int cw, int ch);
		
		/**
		 �F�ݒ�
		 @param r ��(0-255)
		 @param g ��(0-255)
		 @param b ��(0-255)
		 */
		void setColor(unsigned char r, unsigned char g, unsigned char b);
		
		/**
		 �F�ݒ�
		 @param color (0x0-0xFFFFFF)
		 */
		void setColor(dword color);
		
		/**
		 �t�H���g�X�^�C���i�ʏ�A�����A�Ύ��A�Œ蕝�j��ݒ肷��.
		 �e�X�^�C����"|"�őg�ݍ��킹�邱�Ƃ��\�B
		 @param style �t�H���g�X�^�C�� (Font::PLAIN / Font::BOLD / Font::ITALIC / Font::FIXED )
		*/
		void setFontStyle(int style);
	};
}

#endif // _GRAPHICS_H_INCLUDED_

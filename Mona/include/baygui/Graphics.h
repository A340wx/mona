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

#if !defined(_GRAPHICS_H_INCLUDED_)
#define _GRAPHICS_H_INCLUDED_

/**
 �`��N���X
*/
class Graphics : public Object {
private:
	int tx, ty;
	int cx, cy, cw, ch;
	int width, height;
	/** �F�i4�o�C�g�j */
	unsigned int rgb24;
	/** �t�H���g�X�^�C�� */
	int fontStyle;
	/** �����o�b�t�@�[ */
	Image *image;

public:
	/** �R���X�g���N�^ */
	Graphics();

	/**
	 �R���X�g���N�^
	 @param image �����o�b�t�@�[
	*/
	Graphics(Image *image);
	
	/** �f�X�g���N�^ */
	virtual ~Graphics();
	
	/**
	 �_�`��
	 @param x X���W
	 @param y Y���W
	 @param color �`�悷��F
	 */
	void drawPixel(int x, int y, unsigned int color);
	
	/**
	 �C���[�W�`��
	 @param image �C���[�W
	 @param x �`��J�nX���W
	 @param y �`��J�nY���W
	 */
	void drawImage(Image *image, int x, int y);
	
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
	void drawText(char *str, int x, int y);
	
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
	
	/** ���𓾂� */
	inline int getWidth() { return this->width; }
	
	/** �����𓾂� */
	inline int getHeight() { return this->height; }
	
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
	void setColor(unsigned int color);
	
	/**
	 �t�H���g�X�^�C���i�ʏ�A�����A�Ύ��A�Œ蕝�j��ݒ肷��.
	 �e�X�^�C����"|"�őg�ݍ��킹�邱�Ƃ��\�B
	 @param style �t�H���g�X�^�C�� (Font::PLAIN / Font::BOLD / Font::ITALIC / Font::FIXED )
	*/
	void setFontStyle(int style);
};

#endif // _GRAPHICS_H_INCLUDED_

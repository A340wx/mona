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

/**
 �`��N���X
 */
public class Graphics {
	/** �`��J�nX���W */
	private int tx;
	/** �`��J�nY���W */
	private int ty;
	/** �N���b�s���O�̈�X���W */
	private int cx;
	/** �N���b�s���O�̈�Y���W */
	private int cy;
	/** �N���b�s���O�̈敝 */
	private int cw;
	/** �N���b�s���O�̈捂��*/
	private int ch;
	/** �F�i4�o�C�g�j */
	private int rgb24;
	/** �t�H���g�X�^�C�� */
	private int fontStyle;
	/** �����o�b�t�@�[ */
	private Image image;
	
	/** �R���X�g���N�^ */
	public Graphics() {
		tx = ty = cx = cy = cw = ch = 0;
		this.rgb24 = 0;
		this.fontStyle = Font.PLAIN;
		this.image = null;
	}

	/**
	 �R���X�g���N�^
	 @param image �����o�b�t�@�[
	*/
	public Graphics(Image image) {
		tx = ty = cx = cy = 0;
		this.rgb24 = 0;
		this.fontStyle = Font.PLAIN;
		this.image = image;
		this.cw = image.getWidth();
		this.ch = image.getHeight();
	}

	/**
	 �_�`��
	 @param x X���W
	 @param y Y���W
	 @param color �`�悷��F
	 */
	public void drawPixel(int x, int y, int color) {
		this.image.setPixel(tx + x, ty + y, color);
	}

	/**
	 �C���[�W�`��
	 @param image �C���[�W
	 @param x �`��J�nX���W
	 @param y �`��J�nY���W
	 */
	public void drawImage(Image image, int x, int y) {
		for (int i = 0; i < image.getHeight(); i++) {
			for (int j = 0; j < image.getWidth(); j++) {
				drawPixel(j + x, i + y, image.getPixel(j, i));
			}
		}
	}

	/**
	 �����`��
	 @param x1 �n�_X
	 @param y1 �n�_Y
	 @param x2 �I�_X
	 @param y2 �I�_Y
	 */
	public void drawLine(int x1, int y1, int x2, int y2) {
		int dx = (x1 > x2) ? (x1 - x2) : (x2 - x1);
		int dy = (y1 > y2) ? (y1 - y2) : (y2 - y1);
		
		if (dx == 0 && dy == 0) {
			this.drawPixel(x1, y1, this.rgb24);
		} else if (dx >= dy) {
			if (x1 > x2) {
				int tx = x1; x1 = x2; x2 = tx;
				int ty = y1; y1 = y2; y2 = ty;
			}
			for (int x = x1; x <= x2; x++) {
				this.drawPixel(x, ((2 * y1 + 2 * (y2 - y1) * (x - x1) / (x2 - x1)) + 1) / 2, this.rgb24);
			}
		} else {
			if (y1 > y2) {
				int tx = x1; x1 = x2; x2 = tx;
				int ty = y1; y1 = y2; y2 = ty;
			}
			for (int y = y1; y <= y2; y++) {
				this.drawPixel((2 * x1 + 2 * (x2 - x1) * (y - y1) / (y2 - y1) + 1) / 2, y, this.rgb24);
			}
		}
	}

	/**
	 ��`�`��
	 @param x �n�_X
	 @param y �n�_Y
	 @param width ��
	 @param height ����
	 */
	public void drawRect(int x, int y, int width, int height) {
		if (width < 0) {
			x += width;
			width = -width;
		}
		if (height < 0) {
			y += height;
			height = -height;
		}
		int xw = x + width - 1, yh = y + height - 1;
		for (int xx = x; xx <= xw; xx++) {
			this.drawPixel(xx, y , this.rgb24);
			this.drawPixel(xx, yh, this.rgb24);
		}
		for (int yy = y + 1; yy <= yh - 1; yy++) {
			this.drawPixel(x , yy, this.rgb24);
			this.drawPixel(xw, yy, this.rgb24);
		}
	}

	/**
	 �~�`��
	 @param x0 ���SX
	 @param y0 ���SY
	 @param r  ���a
	 */
	public void drawCircle(int x0, int y0, int r) {
		int x, y, f;
		x = r;
		y = 0;
		f = -2 * r + 3;

		while (x >= y) {
			drawPixel(x0 + x, y0 + y, this.rgb24);
			drawPixel(x0 - x, y0 + y, this.rgb24);
			drawPixel(x0 + y, y0 + x, this.rgb24);
			drawPixel(x0 - y, y0 + x, this.rgb24);
			drawPixel(x0 - x, y0 - y, this.rgb24);
			drawPixel(x0 - y, y0 - x, this.rgb24);
			drawPixel(x0 + y, y0 - x, this.rgb24);
			drawPixel(x0 + x, y0 - y, this.rgb24);
			if (f >= 0) {
				x--;
				f -= 4 * x;
			}
			y ++;
			f += 4 * y + 2;
		}
	}

	/**
	 ������`��
	 @param str ������i�����s�Ή��j
	 @param x �n�_X
	 @param y �n�_Y
	 */
	public void drawString(String str, int x, int y) {
		int pos, bit, offset, width, height, w = 0, h = 0;
		byte[] fp = new byte[256];
		
		// null�`�F�b�N
		if (str.length() == 0) return;
		
		FontMetrics fm = new FontMetrics();
		//metrics.setFontStyle(getFontStyle());
		int I = str.length();
		for (int i = 0; i < I; i++) {
			pos = 0;
			bit = 1;
			char ucs4 = str.charAt(i);
			// ���s
			if (ucs4 == '\n') {
				w = 0;
				h += 12;
			}
			if (fm.defaultFontData != null && fm.offsetList[ucs4] != 0) {
				int fw = fm.defaultFontData[fm.offsetList[ucs4] + 4];
				int fh = fm.defaultFontData[fm.offsetList[ucs4] + 5];
				//System.out.print("fontStyle = %d,", fm.getFontStyle());
				if ((fm.getFontStyle() & 0x100) == Font.FIXED) {
					if (ucs4 < 128 || 0xff60 < ucs4) {
						offset = 6;
					} else {
						offset = 12;
					}
				} else {
					offset = fw;
				}
				width  = fw;
				height = fh;
				//memcpy(data, &defaultFontData[offsetList[ucs4] + 6], (int)((fw * fh + 7) / 8));
				// fp �Ƀt�H���g�f�[�^��W�J����
				int J = (fw * fh + 7) / 8;
				for (int j = 0; j < J; j++) {
					fp[j] = fm.defaultFontData[fm.offsetList[ucs4] + 6 + j];
				}
				// �t�H���g�����ۂɕ`�悷��
				for (int j = 0; j < height; j++) {
					for (int k = 0; k < width; k++) {
						int x0 = x + w + k + (offset - width) / 2;
						// �s�p�f�B���O�Ȃ�
						if ((fp[pos] & bit) != 0) {
							// �ʏ폑��
							if ((getFontStyle() & 0x011) == Font.PLAIN) {
								drawPixel(x0, y + h + j, this.rgb24);
							// ������
							} else if ((getFontStyle() & 0x011) == Font.BOLD) {
								drawPixel(x0, y + j, this.rgb24);
								drawPixel(x0 + 1, y + j, this.rgb24);
							// �Ύ���
							} else if ((getFontStyle() & 0x011) == Font.ITALIC) {
								drawPixel(x0 + (height - j) / 4, y + j, this.rgb24);
							// �����́{�Ύ���
							} else if ((getFontStyle() & 0x011) == (Font.BOLD | Font.ITALIC)) {
								drawPixel(x0 + (height - j) / 4, y + j, this.rgb24);
								drawPixel(x0 + (height - j) / 4 + 1, y + j, this.rgb24);
							}
						}
						bit <<= 1;
						if (bit == 256) {
							pos++;
							bit = 1;
						}
					}
				}
				w += offset;
			}
		}
	}

	/**
	 �~�h��Ԃ��`��
	 @param x0 ���SX
	 @param y0 ���SY
	 @param r  ���a
	 */
	public void fillCircle(int x0, int y0, int r) {
		int i;
		int x, y;
		x = r;
		y = 0;
		int f = -2 * r + 3;

		while(x >= y) {
			for (i = x0 - x; i <= x0 + x; i ++) {
				drawPixel(i, y0 + y, this.rgb24);
				drawPixel(i, y0 - y, this.rgb24);
			}
			for (i = x0 - y; i <= x0 + y; i ++) {
				drawPixel(i, y0 - x, this.rgb24);
				drawPixel(i, y0 + x, this.rgb24);
			}
			if (f >= 0) {
				x--;
				f -= 4 * x;
			}
			y ++;
			f += 4 * y + 2;
		}
	}

	/**
	 ��`�ʂ�Ԃ��`��
	 @param x �n�_X
	 @param y �n�_Y
	 @param width ��
	 @param height ����
	 */
	public void fillRect(int x, int y, int width, int height) {
		if (width < 0) {
			x += width;
			width = -width;
		}
		if (height < 0) {
			y += height;
			height = -height;
		}
		
		int xw = x + width, yh = y + height;
		
		for (int yy = y; yy < yh; yy++) {
			for (int xx = x; xx < xw; xx++) {
				this.drawPixel(xx, yy, this.rgb24);
			}
		}
	}

	/**
	 ���W�ݒ�
	 @param x �n�_X
	 @param y �n�_Y
	 */
	public void translate(int x, int y) {
		tx = x;
		ty = y;
	}

	/** �t�H���g�X�^�C���𓾂� */
	public int getFontStyle() { return this.fontStyle; }

	/**
	 �N���b�s���O�̈�ݒ�
	 @param cx �n�_X
	 @param cy �n�_Y
	 @param cw �I�_X
	 @param ch �I�_Y
	 */
	public void setClip(int cx, int cy, int cw, int ch) {
		this.cx = cx;
		this.cy = cy;
		this.cw = cw;
		this.ch = ch;
	}

	/**
	 �F�ݒ�
	 @param r ��(0-255)
	 @param g ��(0-255)
	 @param b ��(0-255)
	 */
	public void setColor(int r, int g, int b) {
		this.rgb24 = 0xff000000 | (r << 16) | (g << 8) | b;
	}

	/**
	 �F�ݒ�
	 @param color (0x0-0xffffffff)
	 */
	public void setColor(int color) {
		this.rgb24 = color;
	}

	/**
	 �t�H���g�X�^�C���i�ʏ�A�����A�Ύ��A�Œ蕝�j��ݒ肷��.
	 �e�X�^�C����"|"�őg�ݍ��킹�邱�Ƃ��\�B
	 @param style �t�H���g�X�^�C�� (Font.PLAIN / Font.BOLD / Font.ITALIC / Font.FIXED )
	*/
	public void setFontStyle(int style) {
		this.fontStyle = style;
	}
}

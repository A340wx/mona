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

//import org.monaos.*;

/**
 �摜�N���X
 */
public class Image {
	/** �� */
	private int width;
	/** ���� */
	private int height;
	/** �o�b�t�@�[ */
	private int[] buffer;
	
	private native void create(Image image, String path);
	private void malloc(int width, int height) {
		this.buffer = new int [width * height];
	}
	
	/** �R���X�g���N�^ */
	public Image(int width, int height) {
		this.width = width;
		this.height = height;
		this.buffer = new int [width * height];
	}

	/** �R���X�g���N�^ */
	public Image(String path) {
		this.width = this.height = 0;
		create(this, path);
	}

	/** �摜��j������ */
	public void flush() {
		this.buffer = null;
	}

	/** ���𓾂� */
	public int getWidth() {
		return this.width;
	}

	/** �����𓾂� */
	public int getHeight() {
		return this.height;
	}

	/** �o�b�t�@�[�𓾂� */
	public int[] getBuffer() {
		return this.buffer;
	}

	/** �_�𓾂� */
	public int getPixel(int x, int y) {
		if (x < 0 || this.width <= x || y < 0 || this.height <= y) {
			return 0;
		} else {
			return this.buffer[x + this.width * y];
		}
	}

	/** �_��ł� */
	public void setPixel(int x, int y, int color) {
		if (0 <= x && x < this.width && 0 <= y && y < this.height) {
			this.buffer[x + this.width * y] = color;
		}
	}
}

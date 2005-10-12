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
 ��`�N���X
*/
public class Rectangle {
	/** x�i��΍��W�j*/
	public int x;
	/** y�i��΍��W�j*/
	public int y;
	/** ���� */
	public int height;
	/** �� */
	public int width;
	
	/** �f�t�H���g�R���X�g���N�^ */
	public Rectangle() {
		this.x = this.y = this.width = this.height = 0;
	}
	
	/** �R���X�g���N�^ */
	public Rectangle(int x, int y, int w, int h) {
		this.x = x;
		this.y = y;
		this.width = w;
		this.height = h;
	}
	
	/** �ʒu�Ƒ傫����ݒ肷�� */
	public void setBounds(int x, int y, int w, int h) {
		setLocation(x, y);
		setSize(w, h);
	}
	
	/** �ʒu��ݒ肷�� */
	public void setLocation(int x, int y) { this.x = x; this.y = y; }
	
	/** �傫����ݒ肷�� */
	public void setSize(int w, int h) { this.width = w; this.height = h; }
}

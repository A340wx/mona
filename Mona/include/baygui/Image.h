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

#if !defined(_IMAGE_H_INCLUDED_)
#define _IMAGE_H_INCLUDED_

/**
 �C���[�W�N���X
*/
class Image : public Object {
private:
	/** �� */
	int width;
	/** ���� */
	int height;
#ifndef MONA
	unsigned int* data;
#endif
	
#ifdef MONA
protected:
	/** GUI�T�[�o�[��̃r�b�g�}�b�v�I�u�W�F�N�g */
	guiserver_bitmap* bitmap;
#endif

public:
	Image();
	
	/**
	 �R���X�g���N�^
	 @param width ��
	 @param height ����
	 */
	Image(int width, int height);

	/**
	 �R���X�g���N�^.
	 �f�R�[�h�̓T�[�o�[���ōs���Ă���B
	 @param path �t�@�C����
	 */
	Image(char *path);
	
	/** �f�X�g���N�^ */
	virtual ~Image();
	
	/** �n���h���𓾂� */
#ifdef MONA
	inline unsigned int getHandle() { return this->bitmap->Handle; }
#else
	inline unsigned int getHandle() { return 0; }
#endif
	
	/** ���𓾂� */
	inline int getWidth() { return this->width; }
	
	/** �����𓾂� */
	inline int getHeight() { return this->height; }
	
	/** �w�肳�ꂽ�_�̐F�𓾂� */
	unsigned int getPixel(int x, int y);
	
	/**
	 �_��ł�
	 @param x X���W
	 @param y Y���W
	 @param color �F
	*/
	void setPixel(int x, int y, unsigned int color);
};

#endif // _IMAGE_H_INCLUDED_

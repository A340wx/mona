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

#if !defined(_LABEL_H_INCLUDED_)
#define _LABEL_H_INCLUDED_

/**
 ���x���N���X
*/
class Label : public Control {
private:
	/** �\���ʒu�i���񂹁A�����񂹁A�E�񂹁j*/
	int align;
	/** �\�������� */
	String text;
	
public:
	/**
	 �R���X�g���N�^.
	 �`��ʒu�� ALIGN_LEFT�B
	 @param text ���x��
	 */
	Label(char *text);
	
	/**
	 �R���X�g���N�^
	 @param text ���x��
	 @param align �`��ʒu (ALIGN_LEFT / ALIGN_CENTER / ALIGN_RIGHT)
	 */
	Label(char *text, int align);
	
	/** �f�X�g���N�^ */
	virtual ~Label();
	
	/**
	 �e�L�X�g�ݒ�
	 @param text
	 */
	virtual void setText(char *text);
	
	/** �e�L�X�g�𓾂� */
	inline  char *getText() { return this->text.getBytes(); }
	
	/** �`��n���h�� */
	virtual void onPaint(Graphics *g);
};

#endif // _LABEL_H_INCLUDED_

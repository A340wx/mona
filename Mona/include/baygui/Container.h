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

#if !defined(_CONTAINER_H_INCLUDED_)
#define _CONTAINER_H_INCLUDED_

/**
 �R���e�i�[�N���X
*/
class Container : public Control {
private:
	/** ���i�ꗗ */
	LinkedList *controlList;

public:
	/** �R���X�g���N�^ */
	Container();
	
	/** �f�X�g���N�^ */
	virtual ~Container();
	
	/**
	 �������i�𓾂�
	 @return �������i�i�Ȃ����NULL�j
	*/
	virtual Control *findChild();
	
	/**
	 ���i�𓾂�
	 @param x �w�肷��X���W
	 @param y �w�肷��Y���W
	 */
	virtual Control *findChild(int x, int y);
	
	/**
	 �w�肵�����i��ǉ�����
	 @param control �w�肷�镔�i
	 */
	virtual void add(Control *control);
	
	/**
	 �w�肵�����i���폜����
	 @param control �w�肷�镔�i
	 @return �폜���ꂽ���i�i�Ȃ����NULL�j
	 */
	virtual void remove(Control *control);
	
	/** �C�x���g���� */
	virtual void postEvent(Event *event);
	
	/** �ĕ`�� */
	virtual void repaint();
};

#endif // _CONTAINER_H_INCLUDED_

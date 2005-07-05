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

#if !defined(_LISTBOX_H_INCLUDED_)
#define _LISTBOX_H_INCLUDED_

/**
 ���X�g�{�b�N�X�N���X
*/
class ListBox : public Control {
private:
	/** �I���ʒu */
	int selectedIndex;
	/** �f�[�^���X�g */
	LinkedList *dataList;
	/** �I���C�x���g */
	Event itemEvent;

public:
	/** �R���X�g���N�^ */
	ListBox();
	
	/** �f�X�g���N�^ */
	virtual ~ListBox();
	
	/** �I���ʒu�𓾂� */
	inline  int getSelectedIndex() { return this->selectedIndex; }
	
	/** �I�����ڂ𓾂� */
	virtual char *getSelectedItem();
	
	/** index �Ԗڂ�I������ */
	virtual void select(int index);
	
	/** ���ڂ�ǉ����� */
	virtual void add(char *item);
	
	/** index �Ԗڂ̍��ڂ��폜���� */
	virtual void remove(int index);
	
	/** �`��n���h�� */
	virtual void onPaint(Graphics *g);
	
	/** �C�x���g�n���h�� */
	virtual void onEvent(Event *event);
};

#endif // _LISTBOX_H_INCLUDED_

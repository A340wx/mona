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

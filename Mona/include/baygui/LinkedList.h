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

#if !defined(_LINKEDLIST_H_INCLUDED_)
#define _LINKEDLIST_H_INCLUDED_

/**
 �o�����A�C�e���\���́i�o�������X�g�Ŏg�p�j
*/
struct LinkedItem {
	/** �����f�[�^ */
	Object *data;
	/** ���̃A�C�e���ւ̃|�C���^�[ */
	LinkedItem *next;
	/** �O�̃A�C�e���ւ̃|�C���^�[ */
	LinkedItem *prev;
};

/**
 �o�������X�g
*/
class LinkedList : public Object {
private:
	/** ���X�g�̒��� */
	int dataListLength;
	/** �ŏ� */
	LinkedItem *firstItem;
	/** �I��� */
	LinkedItem *endItem;
	/** remove����delete���s�����ǂ��� */
	bool autoDelete;
	
private:
	/** Object��LinkedItem�ɕϊ����� */
	LinkedItem *getLinkedItem(Object *o);
	
	/** �w�肵�����Ԃ̍��ڂ𓾂� */
	LinkedItem *getLinkedItem(int index);
	
public:
	/** �f�t�H���g�R���X�g���N�^ */
	LinkedList();
	
	/**
	 �R���X�g���N�^.
	 �f�t�H���g�ō��ڂ�remove����delete�����B
	 delete����邱�Ƃ�]�܂Ȃ��ꍇ��autoDelete��false��ݒ肷��B
	 @param autoDelete remove����delete���s�����ǂ����itrue / false�j
	*/
	LinkedList(bool autoDelete);
	
	/** �f�X�g���N�^ */
	virtual ~LinkedList();
	
	/** ���X�g�̒����𓾂� */
	inline int getLength() { return this->dataListLength; }
	
	/** �w�肵�����Ԃ̍��ڂ𓾂� */
	Object *get(int index);
	
	/** ��ԍŏ��̍��ڂ𓾂� */
	Object *getFirst();
	
	/** ��ԍŌ�̍��ڂ𓾂� */
	Object *getLast();
	
	/** �w�肵�����ڂ�ǉ����� */
	void add(Object *obj);
	
	/** �w�肵�����Ԃ̍��ڂ��폜���� */
	Object *remove(int index);
	
	/** �w�肵�����ڂ��폜���� */
	Object *remove(Object *o);
	
	/** �S�č폜���� */
	void removeAll();
};

#endif // _LINKEDLIST_H_INCLUDED_

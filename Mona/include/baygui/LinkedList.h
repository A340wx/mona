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

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

#include "baygui.h"

/** �R���X�g���N�^ */
LinkedList::LinkedList()
{
	dataListLength = 0;
	firstItem = NULL;
	endItem = NULL;
}

/** �f�X�g���N�^ */
LinkedList::~LinkedList()
{
	removeAll();
}

/** ���X�g�̒����𓾂� */
int LinkedList::getLength()
{
	return dataListLength;
}

/** �w�肵�����Ԃ̍��ڂ𓾂� */
LinkedItem *LinkedList::getItem(int index)
{
	// NULL�`�F�b�N
	if (index >= dataListLength) return NULL;
	if (firstItem == NULL) return NULL;
	// �ŏ��ƍŌ�`�F�b�N
	if (index == 0) return firstItem;
	if (index == dataListLength - 1) return endItem;
	// index�񃋁[�v
	LinkedItem *item = firstItem;
	for (int i = 0; i < index; i++) {
		item = item->next;
	}
	return item;
}

/** �ǉ� */
void LinkedList::add(LinkedItem *item)
{
	if (item == NULL) {
		return;
	} else if (firstItem == NULL) {
		firstItem = item;
		endItem = item;
	} else {
		LinkedItem *s = firstItem;
		while (s->next != NULL) {
			s = s->next;
		}
		item->prev = s;
		s->next = item;
		endItem = item;
	}
	dataListLength++;
}

/** �폜 */
void LinkedList::remove(LinkedItem *item)
{
	if (item == NULL) {
		return;
	} else if (item->next == NULL) {
		if (item->prev != NULL) {
			endItem = item->prev;
			endItem->next = NULL;
		} else {
			firstItem = NULL;
			endItem = NULL;
		}
		item->prev = NULL;
		item->next = NULL;
		delete(item);
	} else {
		if (item->prev != NULL) {
			item->prev->next = item->next;
			item->next->prev = item->prev;
		} else {
			firstItem = item->next;
			firstItem->prev = NULL;
		}
		item->prev = NULL;
		item->next = NULL;
		delete(item);
	}
	dataListLength--;
}

/** �S�폜 */
void LinkedList::removeAll()
{
	while (firstItem != NULL) {
		remove(firstItem);
	}
	dataListLength = 0;
}

/** �w�肵�����ڂ���ԍŌ�Ɏ����Ă��� */
void LinkedList::sort(LinkedItem *item)
{
	if (item == NULL) {
		return;
	} else if (item->next == NULL) {
		return;
	} else {
		if (item->prev != NULL) {
			item->prev->next = item->next;
			item->next->prev = item->prev;
		} else {
			firstItem = item->next;
			firstItem->prev = NULL;
		}
		item->prev = endItem;
		endItem->next = item;
		item->next = NULL;
		endItem = item;
	}
}

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
IN NO KEYEVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(_CHECKBOXGROUP_H_INCLUDED_)
#define _CHECKBOXGROUP_H_INCLUDED_

/**
 �`�F�b�N�{�b�N�X�O���[�v�N���X
*/
class CheckboxGroup : public Object {
private:
	LinkedList *checkboxList;
	
public:
	/** �R���X�g���N�^ */
	CheckboxGroup();
	
	/** �f�X�g���N�^ */
	virtual ~CheckboxGroup();
	
	/** �`�F�b�N�{�b�N�X��ǉ����� */
	virtual void add(Checkbox *check);
	
	/** �I�����ꂽ�`�F�b�N�{�b�N�X�𓾂� */
	virtual Checkbox *getSelectedCheckbox();
	
	/** �C�x���g�n���h�� */
	virtual void onEvent(Event *e);
};

#endif // _CHECKBOXGROUP_H_INCLUDED_

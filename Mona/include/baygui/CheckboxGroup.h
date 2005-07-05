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

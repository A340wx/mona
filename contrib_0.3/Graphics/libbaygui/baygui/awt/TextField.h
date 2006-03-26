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

#if !defined(_TEXTFIELD_H_INCLUDED_)
#define _TEXTFIELD_H_INCLUDED_

/** �e�L�X�g�t�B�[���h������ő咷 */
#define MAX_TEXT_LEN 128

namespace baygui {
	/**
	 �e�L�X�g�{�b�N�X�N���X
	*/
	class TextField : public Component {
	private:
		/** �J�[�\���̈ʒu */
		int textPtr;
		/** ������̒��� */
		int textLen;
		/** �I�t�Z�b�gX */
		int offx;
		/** �I�t�Z�b�gY */
		int offy;
		/** ���������� */
		char text[MAX_TEXT_LEN];
		
	protected:
		/** �e�L�X�g�C�x���g */
		Event textEvent;
		
	private:
		/** 1�����}������ */
		virtual void insertCharacter(char c);
		
		/** �ꕶ���폜���� */
		virtual void deleteCharacter();

	public:
		/** �R���X�g���N�^ */
		TextField();
		
		/** �f�X�g���N�^ */
		virtual ~TextField();
		
		/**
		 �e�L�X�g��ݒ肷��
		 @param text
		 */
		virtual void setText(const String& text);
		
		/** �e�L�X�g�𓾂� */
		inline char* getText() { return this->text; }
		
		/** �`��n���h�� */
		virtual void paint(Graphics* g);
		
		/** �C�x���g�n���h�� */
		virtual void processEvent(Event* event);
	};
}

#endif // _TEXTFIELD_H_INCLUDED_

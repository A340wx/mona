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

#if !defined(_BUTTON_H_INCLUDED_)
#define _BUTTON_H_INCLUDED_

namespace baygui {
	/**
	 �{�^���N���X
	*/
	class Button : public Component {
	private:
		/** �{�^���������ꂽ���ǂ��� */
		bool pushed;
		/** �{�^���̃��x�� */
		String label;
		
	public:
		/** �f�t�H���g�R���X�g���N�^ */
		Button();
		
		/**
		 �R���X�g���N�^
		 @param label ���x��
		 */
		Button(char* label);
		
		/** �f�X�g���N�^ */
		virtual ~Button();
		
		/**
		 ���x����ݒ肷��
		 @param label ���x��
		 */
		virtual void setLabel(char* label);
		
		/** �{�^���������ꂽ���ǂ����𓾂� */
		inline bool getPushed() { return this->pushed; }
		
		/** ���x���𓾂� */
		inline char* getLabel() { return this->label.getBytes(); }
		
		/** �`��n���h�� */
		virtual void paint(Graphics* g);
		
		/** �C�x���g�n���h�� */
		virtual void processEvent(Event* event);
	};
}

#endif // _BUTTON_H_INCLUDED_

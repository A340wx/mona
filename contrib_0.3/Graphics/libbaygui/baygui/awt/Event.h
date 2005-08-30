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

#if !defined(_EVENT_H_INCLUDED_)
#define _EVENT_H_INCLUDED_

namespace baygui {
	class Component;

	/**
	 �C�x���g���N���X
	*/
	class Event : public Object {
	public:
		//
		// �C�x���g�^�C�v�ꗗ
		//
		/** �L�[���� */
		static const int KEY_PRESSED      = 100;
		/** �L�[�����[�X */
		static const int KEY_RELEASED     = 101;
		/** �}�E�X�N���b�N */
		static const int MOUSE_PRESSED    = 200;
		/** �}�E�X�����[�X */
		static const int MOUSE_RELEASED   = 201;
		/** �}�E�X�h���b�O */
		static const int MOUSE_DRAGGED    = 202;
		/** �}�E�X�ړ� */
		static const int MOUSE_MOVED      = 203;
		/** �t�H�[�J�X�C�� */
		static const int FOCUS_IN         = 300;
		/** �t�H�[�J�X�A�E�g */
		static const int FOCUS_OUT        = 301;
		/** �^�C�}�[ */
		static const int TIMER            = 302;
		/** �e�L�X�g�m�� */
		static const int TEXT_CHANGED     = 303;
		/** ���ڑI�� */
		static const int ITEM_SELECTED    = 304;
		/** �u���b�N���� */
		static const int BLOCK_INCLEMENT  = 305;
		/** �u���b�N���� */
		static const int BLOCK_DECLEMENT  = 306;
		/** �{�^������ */
		static const int ACTION_PERFORMED = 307;
		/** �E�B���h�E�I�[�v�� */
		static const int WINDOW_OPENED    = 308;
		/** �E�B���h�E�N���[�Y */
		static const int WINDOW_CLOSED    = 309;
		/** �J�X�^���C�x���g */
		static const int CUSTOM_EVENT     = 400;
		
	private:
		/** �C�x���g�^�C�v */
		int type;
		/** �C�x���g������ */
		Component* source;
		/** �C�x���g����������ǂ��� */
		bool consumed;

	public:
		//
		// Mona�p�C�x���g
		//
		/** �w�b�_�[ */
		dword header;
		/** ����(1) */
		dword arg1;
		/** ����(2) */
		dword arg2;
		/** ����(3) */
		dword arg3;
		/** ���b�Z�[�W������ */
		dword from;
		/** ������ */
		char str[128];
		/** ������̒��� */
		int length;

	public:
		/** �f�t�H���g�R���X�g���N�^ */
		Event() {
			this->type = CUSTOM_EVENT;
			this->source = NULL;
			this->consumed = false;
		}
		
		/**
		 �R���X�g���N�^
		 @param type �C�x���g�^�C�v
		 @param source �C�x���g���������i
		 */
		Event(int type, Component* source) {
			this->type = type;
			this->source = source;
			this->consumed = false;
		}
		
		/** �f�X�g���N�^ */
		virtual ~Event() {}
		
		/** �C�x���g�^�C�v�𓾂� */
		inline int getType() { return this->type; }
		
		/** �C�x���g�^�C�v��ݒ肷�� */
		inline void setType(int type) { this->type = type; }
		
		/** �C�x���g�̔������i�𓾂� */
		inline Component* getSource() { return this->source; }
		
		/** �C�x���g�̔������i��ݒ肷�� */
		inline void setSource(Component* c) { this->source = c; }
		
		/** �C�x���g����������ǂ����𓾂� */
		inline bool isConsumed() { return this->consumed; }
		
		/** �C�x���g������� */
		inline void consume() { this->consumed = true; }
	};
}

#endif // _EVENT_H_INCLUDED_

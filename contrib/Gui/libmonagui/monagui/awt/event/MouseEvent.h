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

#if !defined(_MOUSEEVENT_H_INCLUDED_)
#define _MOUSEEVENT_H_INCLUDED_

namespace monagui {
	/**
	 �}�E�X�C�x���g�N���X
	*/
	class MouseEvent : public Event {
	public:
		static const int BUTTON_LEFT = 1;
		static const int BUTTON_RIGHT = 2;
		static const int BUTTON_MIDDLE = 3;
		
	private:
		/** X���W */
		int x;
		/** Y���W */
		int y;
		/** �{�^����� */
		dword button;
		
	public:
		/** �f�t�H���g�R���X�g���N�^ */
		MouseEvent() {
			setType(MOUSE_PRESSED);
			setSource(NULL);
			this->x = this->y = 0;
			this->button = 0;
		}
		
		/**
		 �R���X�g���N�^.
		 x, y �̓��C���E�B���h�E�̓����̈�̍���ɑ΂��鑊�΍��W�ł���B
		 ��΍��W(ax,ay)�͈ȉ��̂悤�Ɏ擾����B
		 <ul>
		 <li> ax = x + getMainWindow()->getRect()->getX() + Frame::getInsets()->left;
		 <li> ay = y + getMainWindow()->getRect()->getY() + Frame::getInsets()->top;
		 </ul>
		 @param type type �C�x���g�^�C�v
		 @param source �C�x���g������
		 @param x X���W�i��΍��W�j
		 @param y Y���W�i��΍��W�j
		*/
		MouseEvent(int type, Component* source, int x, int y)
		{
			setType(type);
			setSource(source);
			this->x = x;
			this->y = y;
		}
		
		/** �f�X�g���N�^ */
		virtual ~MouseEvent() {}
		
		/** X���W�𓾂� */
		inline int getX() { return this->x; }
		
		/** X���W��ݒ肷�� */
		inline void setX(int x) { this->x = x; }
		
		/** Y���W�𓾂� */
		inline int getY() { return this->y; }
		
		/** Y���W��ݒ肷�� */
		inline void setY(int y) { this->y = y; }
		
		/** �{�^����ʂ𓾂� */
		inline dword getButton() { return this->button; }
		
		/** �{�^����ʂ�ݒ肷�� */
		inline void setButton(dword button) { this->button = button; }
	};
}

#endif // _MOUSEEVENT_H_INCLUDED_

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
IN NO MOUSEEVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(_MOUSEEVENT_H_INCLUDED_)
#define _MOUSEEVENT_H_INCLUDED_

/**
 �}�E�X�C�x���g�N���X
*/
class MouseEvent : public Event {
private:
	/** X���W */
	int x;
	/** Y���W */
	int y;
	/** �{�^����� */
	unsigned int button;
	
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
	 <li> ax = x + getMainWindow()->getRect()->getX() + Window::INSETS_LEFT;
	 <li> ay = y + getMainWindow()->getRect()->getY() + Window::INSETS_TOP;
	 </ul>
	 @param type type �C�x���g�^�C�v
	 @param source �C�x���g������
	 @param x X���W�i��΍��W�j
	 @param y Y���W�i��΍��W�j
	*/
	MouseEvent(int type, Control *source, int x, int y)
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
	inline unsigned int getButton() { return this->button; }
	
	/** �{�^����ʂ�ݒ肷�� */
	inline void setButton(unsigned int button) { this->button = button; }
};

#endif // _MOUSEEVENT_H_INCLUDED_

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

#if !defined(_BAYGUI_H_INCLUDED_)
#define _BAYGUI_H_INCLUDED_

// ==================================================
// OS ��`����
// ==================================================
#define MONA  1
//#define SDL 1
//#define OSASK 1

// ==================================================
// OS �ˑ��w�b�_�t�@�C��
// ==================================================

typedef unsigned int dword;
typedef unsigned int wchar;

#if defined(MONA)
#include <monapi.h>
#include <monapi/messages.h>
#include <monalibc.h>
#include <servers/gui.h>
#elif defined(SDL)
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// ==================================================
// SDL�ˑ�����
// ==================================================

#include <SDL.h>
#undef   WIN32
#undef   main

/** �X�N���[���I�u�W�F�N�g */
extern SDL_Surface* screen;

// ==================================================
// GUI�T�[�o�ˑ�����
// ==================================================

/** GUI�T�[�o�[���r�b�g�}�b�v�\���� */
typedef struct {
	dword Handle;
	int Width, Height;
	dword* Data;
} guiserver_bitmap;

/** GUI�T�[�o�[���E�B���h�E�i���i�j�\���� */
typedef struct {
	dword Handle, Parent, Owner, ThreadID;
	int X, Y, Width, Height, OffsetX, OffsetY, Opacity;
	bool Visible, Focused;
	dword Flags, TransparencyKey;
	dword BufferHandle, FormBufferHandle;
	guiserver_bitmap* __internal1;
	bool __internal2;
	char __reserved[64];
} guiserver_window;

/** GUI�T�[�o�[���E�B���h�E�X�^�C�� */
enum
{
	WINDOWFLAGS_NOBORDER = 1,
	WINDOWFLAGS_MODAL = 2,
	WINDOWFLAGS_NOACTIVATE = 4,
	WINDOWFLAGS_TOPMOST = 8,
	WINDOWFLAGS_BOTTOMMOST = 16
};

#define MAKE_DWORD(a, b) (((dword)(unsigned short)(a)) + (((dword)(unsigned short)(b)) << 16))
#define GET_X_DWORD(a) ((int)(short)(a & 0xffff))
#define GET_Y_DWORD(a) ((int)(short)((a) >> 16))

// ==================================================
// MonAPI�ˑ�����
// ==================================================

/** MonAPI�_�~�[�萔 */
enum {
	MONAPI_FALSE = 0,
	MONAPI_TRUE  = 1,
	THREAD_UNKNOWN,
	ID_GUI_SERVER,
	MSG_GUISERVER_CREATEWINDOW,
	MSG_GUISERVER_CREATEBITMAP,
	MSG_GUISERVER_ACTIVATEWINDOW,
	MSG_GUISERVER_DISPOSEWINDOW,
	MSG_GUISERVER_MOVEWINDOW,
	MSG_GUISERVER_DRAWWINDOW,
	MSG_GUISERVER_MOUSECAPTURE,
	MSG_GUISERVER_CREATEOVERLAP,
	MSG_GUISERVER_DISPOSEOVERLAP,
	MSG_GUISERVER_MOVEOVERLAP,
	MSG_GUISERVER_DECODEIMAGE,
	MSG_GUISERVER_DISPOSEBITMAP
};

/** MonAPI�_�~�[�\���� */
typedef struct {
	dword header;
	dword arg1;
	dword arg2;
	dword arg3;
	dword from;
	char str[128];
	int length;
} MessageInfo;

namespace MonAPI {
	/** MonAPI�_�~�[�N���X */
	class MemoryMap {
	public:
		static void* map(dword size)
		{
			char* memory = new char [size];
			memset(memory, 0, size);
			return memory;
		}
	};
	
	/** MonAPI�_�~�[�N���X */
	class Message {
	public:
		static const int equalsHeader = 0;
		
	public:
		static int lookupMainThread(char *processName)
		{
			return 0;
		}
		
		static int send(dword thread_id, dword msg_id)
		{
			return 0;
		}
		
		static int send(dword thread_id, dword msg_id, dword arg1)
		{
			return 0;
		}
		
		static int reply(MessageInfo* info)
		{
			return 0;
		}
		
		static int receive(MessageInfo* info)
		{
			return 0;
		}
		
		static int receive(MessageInfo* info, MessageInfo* src, int msg_id)
		{
			return 0;
		}
		
		static int sendReceive(MessageInfo* info, dword thread_id, dword msg_id)
		{
			if (msg_id == MSG_GUISERVER_CREATEWINDOW) {
				info->arg2 = sizeof(guiserver_window);
			}
			return 0;
		}
		
		static int sendReceive(MessageInfo* info, dword thread_id, dword msg_id, dword arg1)
		{
			return 0;
		}
		
		static int sendReceive(MessageInfo* info, dword thread_id, dword msg_id, dword arg1, dword arg2)
		{
			return 0;
		}
		
		static int sendReceive(MessageInfo* info, dword thread_id, dword msg_id, dword arg1, dword arg2, dword arg3)
		{
			if (msg_id == MSG_GUISERVER_CREATEBITMAP) {
				info->arg2 = sizeof(guiserver_bitmap);
			}
			return 0;
		}
		
		static int sendReceive(MessageInfo* info, dword thread_id, dword msg_id, dword arg1, dword arg2, dword arg3, const char* str)
		{
			return 0;
		}
	};
	
	/** MonAPI�_�~�[�N���X */
	class System {
	public:
		static dword getThreadID()
		{
			return 0;
		}
	};
}

/** MonAPI�_�~�[���\�b�h */
dword monapi_get_server_thread_id(dword serverID);

/** MonAPI�_�~�[���\�b�h */
bool monapi_register_to_server(int serverID, int isCout);

/** MonAPI�_�~�[���\�b�h */
dword syscall_get_tid();

/** MonAPI�_�~�[���\�b�h */
dword syscall_mthread_create(dword funcID);

/** MonAPI�_�~�[���\�b�h */
void syscall_mthread_join(dword threadID);

/** MonAPI�_�~�[���\�b�h */
void syscall_kill_thread(dword threadID);

/** MonAPI�_�~�[���\�b�h */
void kill_timer(dword timerID);
#endif

// ==================================================
// BayGUI �O���[�o���}�N��
// ==================================================

#define inGetUInt16(b) (unsigned short)( (unsigned short)((b)[1])<<8 | (unsigned short)((b)[0]) )
#define inGetUInt32(b) (dword)( (dword)((b)[3])<<24 | (dword)((b)[2])<<16 | (dword)((b)[1])<<8 | (dword)((b)[0]) )
#define inGetUInt16(b) (unsigned short)( (unsigned short)((b)[1])<<8 | (unsigned short)((b)[0]) )

#define BAYGUI_VERSION "BayGUI $Date$"
#define BAYGUI_COPYING "Copyright (C) 2004-2005, bayside."

// ==================================================
// BayGUI �w�b�_�t�@�C��
// ==================================================

#include "baygui/awt/Font.h"
#include "baygui/awt/Color.h"
#include "baygui/lang/Object.h"
#include "baygui/lang/Pointer.h"
#include "baygui/lang/String.h"
#include "baygui/lang/Runnable.h"
#include "baygui/lang/Thread.h"
#include "baygui/util/Vector.h"
#include "baygui/util/Hashtable.h"
#include "baygui/awt/Event.h"
#include "baygui/awt/event/KeyEvent.h"
#include "baygui/awt/event/MouseEvent.h"
#include "baygui/awt/Insets.h"
#include "baygui/awt/Rectangle.h"
#include "baygui/awt/FontMetrics.h"
#include "baygui/awt/Image.h"
#include "baygui/awt/Graphics.h"
#include "baygui/awt/Component.h"
#include "baygui/awt/Checkbox.h"
#include "baygui/awt/CheckboxGroup.h"
#include "baygui/awt/Button.h"
#include "baygui/awt/Label.h"
#include "baygui/awt/ListBox.h"
#include "baygui/awt/Scrollbar.h"
#include "baygui/awt/TextField.h"
#include "baygui/awt/Container.h"
#include "baygui/awt/Window.h"
#include "baygui/awt/Frame.h"

using namespace baygui;

#endif // _BAYGUI_H_INCLUDED_

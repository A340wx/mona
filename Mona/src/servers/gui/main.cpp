/*!
	\file  main.cpp
	\brief  MonaForms GUI�T�[�o ���C��

	This software is in the public domain.
	There are no restrictions on any sort of usage of this software.

	\author   
	\version $Revision$
	\date   create: update:$Date$
*/

#include <gui/System/Drawing/Rectangle.h>
#define _R ::System::Drawing::Rectangle

#include <monapi/messages.h>
#include <monapi/CString.h>

#include "GUIServer.h"
#include "image.h"
#include "screen.h"
#include "utils.h"
#include "window.h"

using namespace MonAPI;

// ��ʃo�b�t�@
extern guiserver_bitmap* screen_buffer;

// �v���Z�X�ԋ��ʃp�����[�^
CommonParameters* commonParams;
// �ǎ�
guiserver_bitmap* wallpaper = NULL;
// �������ʁA�폜���ʁA���ʂ̃X�e�b�v���A���ʂ̍��ݎ���(ms)
int we_creation = 0, we_destruction = 0, we_step = 6, we_wait = 30;

// �N���C�A���g�̃��X�g
static HList<dword> clients;
// ���L��������Ɋm�ۂ���t�H���g
static monapi_cmemoryinfo* default_font = NULL;
// �ǎ����J���Ƃ��Ƀv�����v�g�ɏ���\�����邩�ǂ���
static bool wallpaper_prompt = false;
// �X�^�[�g�A�b�v�A�v���P�[�V����
static HList<CString>* startup = NULL;

/*!
\brief ReadFont
	 ���L�������Ɏw��t�H���g�����[�h
\param  const char* file [in] �t�H���g�t�@�C����
\author 
\date   create: update:$Date$
*/
static void ReadFont(const char* file)
{
	monapi_cmemoryinfo* mi = monapi_call_file_decompress_bz2_file(file, true);
	if (mi == NULL) return;
	
	default_font = mi;
}

/*!
\brief DrawWallPaper
	 �ǎ���`�悷��
\param  guiserver_bitmap* bmp [in] �ǎ�
\param  int pos [in] �\���ʒu
\param  unsigned int transparent [in] �����x (0x0-0xFFFFFF)
\param  const char* src [in] �ǎ��t�@�C����
\param  bool prompt [in] �v�����v�g��\�����邩�ǂ���
\author 
\date   create: update:$Date$
*/
static void DrawWallPaper(guiserver_bitmap* bmp, int pos, unsigned int transparent, const char* src, bool prompt)
{
	if (wallpaper == NULL || bmp == NULL) return;
	
	int x = 0, y = 0, ww = wallpaper->Width, wh = wallpaper->Height;
	switch (pos)
	{
		case 0: // Stretch
		{
			if (ww != bmp->Width || wh != bmp->Height)
			{
				if (prompt) printf("%s: Resizing %s....", SVR, (const char*)src);
				guiserver_bitmap* bmp2 = ResizeBitmap(bmp, ww, wh);
				DisposeBitmap(bmp->Handle);
				bmp = bmp2;
				if (prompt) printf("Done\n");
			}
			break;
		}
		case 1: // Top Left
			break;
		case 2: // Top Center
			x = (ww - bmp->Width) / 2;
			break;
		case 3: // Top Right
			x = ww - bmp->Width;
			break;
		case 4: // Center Left
			y = (wh - bmp->Height) / 2;
			break;
		case 5: // Center Center
			x = (ww - bmp->Width) / 2;
			y = (wh - bmp->Height) / 2;
			break;
		case 6: // Center Right
			x = ww - bmp->Width;
			y = (wh - bmp->Height) / 2;
			break;
		case 7: // Bottom Left
			y = wh - bmp->Height;
			break;
		case 8: // Bottom Center
			x = (ww - bmp->Width) / 2;
			y = wh - bmp->Height;
			break;
		case 9: // Bottom Right
			x = ww - bmp->Width;
			y = wh - bmp->Height;
			break;
	}
	DrawImage(wallpaper, bmp, x, y, 0, 0, -1, -1, transparent);
	DisposeBitmap(bmp->Handle);
}

/*!
\brief DrawWallPaper
	 �ǎ���`�悷��
\param  const char* src [in] �ǎ��t�@�C����
\param  int pos [in] �\���ʒu
\param  unsigned int transparent [in] �����x (0x0-0xFFFFFF)
\param  int background [in] �w�i�F (0x0-0xFFFFFF)
\author 
\date   create: update:$Date$
*/
static void DrawWallPaper(const char* src, int pos, unsigned int transparent, int background)
{
	bool prompt = wallpaper_prompt;
	wallpaper_prompt = false;
	
	Screen* scr = GetDefaultScreen();
	if (wallpaper == NULL)
	{
		wallpaper = CreateBitmap(scr->getWidth(), scr->getHeight(), background);
		if (wallpaper == NULL) return;
	}
	else
	{
		FillColor(wallpaper, background);
	}
	
	guiserver_bitmap* bmp = ReadImage(src, prompt);
	if (bmp != NULL) DrawWallPaper(bmp, pos, transparent, src, prompt);
	DrawImage(screen_buffer, wallpaper);
	DrawScreen();
}


/*!
\brief ReadConfig
	 �ݒ�t�@�C�� MONAGUI.INI ���MonaForms�̐ݒ�𓾂�
\author 
\date   create: update:$Date$
*/
static void ReadConfig()
{
	monapi_cmemoryinfo* cfg = monapi_call_file_read_data("/MONAGUI.INI", MONAPI_TRUE);
	if (cfg == NULL) return;
	
	if (startup != NULL)
	{
		delete startup;
		startup = NULL;
	}
	char line[256];
	int linepos = 0, wppos = 5;
	unsigned int wptp = 0, bgcol = 0;
	CString section, src;
	for (dword pos = 0; pos <= cfg->Size; pos++)
	{
		char ch = pos < cfg->Size ? (char)cfg->Data[pos] : '\n';
		if (ch == '\r' || ch == '\n')
		{
			if (linepos > 0)
			{
				CString ln(line, linepos);
				if (ln.toUpper().startsWith("REM "))
				{
					// ignore remark
				}
				else if (ln.startsWith("[") && ln.endsWith("]"))
				{
					section = ln.substring(1, ln.getLength() - 2).toUpper();
				}
				else if (ln.indexOf('=') > 0)
				{
					_A<CString> data = CString(line, linepos).split('=');
					if (data.get_Length() == 2 && data[0] != NULL && data[1] != NULL)
					{
						CString name = data[0].toUpper();
						if (section == "GENERAL")
						{
							if (name == "RUN")
							{
								if (startup == NULL) startup = new HList<CString>();
								_A<CString> runs = data[1].split(',');
								FOREACH (CString, r, runs) startup->add(r); END_FOREACH
							}
						}
						else if (section == "WALLPAPER")
						{
							if (name == "SOURCE")
							{
								src = data[1];
							}
							else if (name == "POSITION")
							{
								wppos = atoi(data[1]);
							}
							else if (name == "TRANSPARENCYKEY")
							{
								wptp = xtoui(data[1]);
							}
							else if (name == "BACKCOLOR")
							{
								bgcol = ((unsigned int)xtoui(data[1])) | 0xff000000;
							}
						}
						else if (section == "WINDOW EFFECT")
						{
							if (name == "CREATION")
							{
								we_creation = atoi(data[1]);
							}
							else if (name == "DESTRUCTION")
							{
								we_destruction = atoi(data[1]);
							}
							else if (name == "STEP")
							{
								we_step = atoi(data[1]);
							}
							else if (name == "WAIT")
							{
								we_wait = atoi(data[1]);
							}
						}
					}
				}
				linepos = 0;
			}
		}
		else if (linepos < 255)
		{
			line[linepos++] = ch;
		}
	}
	monapi_cmemoryinfo_dispose(cfg);
	monapi_cmemoryinfo_delete(cfg);
	if (src[0] == '\0') return;

	wallpaper_prompt = true;
	DrawWallPaper(src, wppos, wptp, bgcol);
}

/*!
\brief CheckGUIServer
	 MonaForms�T�[�o �N���ς݃`�F�b�N
	 ���ɋN�����Ă���΁A2�d�N�������I������B
\author 
\date   create: update:$Date$
*/
static void CheckGUIServer()
{
	syscall_set_ps_dump();
	PsInfo info;

	bool ok = true;
	CString self = "GUI.EX2";
	dword tid = MonAPI::System::getThreadID();

	while (syscall_read_ps_dump(&info) == 0)
	{
		if (ok && self == info.name && tid != info.tid) ok = false;
	}
	if (ok) return;

	printf("%s: already has executed!\n", SVR);
	exit(1);
}

/*!
\brief MessageLoop
	 MonaForms�T�[�o ���b�Z�[�W���[�v
\author 
\date   create: update:$Date$
*/
static void MessageLoop()
{
	for (MessageInfo msg;;)
	{
		if (Message::receive(&msg)) continue;
		
		switch (msg.header)
		{
			// �t�H���g�擾�v��
			case MSG_GUISERVER_GETFONT:
				// �t�H���g�̃n���h���A�t�H���g�̃T�C�Y
				Message::reply(&msg, default_font->Handle, default_font->Size);
				break;
			// �ǎ����[�h�v��
			case MSG_GUISERVER_SETWALLPAPER:
				// �t�@�C�����A�\���ʒu�A�����x�A�w�i�F
				DrawWallPaper(msg.str, msg.arg1, msg.arg2, msg.arg3);
				Message::reply(&msg);
				break;
			// ��ʍX�V�v��
			case MSG_GUISERVER_DRAWSCREEN:
				// x, y, w, h
				DrawScreen(msg.arg1, msg.arg2, GET_X_DWORD(msg.arg3), GET_Y_DWORD(msg.arg3));
				Message::reply(&msg);
				break;
			// �o�^�v��
			case MSG_REGISTER_TO_SERVER:
				// threadID
				clients.add(msg.arg1);
				Message::reply(&msg);
				break;
			// �폜�v��
			case MSG_UNREGISTER_FROM_SERVER:
				// threadID
				clients.remove(msg.arg1);
				Message::reply(&msg);
				break;
			default:
				if (ImageHandler(&msg)) break;
				if (WindowHandler(&msg)) break;
				break;
		}
	}
}

/*!
\brief MonaMain
	MonaForms�T�[�o ���C��
\param List<char*>* pekoe [in] �R�}���h���C������
\author
\date   create: update:$Date$
*/
int MonaMain(List<char*>* pekoe)
{
	// 2�d�N���`�F�b�N
	CheckGUIServer();
	if (!InitScreen()) exit(1);

	MessageInfo msg_cp;
	if (Message::sendReceive(&msg_cp, monapi_get_server_thread_id(ID_PROCESS_SERVER), MSG_PROCESS_GET_COMMON_PARAMS) != 0)
	{
		printf("%s: can not get common parameters!\n", SVR);
		exit(1);
	}
	commonParams = (CommonParameters*)MemoryMap::map(msg_cp.arg2);
	
	if (!monapi_register_to_server(ID_MOUSE_SERVER, MONAPI_TRUE)) exit(1);
	if (!monapi_register_to_server(ID_KEYBOARD_SERVER, MONAPI_TRUE)) exit(1);

	// �t�H���g�̃��[�h
	ReadFont("/MONA-12.MF2");
	if (default_font == NULL) exit(1);
	
	// �ݒ�t�@�C���̃��[�h
	ReadConfig();
	if (startup != NULL)
	{
		for (int i = 0; i < startup->size(); i++) {
			monapi_call_process_execute_file(startup->get(i), MONAPI_FALSE);
		}
	}

	// MONITOR�T�[�o�ւ̐���N���ʒm
	Message::send(Message::lookupMainThread("MONITOR.BIN"), MSG_SERVER_START_OK);

	// ���b�Z�[�W���[�v
	MessageLoop();

	// ���L�������Ƀ��[�h���Ă���t�H���g�̉��
	monapi_cmemoryinfo_dispose(default_font);
	monapi_cmemoryinfo_delete(default_font);
	
	// �ǎ��̊J��
	if (wallpaper != NULL) DisposeBitmap(wallpaper->Handle);
	DisposeScreen();
	
	monapi_register_to_server(ID_MOUSE_SERVER, MONAPI_FALSE);
	monapi_register_to_server(ID_KEYBOARD_SERVER, MONAPI_FALSE);
	MemoryMap::unmap(msg_cp.arg2);
	
	return 0;
}

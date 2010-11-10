// This file's encoding is UTF-8.

#include "FileWindow.h"
#include "Icon.h"
#include <gui/System/Mona/Forms/ControlPaint.h>
#include <monapi.h>

#define VIEW_OFFSET_X 8
#define VIEW_OFFSET_Y 8

using namespace System;
using namespace System::Drawing;
using namespace System::Mona::Forms;

extern uint32_t gui_server;
extern int ProcessStart(const String& file);

#define BASE Control

inline String PathCombine(String path1, String path2)
{
    return path1 == "/" ? "/" + path2 : path1 + "/" + path2;
}

FileBrowser::FileBrowser()
{
    this->set_BackColor(Color::get_White());
    this->offset = Point(2, 2);
    this->files = NULL;
    this->target = this->clickTarget = -1;
    this->skip = 0;
}

void FileBrowser::Dispose()
{
    BASE::Dispose();
    if (this->files == NULL) return;

    this->files->unmap();
    delete this->files;
    this->files = NULL;
}

void FileBrowser::ReadDirectory(String path)
{
    this->path = path;
    int len = path.get_Length();
    char* buf = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        wchar ch = path[i];
        buf[i] = ch < 128 ? (char)ch : '?';
    }
    buf[len] = '\0';
    if (this->files != NULL)
    {
        this->files->unmap();
        delete this->files;
    }
    this->files = monapi_file_read_directory(buf);
    delete [] buf;
    if (this->files == NULL) return;

    if (this->get_Visible()) this->Refresh();
}

void FileBrowser::OnPaint()
{
    _P<Graphics> gf = Graphics::FromImage(this->buffer);
    ControlPaint::DrawSunken(gf, 0, 0, this->get_Width(), this->get_Height());
    gf->Dispose();
    if (this->path.get_Length() < 1) return;

    _P<Graphics> g = this->CreateGraphics();
    Size sz = this->get_ClientSize();
    int w = sz.Width, h = sz.Height;
    g->FillRectangle(this->get_BackColor(), 0, 0, w, h);
    if (this->files == NULL)
    {
        g->DrawString("ディレクトリが開けません:\n\n" + this->path,
            Control::get_DefaultFont(), Color::get_Black(), 20, 20);
    }
    else
    {
        int x = VIEW_OFFSET_X, y = VIEW_OFFSET_Y;
        int len = *(int*)this->files->data();
        this->skip = 0;
        monapi_directoryinfo* di = (monapi_directoryinfo*)&this->files->data()[sizeof(int)];
        for (int i = 0; i < len; i++, di++)
        {
            String name = di->name;
            if (name == ".")
            {
                this->skip = 1;
                continue;
            }
            Icons icon = Icon::GetIcon(di);
            if (icon == Icons_Executable && (this->path == "/" || this->path == "/SERVERS")) icon = Icons_Server;
            Icon::DrawIcon(g, name, icon, x, y, false, i == this->target + this->skip);
            x += ARRANGE_WIDTH;
            if (x + ARRANGE_WIDTH >= w)
            {
                x = 8;
                y += ARRANGE_HEIGHT;
            }
        }
    }
    g->Dispose();
}

int FileBrowser::GetTarget(int ex, int ey)
{
    if (this->files == NULL) return -1;

    int x = (ex - VIEW_OFFSET_X) / ARRANGE_WIDTH, y = (ey - VIEW_OFFSET_Y) / ARRANGE_HEIGHT;
    int nx = (this->get_ClientSize().Width - VIEW_OFFSET_X) / ARRANGE_WIDTH;
    if (x >= nx) return -1;

    int len = *(int*)this->files->data() - this->skip;
    int num = x + y * nx;
    if (num >= len) return -1;

    return num;
}

void FileBrowser::OnMouseMove(_P<MouseEventArgs> e)
{
    BASE::OnMouseMove(e);

    int old = this->target;
    this->target = e->Button == 0 ? GetTarget(e->X, e->Y) : -1;
    if (old != this->target) this->Refresh();
}

void FileBrowser::OnMouseDown(_P<MouseEventArgs> e)
{
    BASE::OnMouseDown(e);
    if (e->Button != 1) return;

    this->clickTarget = GetTarget(e->X, e->Y);
}

void FileBrowser::OnMouseUp(_P<MouseEventArgs> e)
{
    BASE::OnMouseUp(e);
    if (e->Button != 1) return;

    int t = GetTarget(e->X, e->Y);
    if (this->clickTarget == t) this->Open(t);
    this->clickTarget = -1;
}

void FileBrowser::OnMouseLeave(_P<EventArgs> e)
{
	BASE::OnMouseLeave(e);
	if (this->target == -1) return;
	
	this->target = -1;
	this->Refresh();
}

void FileBrowser::Open(int target)
{
    if (this->files == NULL) return;

    int len = *(int*)this->files->data() - this->skip;
    if (target < 0 || target >= len) return;

    monapi_directoryinfo* di = (monapi_directoryinfo*)&this->files->data()[sizeof(int)] + this->skip + target;
    String name = di->name;
    Icons icon = Icon::GetIcon(di);
    if (icon == Icons_Executable && (this->path == "/" || this->path == "/SERVERS")) icon = Icons_Server;
    Size sz = this->get_ClientSize();
    int nx = (sz.Width - VIEW_OFFSET_X) / ARRANGE_WIDTH;
    int x = (target % nx) * ARRANGE_WIDTH + VIEW_OFFSET_X;
    int y = ((int)(target / nx)) * ARRANGE_HEIGHT + VIEW_OFFSET_Y;
    Point pc = this->PointToScreen(Point(x + ARRANGE_WIDTH / 2, y + ARRANGE_HEIGHT / 2));

    switch (icon)
    {
        case Icons_Folder:
        {
            Point po = this->PointToScreen(Point::get_Empty());
            _P<FileWindow> fw = this->get_Parent().get();
            if (name == "..")
            {
                int p = -1;
                for (int i = this->path.get_Length() - 1; i >= 0; i--)
                {
                    if (this->path[i] == '/')
                    {
                        p = i;
                        break;
                    }
                }
                if (p >= 0)
                {
                    MonAPI::Message::sendReceive(NULL, gui_server, MSG_GUISERVER_REDUCTIONEFFECT,
                        MAKE_DWORD(po.X + sz.Width / 2, po.Y + sz.Height / 2),
                        MAKE_DWORD(po.X, po.Y), MAKE_DWORD(sz.Width, sz.Height));
                    fw->set_Directory(p == 0 ? "/" : this->path.Substring(0, p));
                }
            }
            else
            {
                MonAPI::Message::sendReceive(NULL, gui_server, MSG_GUISERVER_EXPANSIONEFFECT,
                    MAKE_DWORD(pc.X, pc.Y), MAKE_DWORD(po.X, po.Y), MAKE_DWORD(sz.Width, sz.Height));
                fw->set_Directory(PathCombine(this->path, name));
            }
            break;
        }
        case Icons_Executable:
        case Icons_Terminal:
        {
            Icon::ExpansionEffect(pc.X, pc.Y);
            String exe = PathCombine(this->path, name);
            if (exe.EndsWith(".APP"))
            {
                exe = PathCombine(exe, name.Substring(0, name.get_Length() - 4) + ".EX5");
                if (ProcessStart(exe) != 0)
                {
                    exe = exe.Substring(0, exe.get_Length() - 1) + "2";
                    ProcessStart(exe);
                }
            }
            else if (exe.EndsWith(".NES") || exe.EndsWith(".NE5"))
            {
                ProcessStart("/APPS/BAYGUI/INFONES.EX5 " + exe);
            }
            else
            {
                ProcessStart(exe);
            }
            break;
        }
        case Icons_Picture:
        {
            Icon::ExpansionEffect(pc.X, pc.Y);
            String img = PathCombine(this->path, name);
            if (img.EndsWith(".MPG"))
            {
                ProcessStart("/APPS/BAYGUI/XMONAPEG.EX5 " + img);
            }
            else
            {
                ProcessStart("/APPS/MONAFRMS/BITMAP.EX5 " + img);
            }
            break;
        }
        default:
            break;
    }
}

#include <monapi.h>
#include <monapi/CString.h>
#include <monapi/messages.h>
#include <jpegls.h>

using namespace MonAPI;

int OpenJpeg(const char* filename)
{
    // 16bpp以下では表示しない
    Screen screen;
    if (screen.getBpp() < 16)
    {
        printf("screen information (x, y) = (%d, %d) %dbpp\n", screen.getWidth(), screen.getHeight(), screen.getBpp());
        printf("sorry, this demo needs 16bpp or higher Video mode\n");
        return -1;
    }

    scoped_ptr<SharedMemory> shm(monapi_file_read_all(filename));

    if (shm.get() == NULL)
    {
        printf("file %s not found", filename);
        return -1;
    }

    CJPEGLS* jpeg = new CJPEGLS();

    // JPEGファイルを開く
    if (jpeg->Open(shm->data(), shm->size()) != 0)
    {
        printf("not supported image\n");
        return -1;
    }

    int w, h;
    jpeg->GetInfo(&w, &h);
    uint8_t* picture = new uint8_t[w * h * 3];
    jpeg->Decode(picture);

    int x, y;
    int vesaWidth  = screen.getWidth();
    int vesaHeight = screen.getHeight();
    int vesaBpp    = screen.getBpp() / 8;
    int ww         = w < vesaWidth ? w : vesaWidth;
    int hh         = h < vesaHeight ? h : vesaHeight;
    uint8_t* vesaVram = screen.getVRAM();

    for (y = 0; y < hh; y++)
    {
        for (x = 0; x < ww; x++)
        {
            int k  = (x + (y * vesaWidth)) * vesaBpp;
            int k2 = (x + (y * w)) * 3;
            if (vesaBpp == 2)
            {
                *(uint16_t*)&vesaVram[k] = Color::bpp24to565(picture[k2], picture[k2 + 1], picture[k2 + 2]);
            }
            else
            {
                vesaVram[k]   = picture[k2 + 2];
                vesaVram[k+1] = picture[k2 + 1];
                vesaVram[k+2] = picture[k2 + 0];
            }
        }
    }

    delete [] picture;
    delete jpeg;
    return 0;
}

int OpenSlide(List<CString>* list, int i)
{
    if (list->get(i).endsWith(".jpg") || list->get(i).endsWith(".JPG"))
    {
        // 画像を開く
        CString cstr = list->get(i);
        return OpenJpeg((const char*)cstr);
    }
    else if (list->get(i).endsWith(".mpg") || list->get(i).endsWith(".MPG"))
    {
        // 動画を開く
        CString cstr = "/APPS/MONAPEG.EX5 ";
        cstr += list->get(i);
        syscall_set_cursor(0,0);
        return monapi_call_process_execute_file((const char*)cstr, MONAPI_FALSE);
    }
    else
    {
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    // 設定ファイル名
    const char* filepath;
    if (argc < 2)
    {
        filepath = "/APPS/MONAPPT.INI";
    }
    else
    {
        filepath = argv[1];
    }

    // ファイル読み込み
    printf("loading %s ...\n", filepath);
    scoped_ptr<SharedMemory> shm(monapi_file_read_all(filepath));
    if (shm.get() == NULL || shm->size() == 0)
    {
        printf("file read error\n");
        return(-1);
    }
    uint32_t filesize = shm->size();
    uint8_t* filebuff = (uint8_t*)malloc(shm->size());
    if (filebuff == NULL)
    {
        printf("memory allocate error\n");
        return(-1);
    }
    memcpy(filebuff, shm->data(), shm->size());

    // ファイル解析
    HList<CString> list;
    uint8_t temp[128];
    memset(temp, '\0', sizeof(temp));
    for (int i = 0; i < (int)filesize; i++)
    {
        if (filebuff[i] == '\r')
        {
            // do nothing
        }
        else if (filebuff[i] == '\n' || i == (int)filesize - 1)
        {
            list.add((const char*)temp);
            memset(temp, '\0', sizeof(temp));
        }
        else
        {
            temp[strlen((const char*)temp)] = filebuff[i];
        }
    }
    free(filebuff);

    // キーサーバーに登録する
    syscall_clear_screen();
    syscall_set_cursor(0,0);
    if (M_OK != monapi_register_to_server(ID_KEYBOARD_SERVER)) exit(1);

    // １枚目のスライド
    int slideno = 0;
    if (OpenSlide(&list, slideno) == 0)
    {

        // メッセージループ
        for (MessageInfo info;;)
        {
            if (MonAPI::Message::receive(&info) != 0) continue;

            if (info.header == MSG_KEY_VIRTUAL_CODE)
            {
                int keycode  = info.arg1;
                int modcode  = info.arg2;
                //int charcode = info.arg3;
                if ((modcode & KEY_MODIFIER_DOWN) == KEY_MODIFIER_DOWN)
                {
                    int result = -1;
                    if (keycode == Keys::Escape)
                    {
                        break;
                    }
                    else if (keycode == Keys::Enter || keycode == MonAPI::Keys::Right || keycode == 102)
                    {
                        // 次のスライド
                        if (slideno == list.size() - 1)
                        {
                            result = OpenSlide(&list, list.size() - 1);
                        }
                        else
                        {
                            result = OpenSlide(&list, ++slideno);
                        }
                    }
                    else if (keycode == Keys::Back || keycode == MonAPI::Keys::Left || keycode == 100)
                    {
                        // 前のスライド
                        if (slideno == 0)
                        {
                            result = OpenSlide(&list, 0);
                        }
                        else
                        {
                            result = OpenSlide(&list, --slideno);
                        }
                    }
                    // エラーが起きたので終了～
                    if (result != 0) break;
                }
            }
        }
    }

    // キーサーバーから登録解除する
    monapi_unregister_to_server(ID_KEYBOARD_SERVER);
    syscall_clear_screen();
    syscall_set_cursor(0,0);

    return(0);
}

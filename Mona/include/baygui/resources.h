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
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(_RESOURCES_H_INCLUDED_)
#define _RESOURCES_H_INCLUDED_

/** BayGUIバージョン */
#define BAYGUI_VERSION   "BayGUI build "__DATE__

//#define WINDOWMANAGER_MENU_TITLE_JP "ファイル　編集　表示　特別　ヘルプ"
//#define WINDOWMANAGER_MENU_TITLE_EN "File Edit View Special Help"
//#define WINDOWMANAGER_STARUP_MESSAGE "starting baygui ...\n"
//#define WINDOWMANAGER_SHUTDOWN_MESSAGE "shutdown baygui ...\n"

/** テキストフィールド文字列最大長 */
#define MAX_TEXT_LEN      64

//
// ウィンドウオフセット
//

/** ウィンドウ上端 */
#define INSETS_TOP        22
/** ウィンドウ下端 */
#define INSETS_BOTTOM     6
/** ウィンドウ左端 */
#define INSETS_LEFT       6
/** ウィンドウ右端 */
#define INSETS_RIGHT      6

//
// ウィンドウの状態
//

/** 通常時 */
#define STATE_NORMAL      0
/** ウィンドウ移動中 */
#define STATE_MOVING      1

//
// 書体
//

/** 通常書体 */
#define FONT_PLAIN        0x000
/** 太字体 */
#define FONT_BOLD         0x001
/** 斜字体 */
#define FONT_ITALIC       0x010
/** 固定幅 */
#define FONT_FIXED        0x100

//
// 配置
//

/** 左寄せ */
#define ALIGN_LEFT        1
/** 中央寄せ */
#define ALIGN_CENTER      2
/** 右寄せ */
#define ALIGN_RIGHT       3

//
// 部品の初期色
//

#define DEFAULT_TRANSCOLOR 0x00000000
#define DEFAULT_FORECOLOR  0xff000000
#define DEFAULT_BACKCOLOR  0xffc0c0c0

//
// システム標準16色に準拠
//

#define COLOR_BLACK     0xff000000
#define COLOR_MAROON    0xff800000
#define COLOR_GREEN     0xff008000
#define COLOR_OLIVE     0xff808000
#define COLOR_NAVY      0xff000080
#define COLOR_PURPLE    0xff800080
#define COLOR_TEAL      0xff008080
#define COLOR_LIGHTGRAY 0xffC0C0C0
#define COLOR_GRAY      0xff808080
#define COLOR_RED       0xffff0000
#define COLOR_LIME      0xff00ff00
#define COLOR_YELLOW    0xffffff00
#define COLOR_BLUE      0xff0000ff
#define COLOR_MAGENDA   0xffff00ff
#define COLOR_CYAN      0xff00ffff
#define COLOR_WHITE     0xffffffff

//
// イベントタイプ一覧
//

/** キー押下 */
#define KEY_PRESSED     100
/** キーリリース */
#define KEY_RELEASED    101
/** マウスクリック */
#define MOUSE_PRESSED   200
/** マウスリリース */
#define MOUSE_RELEASED  201
/** マウスドラッグ */
#define MOUSE_DRAGGED   202
/** マウス移動 */
#define MOUSE_MOVED     203
/** フォーカスイン */
#define FOCUS_IN        300
/** フォーカスアウト */
#define FOCUS_OUT       301
/** タイマー */
#define TIMER           302
/** テキスト確定 */
#define TEXT_CHANGED    303
/** 項目選択 */
#define ITEM_SELECTED   304
/** ブロック増加 */
#define BLOCK_INCLEMENT 305
/** ブロック減少 */
#define BLOCK_DECLEMENT 306
/** カスタムイベント */
#define CUSTOM_EVENT    400

//
// 特殊キーコード一覧
//

#define VKEY_ESC         0
#define VKEY_BACKSPACE  14
#define VKEY_TAB        15
#define VKEY_ENTER      28

#define VKEY_PGUP      354
#define VKEY_PGDOWN    355
#define VKEY_INSERT    356
#define VKEY_DELETE    357
#define VKEY_UP        358
#define VKEY_LEFT      359
#define VKEY_RIGHT     360
#define VKEY_DOWN      361
#define VKEY_HOME      362
#define VKEY_END       363

#define VKEY_F11       382
#define VKEY_F12       383
#define VKEY_F1        398
#define VKEY_F2        399
#define VKEY_F3        400
#define VKEY_F4        401
#define VKEY_F5        402
#define VKEY_F6        403
#define VKEY_F7        404
#define VKEY_F8        405
#define VKEY_F9        406
#define VKEY_F10       407
#define VKEY_LSHIFT    412
#define VKEY_ALT       415
#define VKEY_CTRL      416
#define VKEY_RMENU     424
#define VKEY_LMENU     425
#define VKEY_RSHIFT    427

#endif // _RESOURCES_H_INCLUDED_

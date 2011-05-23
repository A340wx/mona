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

#if !defined(_IMEMANAGER_H_INCLUDED_)
#define _IMEMANAGER_H_INCLUDED_

#include "monagui/awt/Component.h"

/**
 IMEマネージャクラス
*/
class ImeManager : public Component {
private:
    /** IMEサーバーID */
    dword imesvrID;
    /** 漢字リスト */
    HList<MonAPI::CString> kanjiList;
    /** 漢字リストポインター */
    int kanjiListPtr;
    /** 入力文字列バッファー */
    char inputBuffer[MAX_TEXT_LEN];
    /** 変換対象文字列バッファー */
    char translateBuffer[MAX_TEXT_LEN];
    /** IMEモード（オンなら日本語入力中）*/
    bool isOn_;
    /** IMEイベント */
    Event *_imeEvent;
    /** 親部品 */
    Component *parent;

    virtual void clearKanjiList();
    virtual void clearBuffer();
    virtual bool getKanji(char *str, HList<MonAPI::CString> *result);
    virtual bool getKana(char *inputBuffer, char *str);

public:
    ImeManager();
    virtual ~ImeManager();
    virtual const char* getFixedString() const;
    virtual bool isOn() const { return isOn_; }
    virtual void clearBuffer(char *buffer);
    virtual void insertCharacter(char *buffer, char c);
    virtual void insertString(char *buffer, const char *str);
    virtual int  deleteCharacter(char *buffer);
    virtual void setParent(Component *parent);
    virtual void paint(Graphics* g);
    virtual void processEvent(Event *event);
};

#endif // _IMEMANAGER_H_INCLUDED_

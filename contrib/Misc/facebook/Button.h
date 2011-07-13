/*
 *   Copyright (c) 2011  Higepon(Taro Minowa)  <higepon@users.sourceforge.jp>
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _FACEBOOK_BUTTON_
#define _FACEBOOK_BUTTON_

namespace facebook {

class Button : public monagui::Button
{
public:
    Button(const char* title) : monagui::Button(title)
    {
        setBackground(monagui::Color::white);
        setForeground(0xff6d84b4);
    }

    virtual ~Button()
    {
    }

    void paint(Graphics* g)
    {
        int w = getWidth();
        int h = getHeight();

        g->setColor(getBackground());
        g->fillRect(0, 0, w, h);

        if (getPushed()) {
            g->setColor(Color::white);
            g->drawLine(2, h - 2, w - 3, h - 2);
            g->drawLine(w - 2, 2, w - 2, h - 3);
            g->drawLine(w - 3 , h - 3, w - 3, h - 3);
            g->setColor(Color::gray);
            g->drawLine(1, 2, 1, h - 3);
            g->drawLine(2, 1, w - 3, 1);
        }
        int fw = getFontMetrics()->getWidth(getLabel());
        int fh = getFontMetrics()->getHeight(getLabel());
        int x = (w - fw) / 2;
        int y = (h - fh) / 2;
        if (getPushed()) {
            x++;
            y++;
        }

        g->setColor(getForeground());
        g->drawString(getLabel(), x, y);
    }
};

};

#endif // _FACEBOOK_BUTTON_

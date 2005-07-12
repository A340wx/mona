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

#include "baygui.h"

/** 未チェック（パレット） */
static dword unchecked_palette[] = {
	0xff040204,
	0xff8c8e8c,
	0xffe4e2e4,
	0xff4c4e4c,
	0xffb4b2b4,
	0xfffcfefc,
	0xffc0c0c0, // 背景色
	0xffeceeec,
	0xff5c5e5c,
	0xffc4c2c4,
};

/** 未チェック（データ）*/
static unsigned char unchecked_data[] = {
	0x6,0x6,0x6,0x6,0x3,0x0,0x0,0x3,0x6,0x6,0x6,0x6,
	0x6,0x6,0x0,0x8,0x2,0x2,0x2,0x9,0x3,0x0,0x6,0x6,
	0x6,0x0,0x9,0x2,0x7,0x5,0x5,0x5,0x2,0x1,0x0,0x6,
	0x6,0x8,0x2,0x7,0x5,0x5,0x7,0x7,0x2,0x9,0x3,0x6,
	0x3,0x2,0x7,0x5,0x5,0x7,0x7,0x7,0x2,0x9,0x1,0x3,
	0x0,0x2,0x5,0x5,0x7,0x7,0x2,0x2,0x9,0x9,0x1,0x0,
	0x0,0x2,0x5,0x7,0x7,0x7,0x2,0x9,0x9,0x4,0x1,0x0,
	0x3,0x9,0x5,0x7,0x2,0x2,0x9,0x9,0x4,0x4,0x1,0x3,
	0x6,0x8,0x2,0x2,0x2,0x9,0x9,0x4,0x4,0x1,0x3,0x6,
	0x6,0x0,0x1,0x9,0x9,0x9,0x4,0x4,0x1,0x1,0x0,0x6,
	0x6,0x6,0x0,0x8,0x1,0x1,0x1,0x1,0x3,0x0,0x6,0x6,
	0x6,0x6,0x6,0x6,0x3,0x0,0x0,0x3,0x6,0x6,0x6,0x6,
};

/** チェック（パレット） */
static dword checked_palette[] = {
	0xff040204,
	0xff8c8e8c,
	0xff4c4e4c,
	0xffe4e2e4,
	0xffc0c0c0, // 背景色
	0xffc4c2c4,
	0xff7c7e7c,
	0xff2c2a2c,
	0xff9c9e9c,
	0xfffcfefc,
	0xff5c5e5c,
};

/** チェック（データ）*/
static unsigned char checked_data[] = {
	0x4,0x4,0x4,0x4,0x7,0x0,0x0,0x7,0x4,0x4,0x4,0x4,
	0x4,0x4,0x7,0x0,0x2,0xa,0xa,0xa,0x2,0x0,0x4,0x4,
	0x4,0x7,0x2,0xa,0x6,0x6,0x6,0x1,0x1,0x8,0x0,0x4,
	0x4,0x0,0xa,0x6,0x0,0x0,0x0,0x0,0x8,0x8,0x2,0x4,
	0x7,0x2,0x6,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x5,0x2,
	0x0,0xa,0x6,0x0,0x0,0x0,0x0,0x0,0x0,0x5,0x5,0x0,
	0x0,0xa,0x6,0x0,0x0,0x0,0x0,0x0,0x0,0x5,0x3,0x0,
	0x7,0xa,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x9,0x2,
	0x4,0x7,0x1,0x8,0x0,0x0,0x0,0x0,0x3,0x9,0x2,0x4,
	0x4,0x7,0x8,0x8,0x8,0x5,0x5,0x3,0x9,0x9,0x0,0x4,
	0x4,0x4,0x7,0x2,0x5,0x5,0x3,0x9,0x2,0x0,0x4,0x4,
	0x4,0x4,0x4,0x4,0x2,0x0,0x0,0x2,0x4,0x4,0x4,0x4,
};

Checkbox::Checkbox(char* label)
{
	this->checked = false;
	this->label  = label;
	this->itemEvent.setType(Event::ITEM_SELECTED);
	this->itemEvent.setSource(this);
	this->group = NULL;
}

Checkbox::~Checkbox()
{
}

void Checkbox::setChecked(bool checked)
{
	if (this->checked == true && checked == false) {
		this->checked = false;
		repaint();
	} else if (this->checked == false && checked == true) {
		this->checked = true;
		// 選択イベント発生
		if (this->group != NULL) {
			this->group->processEvent(&this->itemEvent);
			getParent()->processEvent(&this->itemEvent);
		}
		repaint();
	}
}

void Checkbox::setLabel(char *label)
{
	this->label = label;
	repaint();
}

void Checkbox::paint(Graphics *g)
{
	int w = getWidth(), h = getHeight();
	
	// 一度背景色でクリア
	g->setColor(getBackground());
	g->fillRect(0, 0, w, h);
	
	// 文字
	int fh = getFontMetrics()->getHeight(getLabel());
	int y = (h - fh) / 2;
	if (getEnabled() == true) {
		g->setColor(getForeground());
	} else {
		g->setColor(Color::gray);
	}
	g->drawText(getLabel(), 14, y);
	
	// チェック
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			// チェックの周りは背景色で塗る
			dword c = 0;
			if (this->checked == true) {
				c = checked_palette[checked_data[i * 12 + j] & 0xFF];
			} else {
				c = unchecked_palette[unchecked_data[i * 12 + j] & 0xFF];
			}
			if (c == 0xffc0c0c0) {
				c = getBackground();
			}
			g->drawPixel(j + 0, i + y, c);
		}
	}

}

void Checkbox::processEvent(Event *event)
{
	// 非活性の時はイベントを受け付けない
	if (getEnabled() == false) return;

	if (event->getType() == MouseEvent::MOUSE_RELEASED) {
		if (this->checked == false || this->group == NULL) {
			setChecked(!this->checked);
		}
		getParent()->processEvent(event);
	}
}

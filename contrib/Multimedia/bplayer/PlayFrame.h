/*!
    \file   bplayer.cpp
    \brief  beep music player

    Copyright (c) 2006 Higepon
    All rights reserved.
    License=MIT/X License

    \author  Higepon
    \version $Revision$
    \date   create:2006/11/21 update:$Date$
*/

#ifndef _PLAY_FRAME_
#define _PLAY_FRAME_

#include <monagui.h>

namespace monagui
{
class PlayFrame : public Window
{
protected:
    Image* icon;

protected:
    virtual bool getCloseButtonClicked(int px, int py)
    {
        int w = getWidth();
        return (w - 12 <= px && px <= w - 7 && 6 <= py && py <= 11);
    }

    virtual bool getTitlebarClicked(int px, int py)
    {
        return (0 <= px && px < getWidth() - 12 && 0 <= py && py < getInsets()->top);
    }

public:
    PlayFrame(const char* iconPath);
    virtual ~PlayFrame();
    virtual void repaint();
};
}

#endif // _PLAY_FRAME_

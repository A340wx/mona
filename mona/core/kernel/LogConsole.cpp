/*!
    \file  LogConsole.cpp
    \brief class LogConsole

    class LogConsole

    Thanks nanashi at wiki.osdev.info

    Copyright (c) 2004 Higepon
    All rights reserved.
    License=MIT/X License

    \author  Higepon
    \version $Revision$
    \date   create:2004/03/05 update:$Date$
    \date   2007-12-14 Changed to use Uart driver.
*/

#include "LogConsole.h"
#include "global.h"

/*!
    \brief initialize

    \author Higepon
    \date   create:2004/03/05 update:
*/
#define BUFFER_SIZE 4096
LogConsole::LogConsole()
{
    com1_ = new Uart(Uart::COM1);
    buf_ = new char[4096];
}

/*!
    \brief printf

    \param  color background color
    \author Higepon
    \date   create:2004/03/05 update:
*/
void LogConsole::setBGColor(const char color)
{
}

/*!
    \brief printf

    \param  color character color
    \author Higepon
    \date   create:2004/03/05 update:
*/
void LogConsole::setCHColor(const char color)
{
}

/*!
    \brief printf

    \param  format
    \author Higepon
    \date   create:2004/03/05 update:
*/
void LogConsole::printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vsprintf(buf_, format, ap);
    va_end(ap);
    if (ret >= BUFFER_SIZE) {
        this->print("bufer over at VesaConsole::printf");
    }
    print(buf_);
}

/*!
    \brief clear screen

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::clearScreen()
{
}

/*!
    \brief set cursor

    set cursor at (x, y)

    \param x position x
    \param y position y

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::setCursor(int x, int y)
{
}

void LogConsole::getCursor(int* x, int* y)
{
}

/*!
    \brief forward cursor

    forward cursor

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::forwardCursor()
{
}

/*!
    \brief backward cursor n times

    backward cursor n times

    \param n times backward

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::backwardCursor(int n)
{
}

/*!
    \brief backward cursor

    backward cursor

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::backwardCursor()
{
}


/*!
    \brief go to the next line

    go to the next line

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::newLine()
{
}

/*!
    \brief scroll up

    scroll up

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::scrollUp()
{
}

/*!
    \brief put charcter

    put charcter at the position of current cursor

    \param ch charcter to put

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::putCharacter(char ch)
{
    char str[] = " ";
    str[0] = ch;
    print(str);
}

/*!
    \brief print string

    print string.
    string terminator is '\0'

    \param str string

    \author  Higepon
    \date    create:2004/03/05 update:
*/
void LogConsole::print(const char* str)
{
    while (*str)
    {
        com1_->writeChar(*str++);
    }
    return;
}

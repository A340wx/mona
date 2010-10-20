/*!
    \file  CommandHistory.h
    \brief 

    Copyright (c) 2006-2007 Higepon
    WITHOUT ANY WARRANTY

    \author  Higepon
    \version $Revision$
    \date   create:2007/07/14 update:$Date$
*/

#ifndef __COMMAND_HISTORY_H__
#define __COMMAND_HISTORY_H__

#include "util/String.h"

namespace monash {

class CommandHistory
{
public:
    CommandHistory() {}
    virtual ~CommandHistory() {}

    bool add(::util::String history)
    {
        if (history.size() == 0) return false;
        if (history.last() == '\n')
        {
            history.chop();
        }

        for (int i = 0; i < histories_.size(); i++) {
          if (*(histories_[i]) == history) {
            return false;
          }
        }
        histories_.add(new ::util::String(history));
        positionToNewest();
        return true;
    }

    ::util::String* getOlderHistory()
    {
        positionToOlder();
        return get();
    }

    ::util::String* getNewerHistory()
    {
        positionToNewer();
        return get();
    }

    ::util::String* findFirstMatch(::util::String text)
    {
        for (int i = 0; i < histories_.size(); i++) {
            if (strstr(histories_[i]->data(), text.data()) != NULL) {
                return histories_[i];
            }
        }
        return NULL;
    }

private:

    ::util::String* get()
    {
        if (position_ < 0 || position_ >= histories_.size()) return new ::util::String("");
        return histories_.get(position_);
    }

    void positionToNewest()
    {
        position_ = histories_.size();
    }

    void positionToOlder()
    {
        if (position_ < 0) return;
        position_--;
    }

    void positionToNewer()
    {
        if (position_ >= histories_.size()) return;
        position_++;
    }

private:
    ::util::Vector< ::util::String* > histories_;
    int position_;
};

}; // namespace monash

#endif // __COMMAND_HISTORY_H__

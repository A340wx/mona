/*!
    \file  UserSemaphore.h
    \brief UserSemaphore

    Copyright (c) 2007 Higepon
    WITHOUT ANY WARRANTY

    \author  Higepon
    \version $Revision: 3635 $
    \date   create:2007/09/27 update:$Date$
*/
#ifndef _MONA_USER_SEMAPHORE_
#define _MONA_USER_SEMAPHORE_

#include "KObject.h"
#include "Process.h"

class Thread;
class Process;
/*----------------------------------------------------------------------
    UserSemaphore
----------------------------------------------------------------------*/
class UserSemaphore : public KObject {

  public:
    UserSemaphore(int sem);
    virtual ~UserSemaphore();

  public:
    intptr_t down(Thread* thread);
    intptr_t tryDown();
    intptr_t up();
//     void addRef();
//     void releaseRef();

    inline bool canDown() const {
        return sem_ > 0;
    }

    inline intptr_t getType() const
    {
        return USER_SEMAPHORE;
    }

  private:
    int refcount_;
    int sem_;
    int maxSem_;
    List<Thread*>* waitList_;
    Process* process_;
};

#endif

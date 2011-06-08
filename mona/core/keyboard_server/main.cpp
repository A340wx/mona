/*!
  \file  KeyBoardServer
  \brief class KeyBoard information

  Copyright (c) 2004 Higepon
  All rights reserved.
  License=MIT/X License

  \author  Higepon
  \version $Revision$
  \date   create:2004/01/25 update:$Date$
*/

#include <monapi.h>
#include <monapi/messages.h>
#include <monapi/io.h>
#include "KeyboardManager.h"

using namespace MonAPI;

int regist(List<uint32_t>* destList, MessageInfo* info);
int unregist(List<uint32_t>* destList, MessageInfo* info);
int sendKeyInformation(KeyBoardManager* manager, List<uint32_t>* destList, uint8_t scancode);


bool WaitInterruptWithTimeout(uint32_t ms, uint8_t irq, const char* file = "no file", int line = 0);


#define WAIT_INTERRUPT(ms, irq) WaitInterruptWithTimeout(ms, irq, __FILE__, __LINE__)

bool WaitInterruptWithTimeout(uint32_t ms, uint8_t irq, const char* file, int line)
{
    MessageInfo msg;

    uint32_t timerId = set_timer(ms);

    for (int i = 0; ; i++)
    {
        intptr_t result = Message::peek(&msg, i);

        if (result != M_OK)
        {
            i--;
            syscall_mthread_yield_message();
        }
        else if (msg.header == MSG_TIMER)
        {
            if (msg.arg1 != timerId) continue;
            kill_timer(timerId);

            if (Message::peek(&msg, i, PEEK_REMOVE) != M_OK) {
                _printf("peek error %s:%d\n", __FILE__, __LINE__);
            }

            _printf("interrupt timeout %s:%d\n", file, line);
            return false;
        }
        else if (msg.header == MSG_INTERRUPTED)
        {
            if (msg.arg1 != irq) continue;
            kill_timer(timerId);

            if (Message::peek(&msg, i, PEEK_REMOVE) != M_OK) {
                _printf("peek error %s:%d\n", __FILE__, __LINE__);
            }

            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    /* user mode I/O */
    syscall_get_io();

    const char* MAP_FILE_PATH = "/SERVERS/KEYBDMNG.map";
    uint32_t pid = syscall_get_pid();
    intptr_t ret = syscall_stack_trace_enable(pid, MAP_FILE_PATH);
    if (ret != M_OK) {
        monapi_warn("syscall_stack_trace_enable error %d\n", ret);
        exit(-1);
    }

    /* initilize KeyBoardManager */
    KeyBoardManager* manager = new KeyBoardManager();
    manager->init();

    /* initilize destination list */
    List<uint32_t>* destList = new HList<uint32_t>();
    MessageInfo info;

    if (monapi_notify_server_start("MONITOR.BIN") != M_OK)
    {
        exit(-1);
    }

    syscall_set_irq_receiver(1, 0);

    if (monapi_name_add("/servers/keyboard") != M_OK) {
        monapi_fatal("monapi_name_add failed");
    }

    /* Message loop */
    for (;;)
    {
        /* receive */
        if (!Message::receive(&info))
        {
            switch(info.header)
            {
            case MSG_INTERRUPTED:

                sendKeyInformation(manager, destList, inp8(0x60));
                break;

            case MSG_KEY_PRESS:
            {
                MessageInfo message;
                Message::create(&message, MSG_KEY_VIRTUAL_CODE, info.arg1, KEY_MODIFIER_DOWN, info.arg1, NULL);
                for (int i = destList->size() - 1; i >= 0; i--)
                {
                    if (Message::send(destList->get(i), &message) != M_OK)
                    {
                        monapi_warn("send error to pid = %x", destList->get(i));
                        uint32_t temp;
                        destList->removeAt(i, &temp);
                    }
                }
            }

            case MSG_ADD:

                regist(destList, &info);
                Message::reply(&info);
                break;

            case MSG_REMOVE:

                unregist(destList, &info);
                Message::reply(&info);
                break;

            default:
                /* igonore this message */

                break;
            }
        }
    }
    return 0;
}

int sendKeyInformation(KeyBoardManager* manager, List<uint32_t>* destList, uint8_t scancode)
{
    MessageInfo message;
    KeyInfo keyinfo;

    /* scan code to virtual key information */
    if(manager->setKeyScanCode(scancode) == 0) return 0;
    manager->getKeyInfo(&keyinfo);

    /* create message */
    memset(&message, 0, sizeof(MessageInfo));
    Message::create(&message, MSG_KEY_VIRTUAL_CODE, keyinfo.keycode, keyinfo.modifiers, keyinfo.charcode, NULL);

    /* send message */
    for (int i = destList->size() - 1; i >= 0; i--)
    {
        if (Message::send(destList->get(i), &message) != M_OK)
        {
            _printf("send error to pid = %x", destList->get(i));
            uint32_t temp;
            destList->removeAt(i, &temp);
        }
    }
    return 0;
}

int regist(List<uint32_t>* destList, MessageInfo* info)
{
    uint32_t id = info->arg1;
    destList->add(id);
    return 0;
}

int unregist(List<uint32_t>* destList, MessageInfo* info)
{
    uint32_t id = info->arg1;
    destList->remove(id);
    return 0;
}

/*!
    COPYRIGHT AND PERMISSION NOTICE

    Copyright (c) 2002,2003 Higepon
    Copyright (c) 2002,2003 Guripon
    Copyright (c) 2003      .mjt

    All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
    (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
    publish, distribute, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
    provided that the above copyright notice(s) and this permission notice appear in all copies of the Software and that both
    the above copyright notice(s) and this permission notice appear in supporting documentation.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS
    NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
    WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

    Except as contained in this notice, the name of a copyright holder shall not be used in advertising or otherwise to promote the sale,
    use or other dealings in this Software without prior written authorization of the copyright holder.
*/

/*!
    \file   kernel.cpp
    \brief  mona kernel start at this point

    mona kernel start at this point.
    before startKernel, os entered protected mode.

    Copyright (c) 2002,2003 Higepon
    All rights reserved.
    License=MIT/X Licnese

    \author  HigePon
    \version $Revision$
    \date   create:2002/07/21 update:$Date$
*/

#define GLOBAL_VALUE_DEFINED

#include <types.h>
#include <global.h>
#include <kernel.h>
#include <operator.h>
#include <tester.h>
#include <checker.h>
#include <KeyBoardManager.h>
#include <SystemInfo.h>
#include <FDCDriver.h>
#include <GraphicalConsole.h>
#include <ihandlers.h>
#include <pic.h>
#include <rtc.h>
#include <disp.h>
#include <BitMap.h>
#include <FAT12.h>
#include <string.h>
#include <syscalls.h>
#include <ProcessManager.h>
#include <syscalls.h>
#include <userlib.h>
#include <PageManager.h>
#include <elf.h>
#include <MemoryManager.h>

char* version = "Mona version.0.1.3 $Date$";
void userTest();
void userTest2();
void v86Test();
void mainProcess();

/*!
    \brief  mona kernel start at this point

    cstart call this function.
    actually, kernel starts at this point

    \author HigePon
    \date   create:2002/07/21 update:2003/06/08
*/
void startKernel(void) {

    /* kernel memory range */
    km.initialize(0x200000, 0xAfffff);

    /* set segment */
    GDTUtil::setup();

    /* Process setup */
    Process::setup();

    /* initialze console */
    g_console = new GraphicalConsole();

    /* for Shared Memory */
    SharedMemoryObject::setup();

    /* show start message */
    //    printBanner();

    pic_init();

    printOK("Setting PIC        ");

    IDTUtil::setup();

    printOK("Setting IDT        ");
    printOK("Setting GDT        ");

    checkTypeSize();
    printOK("Checking type size ");

    /* get total system memory */
    g_total_system_memory = MemoryManager::getPhysicalMemorySize();
    g_console->printf("\nSystem TotalL Memory %d[MB]. Paging on\n", g_total_system_memory / 1024 / 1024); //

    /* paging start */
    g_page_manager = new PageManager(g_total_system_memory);
    g_page_manager->setup();

    /* this is test code 2003/12/14 */
    ThreadManager::createIdle((dword)idle_process, g_page_manager->createNewPageDirectory());
    g_processManager = new ProcessManager_(g_page_manager);
    Process_* testProcess1 = g_processManager->create(ProcessManager_::KERNEL_PROCESS, "TEST1");
    g_processManager->add(testProcess1);
    Thread*   testThread1  = g_processManager->createThread(testProcess1, (dword)printBanner);
    g_console->printf("testThread1=%x", testThread1);
    g_processManager->join(testProcess1, testThread1);

    /* initilize keyboard */
    KeyBoardManager& km = KeyBoardManager::instance();
    km.init();

#ifdef HIGE

    disableTimer();
    enableKeyboard();
    enableInterrupt();

    //    keyStrokeTest();


    /* show Logo */
    //    mmChangeTester();
    //    while (true);
    //    FDCDriverTester();

    //    g_console->printf("Hit any key to start Main Process and Load ELF\n");
    //    while (g_demo_step < 2);
    //    g_console->printf("[2]");
    g_info_level = MSG;

    Process* idle     = new Process("idle         ");
    Process* mprocess = new Process("mainProc     ");
    g_process_manager = new ProcessManager(idle);

    g_process_manager->addProcess(mprocess, (virtual_addr)mainProcess);

    enableTimer();
#endif

    while (true);
}

void mainProcess() {

    /*
       User Process should be exec by LoadProcess()

       You can't exec User Process here.
    */

    //Process*     process2 = new Process("krnl_o       ");
    //Process*     process5 = new Process("krnl_o2      ");
    //Process*     process3 = new Process("krnl_n       ");
    //    Process*     process4 = new Process("krnl_m       ");
    Process*     process7 = new Process("show_process ");

    g_process_manager->addProcess(process7          , (virtual_addr)disp_process);
    //    g_process_manager->addProcess(process4          , (virtual_addr)disp_name1);

    //  g_process_manager->addProcess(process3          , (virtual_addr)disp_name3);
    //  g_process_manager->addProcess(process5          , (virtual_addr)disp_name4);
    //  g_process_manager->addProcess((Process*)process9, (virtual_addr)v86_func);

    g_console->printf("loadPloadProcess=%d", loadProcess(".", "USER.ELF", true));

    while (true);
}

void idle_process() {

    while (true) {

        /* do nothing */
    }
}

/*!
    \brief  mona kernel panic

    kernel panic

    \author HigePon
    \date   create:2002/12/02 update:2003/03/01
*/
void panic(const char* msg) {

    g_console->setCHColor(GP_RED);
    g_console->printf("kernel panic\nMessage:%s\n", msg);
    while (true) {
    }
}

void checkMemoryAllocate(void* p, const char* msg) {

    if (p != NULL) return;

    panic(msg);
}

/*!
    \brief print OK

    print "msg             [OK]"

    \param msg message
    \author HigePon
    \date   create:2003/01/26 update:2003/01/25
*/
inline void printOK(const char* msg) {

    static int i = 0;

    if (i % 2) g_console->printf("   ");

    g_console->printf((char*)msg);
    g_console->printf("[");
    g_console->setCHColor(GP_LIGHTBLUE);
    g_console->printf("OK");
    g_console->setCHColor(GP_WHITE);
    g_console->printf("]");

    if (i % 2) g_console->printf("\n");
    i++;
}

/*!
    \brief print Banner

    print Banner

    \author HigePon
    \date   create:2003/01/26 update:2003/01/25
*/
inline void printBanner() {

    g_console->printf("------------------------------------------------------\n");
    g_console->printf("   Thanks for choosing MONA!                          \n");
    g_console->printf("            /\x18__/\x18                                    \n");
    g_console->printf("           ( ;'[]`)  < ���܎܎܎���!!                       \n");
    g_console->printf("           (      )                                   \n");
    g_console->printf("------------------------------------------------------\n");
    g_console->printf("%s\n\n", version);
    g_console->setCHColor(GP_WHITE);
}

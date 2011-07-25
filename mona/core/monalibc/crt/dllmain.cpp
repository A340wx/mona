#include <monapi.h>

extern "C" void init_stdio(void);

extern "C" int dllmain(uint32_t reason);
extern "C" __attribute__((constructor)) void monalibc_initialize();
extern "C" __attribute__((destructor)) void monalibc_finalize();
extern "C" FuncVoid* __CTOR_LIST__[];
extern "C" FuncVoid* __DTOR_LIST__[];

int dllmain(uint32_t reason)
{
    switch (reason)
    {
    case 0: // DLL_PROCESS_ATTACH
        invokeFuncList(__CTOR_LIST__, __FILE__, __LINE__);
        break;
    case 1: // DLL_PROCESS_DETACH
        invokeFuncList(__DTOR_LIST__, __FILE__, __LINE__);
        break;
    default:
        break;
    }
    return 1;
}

bool monalibc_initialized = false;
extern "C" void monapi_initialize_memory(int);

__attribute__((constructor)) void monalibc_initialize()
{
    if (monalibc_initialized) return;
    monalibc_initialized = true;
    monapi_initialize_memory(PROCESS_HEAP_SIZE);
    monapi_initialize();
// known bug.
#if 0
    uint32_t handle;
    handle = MonAPI::System::getProcessStdinID();
    _logprintf("%s:%d stdin handle=%x\n", __FILE__, __LINE__, handle);
    inStream = MonAPI::Stream::createFromHandle(handle);
    handle = MonAPI::System::getProcessStdoutID();
    _logprintf("%s:%d stdout handle=%x\n", __FILE__, __LINE__, handle);
    outStream = MonAPI::Stream::createFromHandle(handle);
#endif
    init_stdio();
}

__attribute__((destructor)) void monalibc_finalize()
{
}

// if __attribute__((constructor)) doesn't work, use this.
//static struct MonalibcInitWrapper {MonalibcInitWrapper(){monalibc_initialize();}} Monalibc_initializer;

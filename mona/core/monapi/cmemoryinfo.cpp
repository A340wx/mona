#include <sys/error.h>
#include <monapi/syscall.h>
#include <monapi/messages.h>
#include <monapi/cmemoryinfo.h>
#include <monapi/Message.h>
#include <monapi/MemoryMap.h>
#include <monapi.h>

#define ASSERT(cond) if (!cond) { printf("%s:%d: null pointer exception!\n", __FILE__, __LINE__); exit(1); }

using namespace MonAPI;

monapi_cmemoryinfo* monapi_cmemoryinfo_new()
{
    monapi_cmemoryinfo* self = (monapi_cmemoryinfo*)malloc(sizeof(monapi_cmemoryinfo));
    ASSERT(self);
    self->Handle = 0;
    self->Owner  = THREAD_UNKNOWN;
    self->Size   = 0;
    self->Data   = NULL;
    return self;
}

void monapi_cmemoryinfo_delete(monapi_cmemoryinfo* self)
{
    // monapi_cmemoryinfo_dispose(self);
    free(self);
}

intptr_t monapi_cmemoryinfo_create(monapi_cmemoryinfo* self, uint32_t size, int prompt, int isImmediateMap)
{
    self->Handle = monapi_cmemorymap_create(size);
    if (self->Handle == 0)
    {
        if (prompt) printf("ERROR\n");
        monapi_warn("%s:%d: MemoryMap create error\n", __FILE__, __LINE__);
        return M_MEMORY_MAP_ERROR;
    }
    if (monapi_cmemoryinfo_map(self, isImmediateMap) != M_OK)
    {
        if (prompt) printf("ERROR\n");
        monapi_warn("%s:%d: MemoryMap map error\n", __FILE__, __LINE__);
        return M_MEMORY_MAP_ERROR;
    }

    self->Size  = size;
    self->Owner = syscall_get_tid();
    return M_OK;
}

intptr_t monapi_cmemoryinfo_map(monapi_cmemoryinfo* self, int isImmediateMap)
{
    self->Data = monapi_cmemorymap_map(self->Handle, isImmediateMap);
    if (self->Data != NULL) {
        return M_OK;
    }

    monapi_warn("map error self->Handle=%x, %s:%d:(%s)\n", self->Handle, __FILE__, __LINE__, __func__);
    if (monapi_cmemorymap_unmap(self->Handle) != M_OK) {
        monapi_warn("unmap failed on monapi_cmemoryinfo_map\n");
    }
    self->Handle = 0;
    self->Size   = 0;
    return M_MEMORY_MAP_ERROR;
}

void monapi_cmemoryinfo_dispose(monapi_cmemoryinfo* self)
{
    if (monapi_cmemorymap_unmap(self->Handle) != M_OK) {
        monapi_warn("unmap failed on monapi_cmemoryinfo_dispose\n");
    }
    if (self->Owner != syscall_get_tid())
    {
        if (Message::send(self->Owner, MSG_DISPOSE_HANDLE, self->Handle) != M_OK) {
            printf("Error %s:%d\n", __FILE__, __LINE__);
            exit(-1);
        }
    }
    self->Handle = 0;
}

intptr_t monapi_cmemoryinfo_dispose_no_notify(monapi_cmemoryinfo* self)
{
    if (monapi_cmemorymap_unmap(self->Handle) != M_OK) {
        return M_BAD_MEMORY_MAP_ID;
    }
    self->Handle = 0;
    return M_OK;
}

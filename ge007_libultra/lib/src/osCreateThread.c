#include "libultra_internal.h"
extern OSThread* D_8033489C;
void __osCleanupThread(void);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
void osCreateThread(OSThread *thread, OSId id, void (*entry)(void *),
                    void *arg, void *sp, OSPri pri)
{
    register u32 int_disabled;
    u32 tmp;
    thread->id = id;
    thread->priority = pri;
    thread->next = NULL;
    thread->queue = NULL;
    thread->context.pc = (u32)entry;
    thread->context.a0 = arg;
    thread->context.sp = ((u64)sp) - 16;
    thread->context.ra = __osCleanupThread;
    tmp = 0x003FFF01;
    thread->context.sr = 65283;
    thread->context.rcp = (tmp & 0x3f0000) >> 16;
    thread->context.fpcsr = (u32)0x01000800;
    thread->fp = 0;
    thread->state = OS_STATE_STOPPED;
    thread->flags = 0;
    int_disabled = __osDisableInt();
    thread->tlnext = D_8033489C;

    D_8033489C = thread;
    __osRestoreInt(int_disabled);
}
#pragma GCC diagnostic pop

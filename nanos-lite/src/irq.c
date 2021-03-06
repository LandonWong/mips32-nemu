#include "common.h"
#include "am.h" 
extern _Context* do_syscall(_Context *c);
extern _Context* schedule(_Context *prev);
static _Context* do_event(_Event e, _Context* c) {
  _Context* ret = NULL;
  switch (e.event) {
    case _EVENT_IRQ_TIMER: _yield();ret=c;break;
    case _EVENT_TLBL: __am_tlb_refill();ret=c;break;//printf("TLB REFILL: cpu.epc %x\n",c->epc);break;
    case _EVENT_SYSCALL: ret = do_syscall(c);break;//printf("syscall finished and cpu.epc is %x\n",ret->epc);break;
    case _EVENT_YIELD: ret = schedule(c);__am_tlb_clear();break;//printf("schedule before %x after %x and cpu.epc %x\n",c,ret,ret->epc);break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return ret;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  _cte_init(do_event);
}

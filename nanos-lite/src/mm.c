#include "memory.h"
#include "proc.h"

static void *pf = NULL;

void* new_page(size_t nr_page) {
  void *p = pf;
  pf += PGSIZE * nr_page;
  // printf("pf now is %x\n",pf);//debug
  assert(pf < (void *)_heap.end);
  return p;
}

void free_page(void *p) {
  panic("not implement yet");
}

extern PCB *current ;
/* The brk() system call handler. */
int mm_brk(uintptr_t brk) {
  if(brk<=current->max_brk) return 0;
  void* va = (void*)PGROUNDUP(current->max_brk);
  while(va<(void*)brk){
    void* pa = new_page(1);
    _map(&current->as,va,pa,0);
    va+=PGSIZE;
  }
  current->max_brk = brk;
  return 0;
}

void init_mm() {
  pf = (void *)PGROUNDUP((uintptr_t)_heap.start);
  Log("free physical pages starting from %p", pf);

  _vme_init(new_page, free_page);
}

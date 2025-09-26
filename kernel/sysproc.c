#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(n < 0) {
    if(shrinkproc(-n) < 0)
      return -1;
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_getppid(void)
{
  return myproc()->parent->pid;
}

uint64
sys_getancestor(void)
{
  int generation;
  
  // Obtener el parámetro (número de generaciones)
  argint(0, &generation);
    
  // Validar que sea un número no negativo
  if(generation < 0)
    return -1;
    
  struct proc *current = myproc();
  
  // Si generation es 0, retorna el mismo proceso
  if(generation == 0)
    return current->pid;
    
  // Recorrer hacia arriba en la jerarquía de procesos
  for(int i = 0; i < generation; i++) {
    if(current->parent == 0) {
      // No hay más ancestros
      return -1;
    }
    current = current->parent;
  }
  
  return current->pid;
}

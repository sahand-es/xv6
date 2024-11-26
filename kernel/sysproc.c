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
  if(growproc(n) < 0)
    return -1;
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


uint64 sys_sysinfo(void) 
{
  struct sysinfo_data *out;
  struct sysinfo_data result;
  // struct proc *p;

  argaddr(0, (uint64*)&out);
  result.running_processes = active_proc_count();
  result.free_memory = get_free_mem();

  return copyout(myproc()->pagetable, (uint64)out, (char*)&result, sizeof(result));
}

uint64 sys_next_process(void)
{
  int before_pid;
  struct process_data temp;
  struct process_data *proc_data;

  argint(0, &before_pid);
  argaddr(1, (uint64*)&proc_data);

  int result = next_process(before_pid, &temp);
  if (result > 0) {
    int copy_result = copyout(myproc()->pagetable, (uint64)proc_data, (char*)&temp, sizeof(temp));
    if (copy_result < 0) {
      return 0;
    }
    return 1;
  }
  return 0;
}

uint64 sys_nice(void)
{
  int inc;
  argint(0, &inc);
  return nice(inc);
}

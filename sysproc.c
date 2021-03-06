#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
	return fork();
}

int sys_exit(void)
{
	exit();
	return 0; // not reached
}

int sys_wait(void)
{
	return wait();
}

int sys_kill(void)
{
	int pid;

	if (argint(0, &pid) < 0)
		return -1;
	return kill(pid);
}

int sys_getpid(void)
{
	return proc->pid;
}

int sys_sbrk(void)
{
	int addr;
	int n;

	if (argint(0, &n) < 0)
		return -1;
	addr = proc->sz;
	if (growproc(n) < 0)
		return -1;
	return addr;
}

int sys_sleep(void)
{
	int n;
	uint ticks0;

	if (argint(0, &n) < 0)
		return -1;
	acquire(&tickslock);
	ticks0 = ticks;
	while (ticks - ticks0 < n)
	{
		if (proc->killed)
		{
			release(&tickslock);
			return -1;
		}
		sleep(&ticks, &tickslock);
	}
	release(&tickslock);
	return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
	uint xticks;

	acquire(&tickslock);
	xticks = ticks;
	release(&tickslock);
	return xticks;
}

int sys_shutdown(void)
{
	outw(0xB004, 0x0 | 0x2000);
	return 0;
}

int sys_forkwinner(void)
{
	int b;
	argint(0, &b);
	// cprintf("for test: %d %d\n",(int)(cpu->id),b);
	useCustomScheduleAlgorithm = b;
	return 0;
}

int sys_alloc_sem(void)
{
	int v;
	if (argint(0, &v) < 0)
		return -1;
	return alloc_sem(v);
}

int sys_wait_sem(void)
{
	int i;
	if (argint(0, &i) < 0)
		return -1;
	if (i >= 100 || i < 0)
		return -1;	
	return wait_sem(i);
}

int sys_signal_sem(void)
{
	int i;
	if (argint(0, &i) < 0)
		return -1;
	if (i >= 100 || i < 0)
		return -1;
	return signal_sem(i);
}

int sys_dealloc_sem(void)
{
	int i;
	if (argint(0, &i) < 0)
		return -1;
	if (i >= 100 || i < 0)
		return -1;
	return dealloc_sem(i);
}

int sys_enable_schedule_display(void)
{
	int e;
	if(argint(0,&e)<0)
		return -1;
	display_enabled = e;
	return 0;
}

int sys_set_priority(void)
{
	int pid,prior;
	if(argint(0,&pid)<0)
		return -1;
	if(argint(1,&prior)<0)
		return -1;
	return set_priority(pid,prior);
}
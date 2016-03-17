#include "types.h"
#include "user.h"
#include "traps.h"
#include "syscall.h"
#include "x86.h"
int main()
{
	asm volatile("movl %0, %%eax"
				:
				:"i"(SYS_shutdown)
				:);
	asm volatile("int %0"
				:
				:"i"(T_SYSCALL)
				:);
	exit();
}
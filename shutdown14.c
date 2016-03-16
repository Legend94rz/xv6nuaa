#include "types.h"
#include "user.h"
#include "traps.h"
#include "syscall.h"

int main()
{
	asm volatile("movl %0, %%eax"
				:
				:""(SYS_shutdown)
				:);
	asm volatile("int %0"
				:
				:""(T_SYSCALL)
				:);
	exit();
}
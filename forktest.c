#include "types.h"
#include "user.h"
#include "syscall.h"
#include "traps.h"

#define TOTAL_TEST_TRIALS 50

void fork_winner(int b)
{
	asm volatile("pushl %0"::"g"(b));
	asm volatile("pushl %0"::"g"(0));					//If don't add this instruction, the parameter sys_forkwinner gets is not correct. WHY???
	asm volatile("movl %0, %%eax"::"i"(SYS_forkwinner));
	asm volatile("int %0"::"i"(T_SYSCALL));
	asm volatile("addl $8,%esp");						//If we don't balance the stack, it will not jump out of the sys_forkwinner(), WHY???
}

int main(int argc, char *argv[])
{
	int i = 0;
	int w = 0;
	int ret = 0;

	if (argc < 2)
	{
		printf(1, "Usage: forktest 0|1 \n"
				  "\t0: Parent is scheduled to run most often\n"
				  "\t1: Child is scheduled to run most often\n");
		exit();
	}

	if (argv[1][0] == '0')
	{
		w = 0;
		printf(1, "\nSetting parent as the fork winner ...\n");
	}
	else
	{
		w = 1;
		printf(1, "\nSetting child as the fork winner ...\n");
	}

	fork_winner(w); // set according to user input

	printf(1, "\n NUAA OS proj1 fork test ==> \n");

	for (i = 0; i < TOTAL_TEST_TRIALS; i++)
	{
		printf(1, "\nTrial %d: ", i);
		ret = fork();
		if (ret < 0)
		{
			printf(1, "fork() failed (%d)\n", ret);
			exit();
		}
		else if (ret == 0) // child
		{
			printf(1, " child! ");
			exit();
		}

		// parent
		printf(1, " parent! ");
		if (ret != wait())
		{
			printf(1, "wait() failed!\n");
		}
	}

	printf(1, "\n");

	fork_winner(0); // set back to default

	exit();
}

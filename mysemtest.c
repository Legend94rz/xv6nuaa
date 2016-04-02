#include "types.h"
#include "stat.h"
#include "user.h"
int mutex;
int full;
int empty;
int count = 0;

extern int alloc_sem(int);
extern int wait_sem(int);
extern int signal_sem(int);

int main(int argc, char *argv[])
{
	mutex = alloc_sem(1);
	empty = alloc_sem(10);
	full = alloc_sem(0);
	if (fork() == 0)
	{ // consumer
		int M = 10;
		while (M--)
		{
			wait_sem(full);
			wait_sem(mutex);
			count--;
			printf(1, "consumed: -1\n");
			signal_sem(mutex);
			signal_sem(empty);
		}
		exit();
	}
	// producer
	int N = 10;
	while (N--)
	{
		wait_sem(empty);
		wait_sem(mutex);
		count++;
		printf(1, "produced: 1\n");
		signal_sem(mutex);
		signal_sem(full);
	}
	wait();
	exit();
}
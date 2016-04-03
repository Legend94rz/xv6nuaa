#include "types.h"
#include "stat.h"
#include "user.h"
extern int alloc_sem(int);
extern int wait_sem(int);
extern int signal_sem(int);
extern int dealloc_sem(int);
extern int set_priority(int, int);
extern int enable_schedule_display(int);
int sem;
void compute()
{
	int i, j, s = 0;
	for (j = 0; j < 3000; j++)
	{
		for (i = 0; i < 2000; i++)
		{
			s = (s * i) % 100000;
		}
	}
}
int main(int argc, char *argv[])
{
	printf(1, "========Parent Pid: %d==========\n", getpid());
	set_priority(getpid(), 1);sem = alloc_sem(0);
	int i;
	for (i = 2; i < 8; i++)
	{
		if (fork() == 0)
		{
			set_priority(getpid(), i / 2);
			printf(1, "Parent: child (pid: %d, prior: %d) created!\n", getpid(), i / 2);
			wait_sem(sem);
			compute();
			exit();
		}
	}
	sleep(10);
	printf(1, "==================\n");
	for (i = 0; i < 6; i++)signal_sem(sem);
	enable_schedule_display(1);
	for(i=0;i<6;i++)wait();
	enable_schedule_display(0);
	printf(1,"\n");
	return 0;
}
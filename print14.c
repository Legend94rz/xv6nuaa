#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
	int i;
	printf(1,"OS Lab 161330214:");
	for (i = 1; i < argc; i++)
		printf(1, " %s", argv[i]);
	printf(1,"\n");
	exit();
}

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int i;

	for(i = 0; i < 7; i++)
	{
		printf("P1 rodando %d\n", i);
		fflush(stdout);
		sleep(1);
	}

}
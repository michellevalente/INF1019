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
	for(int i = 0; i < 12; i++)
	{
		printf("P3 rodando %d\n", i);
		fflush(stdout);
		if(i == 2)
		{
			kill(getppid(), SIGILL);

		}
		sleep(1);
	}
}
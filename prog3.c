#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

void sighandler(int signum)
{
	return;
}
int main()
{
	int i;
	for(int i = 0; i < 10; i++)
	{
		printf("P3 rodando %d\n", i);
		signal(SIGILL, sighandler);
		signal(SIGALRM, sighandler);
		if(i == 2)
		{
			kill(getppid(), SIGILL);

		}

		sleep(1);
	}
}
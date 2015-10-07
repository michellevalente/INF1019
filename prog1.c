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
	//signal(SIGINT, intHandler);
	for(i = 0; i < 10; i++)
	{
		printf("P1 rodando\n");
		sleep(1);
	}

}
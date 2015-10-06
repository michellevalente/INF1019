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
	int 	i = 0;
	while(1)
	{
		printf("P2 rodando\n");
		sleep(1);
		i++;
		if(i == 5)
			return 1;
	}
}
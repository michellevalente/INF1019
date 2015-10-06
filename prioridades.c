#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_PROG 10 
#define INF 1000000

int menor_prioridade(int prioridades[MAX_PROG], int n)
{
	int min, index, i;
	min = prioridades[0];
	index  = 0;
	for(i = 1 ; i < n; i++)
	{
		if(prioridades[i] < min)
		{
			min = prioridades[i];
			index = i;
		}
	}

	return index;
}

void prioridades(char * programas[MAX_PROG], int prioridades[MAX_PROG], int n)
{
	int i, pid[MAX_PROG], n_pid, j, min;
	int finished[MAX_PROG];
	char * programas_ordenados[MAX_PROG];
	char aux[20];
	int result, status;

	for(i = 0; i < n; i++)
		finished[i] = 0;

	for(i = 0; i < n; i++)
	{
		n_pid = fork();
		if(n_pid != 0)
		{
			pid[i] = n_pid;
			kill(n_pid, SIGSTOP);
		}
		else
		{
			sleep(1);
			execve(programas[i],NULL,NULL) ;
		}
	}	

	while(1)
	{
		i = menor_prioridade(prioridades, n);

		if(i == INF)
			return;

		if(finished[i] == 0)
		{
			kill(pid[i], SIGCONT);
			result = waitpid(pid[i], &status, WNOHANG);
				
			if (result == 0) 
			{
			  continue;
			} 
			else 
			{
			  finished[i] =1;
			  prioridades[i] = INF;
			}
		}
	}
}


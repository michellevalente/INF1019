#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#define MAX_PROG 10 
#define INF 1000000

int seg1 , seg2;
int * prioridades_prontos;
int index_prog_atual;
int prog_io[MAX_PROG];
int pid_atual;

void intHandler(int dummy) {
    printf("Limpando memoria compartilhada! \n");
    shmdt (prioridades_prontos);

	shmctl (seg1, IPC_RMID, 0);

	shmctl (seg2, IPC_RMID, 0);
	exit(0);

}

void handle_io(int dummy)
{
	printf("I/O recebido!\n");
	prog_io[index_prog_atual] = 1;
	kill(pid_atual, SIGCONT);
	sleep(4);
	prog_io[index_prog_atual] = 0;
	exit(0);
}

void round_robin(char * programas[MAX_PROG], int n)
{
	int i, pid[MAX_PROG], n_pid;
	int finished[MAX_PROG];
	int result, status;
	signal(SIGINT, intHandler);
	
	for(i = 0; i < n; i++){
		finished[i] = 0;
		prog_io[i] = 0;
	}

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

	i = 0;
	n_pid = fork();

	if(n_pid == 0)
	{
		while(1)
		{
			signal(SIGILL, handle_io);

		}
			
	}
	else
	{
		while(1)
		{
			if(finished[i] == 0 && prog_io[i] == 0)
			{
				kill(pid[i], SIGCONT);
				pid_atual = pid[i];
				index_prog_atual = i;
				sleep(5);
				result = waitpid(pid[i], &status, WNOHANG);
				if (result == 0) 
				{
				  kill(pid[i], SIGSTOP);
				} 
				else 
				{
				  finished[i] =1;
				}
			}
			i++;
			if(i == n)
				i = 0;

		}
	}
	
}

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
	signal(SIGINT, intHandler);
	char * programas_prontos[MAX_PROG];
	int index_prog_novo;
	char aux[20];
	int result, status;
	signal(SIGINT, intHandler);
	seg1 = shmget(IPC_PRIVATE, sizeof(int)*MAX_PROG, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	seg2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	if(seg1 < 0)
	{
		printf("Error!!\n");
	}
	prioridades_prontos = (int * )shmat (seg1, 0 , 0);
	index_prog_atual = (int )shmat (seg2, 0 , 0);


	for(i = 0; i < n; i++)
		finished[i] = 0;

	for(i = 0 ; i < MAX_PROG; i++)
	{
		programas_prontos[i] = (char *) malloc(sizeof(char) * 10);
		strcpy(programas_prontos[i], "");
		prioridades_prontos[i] = INF;
	}

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
	n_pid = fork();

	if(n_pid == 0)
	{
		for(i = 0 ; i < n; i++)
		{
			printf("Entrou na lista de pronto: %s com prioridade: %d\n", programas[i], prioridades[i]);
			strcpy(programas_prontos[i], programas[i]);
			prioridades_prontos[i] = prioridades[i];
			index_prog_novo = i;
			if(prioridades[index_prog_novo] < prioridades[index_prog_atual])
			{
				kill(pid[index_prog_atual], SIGSTOP);
			}
			sleep(4);
		}
		
	}
	else
	{
		while(1)
		{
			i = menor_prioridade(prioridades_prontos, n);
			//printf("%d %d %d\n", prioridades_prontos[0], prioridades_prontos[1], prioridades_prontos[2]);
			//scanf("%d", &min);
			if(i == INF)
				return;

			if(finished[i] == 0)
			{
				kill(pid[i], SIGCONT);
				//printf("PID1: %d\n", pid[i]);
				index_prog_atual = i;
				result = waitpid(pid[i], &status, WNOHANG);

				if (result == 0) 
				{
				 	kill(pid[index_prog_atual], SIGSTOP);
					continue;
				} 
				else 
				{
				  finished[i] =1;
				  prioridades_prontos[i] = INF;
				}
			}
		}
	}

	
}


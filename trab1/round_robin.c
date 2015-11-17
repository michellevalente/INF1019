
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escalonadores.h"
#include <unistd.h>
#define MAX_PROG 10 

int main()
{
	FILE *arq, *arq2;
	char ex[5], prog[10], p[11];
	int pr, NumProg =0, i;
	char * programa[MAX_PROG];
	int prioridade[MAX_PROG];
	arq = fopen("entrada.txt", "r");
	arq2  = fopen("saida.txt", "w");
	printf("1: Stdout no terminal \n2: Stdout no arquivo saida.txt\n");
	scanf("%d", &i);
	if(i == 2)
	{
		printf("Stdout sendo gravado no arquivo, espere ate o termino do programa.\n");
		dup2(fileno(arq2), STDOUT_FILENO);
	}
	

	for(i = 0 ; i < MAX_PROG; i++)
	{
		programa[i] = (char *) malloc(sizeof(char) * 10);
	}
	while(fscanf(arq, "%s %s", ex, prog) != EOF)
	{

		strcpy(programa[NumProg], prog);
		NumProg++;

	}

	for(i = 0 ; i < NumProg; i++)
	{
		printf("Programa: %s\n", programa[i]);
		fflush(stdout);

	}
	
	round_robin(programa, NumProg);
	fclose(arq);
	fclose(arq2);
	return 0;
}
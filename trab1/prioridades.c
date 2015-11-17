
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "escalonadores.h"
#define MAX_PROG 10 
int main()
{
	FILE *arq, *arq2;
	char ex[5], prog[10], p[11];
	int pr, NumProg =0, i;
	char * programa[MAX_PROG];
	int prioridade[MAX_PROG];
	arq2  = fopen("saida.txt", "w");
	printf("1: Stdout no terminal \n2: Stdout no arquivo saida.txt\n");
	scanf("%d", &i);
	if(i == 2)
	{
		printf("Stdout sendo gravado no arquivo, espere ate o termino do programa.\n");
		dup2(fileno(arq2), STDOUT_FILENO);
	}
		
	arq = fopen("entrada.txt", "r");

	for(i = 0 ; i < MAX_PROG; i++)
	{
		programa[i] = (char *) malloc(sizeof(char) * 10);
	}
	while(fscanf(arq, "%s %s %s %d", ex, prog, p, &pr) != EOF)
	{
		strcpy(programa[NumProg], prog);
		prioridade[NumProg] = pr;
		NumProg++;

	}

	for(i = 0 ; i < NumProg; i++)
	{
		printf("Programa: %s, prioridade: %d\n", programa[i], prioridade[i]);

	}
	prioridades(programa, prioridade, NumProg);
	return 0;
}
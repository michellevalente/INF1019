
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escalonadores.h"
#define MAX_PROG 10 
int main()
{
	FILE *arq;
	char ex[5], prog[10], p[11];
	int pr, NumProg =0, i;
	char * programa[MAX_PROG];
	int prioridade[MAX_PROG];

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
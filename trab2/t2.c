#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define IO 0
#define EXEC 1
#define TAM_MEMORIA 5
#define MAX_PROC 100

int alocacao = 0;
int ultima_alocacao = 0;
int memoria[] ={8, 4, 2,1,1}; 
int MemoriaAux[] ={0,0,0,0,0};
int num;
int alocados[MAX_PROC];
int prontos_esperando[MAX_PROC];
int bloqueados[MAX_PROC];
int finalizados[MAX_PROC];

struct processo{
	int num;
	int tam;
	int info;
	int atual;
	int particao;
	int ex[][2];
} typedef Proc;

int BestFit(Proc * p, int index)
{
	int i;
	int melhor = -1;
	int menor_diferenca=1000000;

	for (i = 0; i < TAM_MEMORIA; i++) {         
        if (memoria[i] >= p->tam && MemoriaAux[i] == 0) {
            if(memoria[i] - p->tam < menor_diferenca)
            {
            	melhor = i;
            	menor_diferenca = memoria[i] - p->tam;
            }
        }                       
    }
    if(melhor != -1)
    {
    	alocados[index] = 1;
    	MemoriaAux[melhor] = index + 1;
    	p->particao = melhor;
    	return 1;
    }
    else
    {
    	prontos_esperando[index] = 1; 
    	p->particao = -1;
    	return 0;
    }
	

}

int NextFit(Proc * p, int index)
{  
    int i;

	for (i = ultima_alocacao; i < TAM_MEMORIA; i++) {         
        if (memoria[i] >= p->tam && MemoriaAux[i] == 0) {
            alocados[index] = 1;
	    	MemoriaAux[i] = index + 1;
	    	p->particao = i;
	    	ultima_alocacao = i;
	    	return 1;
        }                       
    }
    for(i = 0; i < ultima_alocacao; i++)
    {
    	if (memoria[i] >= p->tam && MemoriaAux[i] == 0) {
            alocados[index] = 1;
	    	MemoriaAux[i] = index + 1;
	    	p->particao = i;
	    	ultima_alocacao = i;
	    	return 1;
        }
    }
	prontos_esperando[index] = 1; 
	p->particao = -1;
	return 0;
}

int FirstFit(Proc * p, int index)
{  
    int i;

	for (i = 0; i < TAM_MEMORIA; i++) {         
        if (memoria[i] >= p->tam && MemoriaAux[i] == 0) {
            alocados[index] = 1;
	    	MemoriaAux[i] = index + 1;
	    	p->particao = i;
	    	return 1;
        }                       
    }
	prontos_esperando[index] = 1; 
	p->particao = -1;
	return 0;
}

int WorstFit(Proc * p, int index)
{  
    int i;
	int pior = -1;
	int maior_tamanho=0;

	for (i = 0; i < TAM_MEMORIA; i++) {         
        if (memoria[i] >= p->tam && MemoriaAux[i] == 0) {
            if(memoria[i] > maior_tamanho)
            {
            	pior = i;
            	maior_tamanho = memoria[i];
            }
        }                       
    }
    if(pior != -1)
    {
    	alocados[index] = 1;
    	MemoriaAux[pior] = index + 1;
    	p->particao = pior;
    	return 1;
    }
    else
    {
    	prontos_esperando[index] = 1; 
    	p->particao = -1;
    	return 0;
    }
}

void print_processos(Proc ** p)
{
	int i;
	for(i = 0; i < num ; i++)
	{
		printf("Num: %d\n Tam: %d\n", p[i]->num, p[i]->tam);
	}

}

void print_memoria(int relogio)
{
	int i;
	if(relogio % 10 == 0 || relogio == 0)
	{
		printf("\nMemoria: \n");
		for(i = 0 ; i < TAM_MEMORIA;i++)
		{
			if(MemoriaAux[i] != 0)
				printf("Particao %d (%d MB): Processo %d\n", i + 1, memoria[i], MemoriaAux[i]);
			else
				printf("Particao %d (%d MB): Vazia\n", i + 1, memoria[i]);
		}

		printf("\n");
	}
}
int swap_proc(Proc ** p, int i)
{
	int swap = 0;
	int k, temp;

	alocados[i] = 0;
	temp = MemoriaAux[p[i]->particao];
	MemoriaAux[p[i]->particao] = 0;
	for(k = 0; k < num; k++)
	{
		if(k != i && prontos_esperando[k])
		{
			if(alocacao == 0)
			{
				if(FirstFit(p[k], k))	
				{
					swap = 1;
					p[i]->particao = -1;
					prontos_esperando[k] = 0;
					printf("Processo %d retirado da memoria\n", i + 1);
					printf("Processo %d inserido na memoria\n", k + 1);
					return 1;
				}
			}
			if(alocacao == 1)
			{
				if(NextFit(p[k], k))	
				{
					swap = 1;
					p[i]->particao = -1;
					prontos_esperando[k] = 0;
					printf("Processo %d retirado da memoria\n", i + 1);
					printf("Processo %d inserido na memoria\n", k + 1);
					return 1;
				}
			}
			else if(alocacao == 2)
			{
				if(BestFit(p[k], k))	
				{
					swap = 1;
					p[i]->particao = -1;
					prontos_esperando[k] = 0;
					printf("Processo %d retirado da memoria\n", i + 1);
					printf("Processo %d inserido na memoria\n", k + 1);
					return 1;
				}
			}
			else if(alocacao == 3)
			{
				if(WorstFit(p[k], k))	
				{
					swap = 1;
					p[i]->particao = -1;
					prontos_esperando[k] = 0;
					printf("Processo %d retirado da memoria\n", i + 1);
					printf("Processo %d inserido na memoria\n", k + 1);
					return 1;
				}
			}
				
		}
	}
	if(swap == 0)
	{
		alocados[i] = 1;
		MemoriaAux[p[i]->particao] = temp;
		return 0;
	}

	return 1;
}

void io(Proc ** p)
{
	int i;
	for(i = 0; i < num; i++)
	{
		if(bloqueados[i] != 0)
		{
			bloqueados[i]--;
			if(bloqueados[i] == 0)
			{
				p[i]->atual++;
				if(p[i]->atual == p[i]->info)
				{
					finalizados[i] = 1;
					prontos_esperando[i] = 0;
					printf("Processo %d finalizado\n", i + 1);
					swap_proc(p,i);
				}
				else if(!alocados[i])
				{
					prontos_esperando[i] = 1;
				}
			}
		}

	}
}
int terminou()
{
	int i;
	for(i = 0; i < num; i++)
	{
		if(!finalizados[i])
			return 0;
	}

	return 1;
}
int main(int argc, char ** argv)
{
	FILE *arq;
	int i, info,j, k, tam, tp, swap, atual, todos_io, temp;
	int tempo, max;
	char c;
	char t[100], tipo[50];

	if(argc != 2)
	{
		printf("Entrar com arquivo de entrada.\n");
	}

	arq = fopen(argv[1], "r");
	if(arq == NULL)
	{
		printf("Erro ao abrir o arquivo de entrada\n");
	}
	printf("Escolha o tipo de alocacao de memoria: \n0 - first fit, 1- next fit, 2 - best fit , 3 - worst fit\n");
	scanf("%d", &alocacao);

	fscanf(arq, "%d", &num);
	Proc * processos[num];

	for(i = 0; i < num ; i++)
	{
		alocados[i] = 0;
		finalizados[i] = 0;
		prontos_esperando[i] = 0;
		bloqueados[i] = 0;
		MemoriaAux[i] = 0;
	}

	printf("PROCESSOS:\n");
	for(i = 0; i < num; i++)
	{

		fscanf(arq, "%s %s %s %s", t,t,t,t);
		tam = atoi(&t[0]);
		fscanf(arq, "%d", &info);
		printf("Processo #%d - %dMB\n", i + 1, tam);
		Proc * p = (Proc *)malloc(sizeof(*p) + info * sizeof(*p->ex)) ;
		p->num = i + 1;
		if(tam < 2)
			tam = 1;
		else if(tam > 2 && tam <= 4)
			tam = 4;
		else if(tam > 4 && tam < 8)
			tam = 8;

		p->tam = tam;
		p->info = info;

		for(j = 0; j < info; j++)
		{
			fscanf(arq, "%s %d", tipo, &tempo);
			if(strcmp(tipo, "io"))
			{
				printf("Exec %d\n", tempo);
				tp = EXEC;
			}
			else
			{
				printf("IO %d\n", tempo);
				tp = IO;
			}

			p->ex[j][0] = tp;
			p->ex[j][1] = tempo;
			
		}
		p->atual = 0;
		processos[i] = p;
		printf("\n");

	}
	sleep(1);
	for(i= 0; i < num; i++)		
	{
		if(alocacao == 0)
			FirstFit(processos[i], i);
		if(alocacao == 1)
			NextFit(processos[i], i);
		else if(alocacao == 2)
			BestFit(processos[i], i);
		else if(alocacao == 3)
			WorstFit(processos[i], i);
	}

	int relogio = 0;

	//print_memoria(relogio);

	while(1)
	{
		if(terminou())
			break;
		todos_io = 1;
		for(i = 0 ; i < num; i++)
		{
			
			if(alocados[i] && !bloqueados[i] && !finalizados[i])
			{ 
				todos_io = 0;
				info = processos[i]->info;
			
				for(j = processos[i]->atual; j < processos[i]->info; j++)
				{
					if(processos[i]->ex[processos[i]->atual][0] == EXEC)
					{
						printf("No CPU: processo %d em exec faltando %d\n", i + 1,processos[i]->ex[processos[i]->atual][1]);
				
						if(processos[i]->ex[processos[i]->atual][1] > 10)
							max = 10;
						else
							max = processos[i]->ex[processos[i]->atual][1];
						for(k = 0; k < max; k++)
						{
							processos[i]->ex[processos[i]->atual][1]--;
							print_memoria(relogio);
							relogio++;
							io(processos);
							if(relogio % 5 == 0)
								sleep(1);
						}
						if(processos[i]->ex[processos[i]->atual][1] == 0)
						{
							processos[i]->atual++;
						}
						else
						{
							// if(swap_proc(processos,i))
							// {
							// 	prontos_esperando[i] = 1;
							// }
							break;
						}

						if(processos[i]->atual >= processos[i]->info)
						{
							finalizados[i] = 1;
							prontos_esperando[i] = 0;
							printf("Processo %d finalizado\n", i + 1);
							swap_proc(processos,i);
						}

					}
					else
					{
						printf("Processo %d em I/O por %d\n", i + 1, processos[i]->ex[processos[i]->atual][1]);

						bloqueados[i] = processos[i]->ex[j][1];
						swap_proc(processos,i);
		
						break;
					}
				}

				
				
			}
		}
		if(todos_io)
		{
			for(j = 0; j < num ;j++ )
			{
				if(alocados[j])
					swap_proc(processos, j);
			}
			print_memoria(relogio);
			relogio++;
			io(processos);
			if(relogio % 5 == 0)
				sleep(1);
		}
	}	
	printf("Tempo total: %d\n", relogio);
	return 0;
}
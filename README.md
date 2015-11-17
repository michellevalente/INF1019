Trabalho 1

O primeiro trabalho consiste em programar em linguagem C programas que implementem um
interpretador de comandos e um escalonador de programas. O interpretador deverá solicitar ao
escalonador a execução de programas. O escalonador por sua vez dispara a execução dos
programas de acordo com uma determinada política de escalonamento, que deve ser:

LISTA DE PRIORIDADES (neste caso o interpretador deve indicar ao escalonador uma
prioridade de execução que é um número de 1 a 7 sendo 1 a maior prioridade e 7 a
menor) .
ROUND-ROBIN.

O escalonador deve ter estruturas de dados capazes de possibilitar a execução destas políticas.
Assim, de fato, será necessário implementar dois escalonadores, cada um implementando uma
política.
A comunicação entre os processos é feita da seguinte forma:
Interpretador de comandos -> Escalonador -> Sistema Operacional
O Sistema Operacional tem um escalonador próprio mas o escalonador do trabalho é quem vai
coordenar a execução dos processos indicados pelo usuário no interpretador de comandos. Ou
seja, o escalonador é quem vai indicar a ordem de disparo para a execução dos programas e vai
influir na sua execução pois é o escalonador que vai realizar a preempção, via comunicação entre
processos (vai indicar a interrupção da execução de um processo e a continuidade da sua
execução).
A linguagem a ser analisada pelo interpretador de comandos é a seguinte:
exec <nome_programa> prioridade=<numero de 1 a 7>, no caso de lista de prioridades
exec <nome_programa>, no caso de ROUND-ROBIN
Os programas a serem executados devem do tipo CPU bound e IO bound (elaborados pelos
alunos). A entrada padrão e a saída padrão dos processos devem ser redirecionadas para os
arquivos entrada.txt e saída.txt, respectivamente. 

Trabalho 2

Trata-se de programar um simulador de um sistema com gerente de memória.
1) Haverá um relógio indicando unidades de tempo dos processos em execução.
Apenas um processo ocupa a CPU. O sistema tem compartilhamento de tempo e
cada processo não pode ocupar a CPU por mais de 10 unidades de tempo.

2) Haverá uma fila de processos prontos e outra de processos bloqueados.

3) Haverá uma memória de 16Mbytes com partições de tamanho fixo como descrito a
seguir:
Partição 1 – 8MB
Partição 2 – 4 MB
Partição 3 – 2MB
Partição 4 – 1MB
Partição 5 – 1 MB

4) Na entrada haverá uma lista de processos a executar com as seguintes informações:
Quantidade de processos,
Número do processo, memória requerida pelo processo,
Total de entradas que descrevem a execução do processo
Tempo de execução 1,
Tempo de operação de entrada e saída 1,
Tempo de execução 2,
Tempo de operação de entrada e saída 2,
...
Tempo de execução n
O simulador deve ler da entrada os processos a executar (todos entram na fila de
prontos, na ordem de entrada) com o seguinte formato:
 < quantidade de processos a executar>
 Processo #< numero do processo > - < quantidade de memória necessária >
 < quantidade de informações sobre o processo>
 exec < tempo de execução >
 [io < tempo de i/o > ] *
Obs: * indica que o processo pode não ter i/o
Exemplo:
3
Processo #1 – 5Mb
3
exec 20
io 5
exec 50
Processo #2 – 7Mb
1
exec 100
Processo #3 – 8Mb
5
exec 30
io 20
exec 30
io 20
exec 10

5) O relógio tem por função diminuir o tempo de execução do processo que está
ocupando a CPU e diminuir os tempos de execução dos processos que estão
bloqueados executando operações de entrada e saída (estas ocorrem em paralelo).

6) Deve ser implementado o swapping dos processos bloqueados (se houver processo a
ser executado na lista de prontos e não houver espaço em memória para a sua
execução).

7) Devem ser implementados separadamente os algoritmos de alocação de memória
First fit, Next fit, Best fit e Worst fit.

8) Deverá ser gerada uma saída indicando, para cada 10 unidades de tempo do relógio,
que processo irá ocupar a CPU, o mapa de alocação de memória e os tempos que
restam de cada processo


#include <stdlib.h>
#include <stdio.h>

typedef struct processo
{
    int id;
    int tempo;
    int tempoRestante;
    int tempoEspera;
    int tempoExecucao;
    int tempoRetorno;
} Processo;

void ordenaPorTempo(Processo *processos, int n)
{
    int i, j;
    Processo aux;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (processos[i].tempo > processos[j].tempo)
            {
                aux = processos[i];
                processos[i] = processos[j];
                processos[j] = aux;
            }
        }
    }
}

void imprimeProcessos(Processo *processos, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Processo %d: %d %d %d %d %d\n", processos[i].id, processos[i].tempo, processos[i].tempoRestante, processos[i].tempoEspera, processos[i].tempoExecucao, processos[i].tempoRetorno);
    }
}

void imprimeDiagramaDeGantt(Processo *processos, int n, int tempoTotal)
{
    int i, j, k = 0;
    int tempoPercorrido = 0;
    for (i = 0; i < n; i++)
    {
        printf("P%d -> ", processos[i].id);
        for (k = 0; k < tempoPercorrido; k++)
        {
            printf("-");
        }
        for (j = 0; j < tempoTotal - tempoPercorrido; j++)
        {
            if (j < processos[i].tempo)
            {
                printf("#");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
        tempoPercorrido += processos[i].tempo;
    }
}

int calculaTempoTotal(Processo *processos, int n)
{
    int i, tempoTotal = 0;
    for (i = 0; i < n; i++)
    {
        tempoTotal += processos[i].tempo;
    }
    return tempoTotal;
}
int main()
{
    int n, i, j, tempoTotal = 0;
    Processo *processos;
    printf("Digite o numero de processos: ");
    scanf("%d", &n);
    processos = (Processo *)malloc(n * sizeof(Processo));
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &processos[i].id, &processos[i].tempo);
        processos[i].tempoRestante = processos[i].tempo;
        processos[i].tempoEspera = 0;
        processos[i].tempoExecucao = 0;
        processos[i].tempoRetorno = 0;
        tempoTotal += processos[i].tempo;
    }
    for (i = 0; i < n; i++)
    {
        processos[i].tempoRetorno = processos[i].tempoEspera + processos[i].tempo;
    }
    ordenaPorTempo(processos, n);
    imprimeProcessos(processos, n);
    printf("\n----------------------------\n");
    imprimeDiagramaDeGantt(processos, n, tempoTotal);
    return 0;
}
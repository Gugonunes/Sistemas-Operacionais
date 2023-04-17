#include <stdlib.h>
#include <stdio.h>

typedef struct processo {
    int id;
    int tempo;
    int tempoRestante;
    int tempoEspera;
    int tempoExecucao;
    int tempoRetorno;
} Processo;

void ordenaPorTempo(Processo *processos, int n) {
    int i, j;
    Processo aux;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (processos[i].tempo > processos[j].tempo) {
                aux = processos[i];
                processos[i] = processos[j];
                processos[j] = aux;
            }
        }
    }
}

void ordenaPorId(Processo *processos, int n) {
    int i, j;
    Processo aux;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (processos[i].id > processos[j].id) {
                aux = processos[i];
                processos[i] = processos[j];
                processos[j] = aux;
            }
        }
    }
}

void imprimeProcessos(Processo *processos, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Processo %d: %d %d %d %d %d\n", processos[i].id, processos[i].tempo, processos[i].tempoRestante, processos[i].tempoEspera, processos[i].tempoExecucao, processos[i].tempoRetorno);
    }
}

int main() {
    int n, i, j, tempoTotal = 0;
    Processo *processos;
    scanf("%d", &n);
    processos = (Processo *) malloc(n * sizeof(Processo));
    for (i = 0; i < n; i++) {
        scanf("%d %d", &processos[i].id, &processos[i].tempo);
        processos[i].tempoRestante = processos[i].tempo;
        processos[i].tempoEspera = 0;
        processos[i].tempoExecucao = 0;
        processos[i].tempoRetorno = 0;
        tempoTotal += processos[i].tempo;
    }
    ordenaPorTempo(processos, n);
    for (i = 0; i < tempoTotal; i++) {
        for (j = 0; j < n; j++) {
            if (processos[j].tempoRestante > 0) {
                processos[j].tempoRestante--;
                processos[j].tempoExecucao++;
                for (int k = 0; k < n; k++) {
                    if (k != j && processos[k].tempoRestante > 0) {
                        processos[k].tempoEspera++;
                    }
                }
                break;
            }
        }
    }
    for (i = 0; i < n; i++) {
        processos[i].tempoRetorno = processos[i].tempoEspera + processos[i].tempo;
    }
    ordenaPorId(processos, n);
    imprimeProcessos(processos, n);
    return 0;
}
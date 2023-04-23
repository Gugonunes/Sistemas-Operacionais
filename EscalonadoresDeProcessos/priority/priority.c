#include <stdlib.h>
#include <stdio.h>

typedef struct Process
{
    int pid;
    int priority;
    int time;
    int startTime;
    int endTime;
} Process;

void priorityFunction(Process *process, int n)
{
    int i, j;
    Process aux;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (process[i].priority > process[j].priority)
            {
                aux = process[i];
                process[i] = process[j];
                process[j] = aux;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            process[i].startTime = 0;
        }
        else
        {
            process[i].startTime = process[i - 1].startTime + process[i - 1].time;
        }
    }
    for (i = 0; i < n; i++)
    {
        process[i].endTime = process[i].startTime + process[i].time;
    }

    int totalTime = 0;
    for (i = 0; i < n; i++)
    {
        totalTime += process[i].startTime;
    }
    printf("Tempo medio de espera: %.2f\n", (float)totalTime / n);
}

void printProcesses(Process *process, int n)
{
    printf("%-10s %-10s %-10s %-10s %-10s\n", "PID", "Priority", "Time", "Start Time", "End Time"); // Cabeçalho da tabela
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%-10d %-10d %-10d %-10d %-10d\n", process[i].pid, process[i].priority, process[i].time, process[i].startTime, process[i].endTime);
        printf("-----------------------------------------------------\n");
    }
}

void orderById(Process *process, int n)
{
    int i, j;
    Process aux;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (process[i].pid > process[j].pid)
            {
                aux = process[i];
                process[i] = process[j];
                process[j] = aux;
            }
        }
    }
}
void printGranntDiagram(Process *process, int n, int totalTime)
{
    orderById(process, n);
    int i, j, k = 0;
    int tempoPercorrido = 0;
    for (i = 0; i < n; i++)
    {
        printf("P%d -> ", process[i].pid);
        for (k = 0; k < process[i].startTime; k++)
        {
            printf("-");
        }
        for (k=0; k < process[i].time; k++)
        {
            printf("#");
        }
        for (k = process[i].startTime + process[i].time; k < totalTime; k++)
        {
            printf("-");
        }
        printf("\n");
    }
}

int main()
{
    int n, i, j, totalTime = 0;
    Process *process;
    printf("Digite o numero de processos: ");
    scanf("%d", &n);
    process = (Process *)malloc(n * sizeof(Process));
    for (i = 0; i < n; i++)
    {
        printf("Digite o PID, prioridade e o tempo do processo (ex: 1 1 3):");
        scanf("%d %d %d", &process[i].pid, &process[i].priority, &process[i].time);
        process[i].startTime = 0;
        process[i].endTime = 0;
        totalTime += process[i].time;
    }
    printf("----------------------------\n");
    priorityFunction(process, n);

    printf("----------------------------\n");

    printProcesses(process, n);

    printGranntDiagram(process, n, totalTime);
    return 0;
}
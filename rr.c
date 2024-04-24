//inputP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


struct process {
    int pid;
    int priority;
    int burstTime;
    int watingTime;
    int TurnaroundTime;
    int done ;
} ;
struct process processes[5];
int cpuTime = 0;
int flag;
const int timeQuantum = 2;
void PrintResult();
int main(int argc, char *argv[])
{

    FILE *fp = fopen("inputP.txt","r"); 
    if (fp == NULL) 
        return EXIT_FAILURE; 
    for (int i = 0; i < 5; i++)
    {
        processes[i].pid = i;
        processes[i].done = 0;
        processes[i].watingTime = 0;
        fscanf(fp, "%d", &processes[i].burstTime);
        fscanf(fp, "%d", &processes[i].priority);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("p b Time = %d   ",processes[i].burstTime);
    }
    int start = 0;
    while (1 == 1)
    {
        //schadular
        int selectedProc = -1;
        for (int i = start ;i < 5 ; i++)
        {
            if (processes[i].done == 0)
            {
                selectedProc = i;
                break ;
            }
        }
        printf("selected  = %d |||| start = %d\n",selectedProc,start);

        //cpu
        int pTime = 0;
        while (pTime < timeQuantum )
        {
            pTime ++;
            cpuTime++;
            if (pTime == processes[selectedProc].burstTime)
                {
                    processes[selectedProc].done = 1;
                    processes[selectedProc].TurnaroundTime = cpuTime ;
                    flag = 0;
                    break;
                }  
        }
        processes[selectedProc].burstTime = processes[selectedProc].burstTime - pTime ;
        start = (selectedProc + 1) % 5;
                                                                                                                                                                                            
        for (int i = 0 ;i < 5 ; i++)
        {
            if (processes[i].done == 0) 
            {
                flag = 1;
                if (i!=selectedProc)
                     processes[i].watingTime += pTime ;
            }
        }
        if (flag == 0)
            break;
    }
    PrintResult();
}
void PrintResult()
{
    float avgTurnaround = 0.0;
    float avgWatingtime = 0.0;
    for (int i = 0; i < 5; i++)
    {
        printf("pid = %d  Turnaround Time = %d  Wating Time = %d\n",processes[i].pid,processes[i].TurnaroundTime,processes[i].watingTime);
        avgTurnaround = avgTurnaround +  processes[i].TurnaroundTime ;
        avgWatingtime = avgWatingtime + processes[i].watingTime ;
    }
    avgTurnaround = avgTurnaround / 5;
    avgWatingtime = avgWatingtime / 5 ;
    printf("Average Turnaround Time = %f Average WatingT ime = %f\n",avgTurnaround,avgWatingtime);
    
}
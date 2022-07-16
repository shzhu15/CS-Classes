#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Process{
    int Process_ID;
    int Arrival_Time;
    int Burst_Duration;
    int Priority;
    int TurnAroundTime;
    int WaitTime;
};
//**********************************************************
struct Gantt
{
  int Process_ID;
  int Arrival_Time;
  int End_Time;
};

void File_Content(struct  Process Processes[], int number);
void FCFS(struct Process Processes[], int number);
void SJFP(struct Process Processes[], int number);
void PRIORITY(struct Process Processes[], int number);
void RR(struct Process Processes[], int number, int quantum);
void Display_Output(struct  Process Processes[],int number,struct Gantt Rows[],int count, char* filename);

int main(int argc, char **argv)
{

    int number_of_pross = 0;

    	if (argc != 2)
    	{
       		printf("Incorrect number of arguments.\n");
       	 	return -1;
    	}

		FILE* file1 = fopen(argv[1], "r");

  while(!feof(file1))
  {
  char  ch = fgetc(file1);
    if(ch == '\n')
    {
      number_of_pross++;
    }
  }
        struct Process Processes[number_of_pross];

        fseek(file1, 0, SEEK_SET);


        number_of_pross=0;


		while(fscanf(file1, "%d,%d,%d,%d",&Processes[number_of_pross].Process_ID,&Processes[number_of_pross].Arrival_Time,&Processes[number_of_pross].Burst_Duration,&Processes[number_of_pross].Priority) != EOF	)
       {
			number_of_pross++;
        }
        fclose(file1);

            File_Content(Processes,number_of_pross);
            FCFS(Processes,number_of_pross);
            SJFP(Processes,number_of_pross);
            PRIORITY(Processes,number_of_pross);

        return 0;
}
//--------------------------------------------------------
void File_Content(struct Process Processes[], int number)
{
    int i;
    printf("PROCESS ID\tARRIVAL TIME\tBURST DURATION\tPRIORITY\n");
    for(i=0;i<number;i++)
    {

        printf("%d\t\t%d\t\t%d\t\t%d\n",Processes[i].Process_ID,Processes[i].Arrival_Time,Processes[i].Burst_Duration,Processes[i].Priority);

    }
}
//---------------------------------------------------------------
void Display_Output(struct  Process Processes[],int number,struct Gantt Rows[],int count, char *filename)
{
      FILE* file;
      int i;
      file=fopen(filename,"w");
      fprintf(file,"PROCESS ID\tARRIVAL TIME\tEND TIME\n");

      for(i=0;i<count;i++)
      {
        fprintf(file,"%10d%10d%10d\n",Rows[i].Process_ID,Rows[i].Arrival_Time,Rows[i].End_Time);
      }

      float avgWait=0;
      float avgTurnAround=0;
      for(i=0;i<number;i++)
      {
          avgWait+=Processes[i].WaitTime;
          avgTurnAround+=Processes[i].TurnAroundTime;
      }
      fprintf(file,"Average Wait Time=%f\n",avgWait/number);
      fprintf(file,"TurnAround Time=%f\n",avgTurnAround/number);
      // Assumption: the value of count recieved is greater than exact number of rows in the Gantt chart by 1. Dont forget to adjust the value if yours is not so.
      fprintf(file,"Throughput=%f\n",((float)number/Rows[count-1].End_Time));
      fclose(file);

}
//------------------------------------------------------------

/*
 Note: Use function Display_Output to display the result. The Processes is the
 updated Processes with their respective waittime, turnAround time.
 Use the array of Gantt Struct to mimic the behaviour of Gantt Chart. Rows is the base name of the same array.
 number is the number of processes which if not changed during processing, is taken care. count is the number of rows in the Gantt chart.

 Number of Processes will not exceed 1000. Create and array of Gantt chart which can accomodate atleast 1000 process.
 */


// -------------FCFS----------------------------------------
void FCFS(struct Process Processes[], int number)
{
    struct Process copy[number];
    for (int i = 0; i < number; i++) {
        copy[i] = Processes[i];
    }
    struct Gantt gantt[2*number-1];

    // int keeping;
    // int counter = 0;
    bool flag = true;
    //---------Start Processing
    while(flag == true) {
        flag = false;
        for (int i = 0; i < number-1; ++i) {
            if(copy[i].Arrival_Time > copy[i+1].Arrival_Time) {
                // if(copy[i].Process_ID < copy[i+1].Process_ID) {
                    struct Process temp = copy[i];
                    copy[i] = copy[i+1];
                    copy[i+1] = temp;
                    flag = true;
                // }
            }
        }
        if(flag == false) {
            break;
        }
    }
    // printf("---------------------------------------------------------------------------------------------------\n");
    // for(int i = 0; i < number; i++) {
    //     printf("%d   %d   %d   %d\n", copy[i].Process_ID, copy[i].Arrival_Time, copy[i].Burst_Duration, copy[i].Priority);
    // }

    for (int i = 0; i < number; i++) {
        gantt[i].Process_ID = copy[i].Process_ID;
        if(i == 0) {
            gantt[i].Arrival_Time = 0;
            gantt[i].End_Time = copy[i].Burst_Duration;
            copy[i].WaitTime = 0;
            copy[i].TurnAroundTime =  gantt[i].End_Time - copy[i].Arrival_Time ;
        }
        if(i != 0) {
            int time = gantt[i-1].End_Time + copy[i].Burst_Duration;
            gantt[i].Arrival_Time = gantt[i-1].End_Time;
            gantt[i].End_Time = time;
            copy[i].WaitTime = gantt[i].Arrival_Time - copy[i].Arrival_Time ;
            copy[i].TurnAroundTime =  gantt[i].End_Time - copy[i].Arrival_Time ;
        }
    }

    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            if(Processes[i].Process_ID == copy[j].Process_ID) {
                // printf("ID1: %d        ID2: %d\n", Processes[i].Process_ID, copy[j].Process_ID);
                Processes[i].WaitTime = copy[j].WaitTime;
                Processes[i].TurnAroundTime = copy[j].TurnAroundTime;
            }
        }
    }
     Display_Output(Processes,number,gantt,number,"FCFS");
     // printf("---------------------------------------------------------------------------------------------------\n");
     // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
     // for(int i = 0; i < number; i++) {
     //     printf("%10d%10d%10d\n", gantt[i].Process_ID, gantt[i].Arrival_Time, gantt[i].End_Time);
     // }

     // float total1 = 0;
     // float total2 = 0;
     // for(int i = 0; i < number; i++) {
     //     total1 += copy[i].WaitTime;
     //     total2 += copy[i].TurnAroundTime;
     // }
     // printf("Average Wait Time=%f\n",total1/number);
     // printf("TurnAround Time=%f\n",total2/number);

    //---------End of Processing
   //Hint: Call function with arguments shown Display_Output(Processes,number,Rows,count,"FCFS");
}



struct ProcessCopy{
    int Process_ID;
    int Arrival_Time;
    int Burst_Duration;
    int Priority;
    int TurnAroundTime;
    int WaitTime;
    bool finished;
};

typedef struct {
    int priority;
    struct ProcessCopy *data;
} node_t;

typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;

void push (heap_t h, int priority, struct ProcessCopy *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

struct ProcessCopy pop (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }
    char *data = h->nodes[1].data;

    h->nodes[1] = h->nodes[h->len];

    h->len--;

    i = 1;
    while (i!=h->len+1) {
        k = h->len+1;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    return data;
}

struct ProcessCopy peek (heap_t *h) {
  return h->nodes[0].priority;
}



//---------------------SJFP---------------------------------------
void SJFP(struct Process Processes[], int number)
{
    // //---------Start Processing
    // struct ProcessCopy arr[number];
    // for (int i = 0; i < number; i++) {
    //     arr[i].Process_ID = Processes[i].Process_ID;
    //     arr[i].Arrival_Time = Processes[i].Arrival_Time;
    //     arr[i].Burst_Duration = Processes[i].Burst_Duration;
    //     arr[i].Priority = Processes[i].Priority;
    //     arr[i].TurnAroundTime = Processes[i].TurnAroundTime;
    //     arr[i].WaitTime = Processes[i].WaitTime;
    //
    // }
    //
    // // bool flag = true;
    // // while(flag == true) {
    // //     flag = false;
    // //     for (int i = 0; i < number-1; ++i) {
    // //         if(arr[i].Arrival_Time > arr[i+1].Arrival_Time) {
    // //             // if(copy[i].Process_ID < copy[i+1].Process_ID) {
    // //                 struct ProcessCopy temp = arr[i];
    // //                 arr[i] = arr[i+1];
    // //                 arr[i+1] = temp;
    // //                 flag = true;
    // //             // }
    // //         }
    // //     }
    // //     if(flag == false) {
    // //         break;
    // //     }
    // // }
    //
    //
    // printf("---------------------------------------------------------------------------------------------------\n");
    // for(int i = 0; i < number; i++) {
    //     printf("%d   %d   %d   %d\n", arr[i].Process_ID, arr[i].Arrival_Time, arr[i].Burst_Duration, arr[i].Priority);
    // }
    // struct Gantt gantt[2*number-1];
    //
    // int counter = 0;
    //
    // Node* queue;
    //
    // int time = 0;
    // int completed = 0;
    // int size = 0;
    // int counterg = 0;
    // while(completed != number) {
    //     if(counter != number) {
    //         for (int i = 0; i < number; i++) {
    //             if(arr[i].Arrival_Time == time) {
    //               if(time == 0) {
    //                 printf("time: %d\n", time);
    //                 queue = newNode(arr[i], arr[i].Burst_Duration);
    //                 counter++;
    //                 printf("added id: %d, with priority of %d added %d\n", arr[i].Process_ID, arr[i].Burst_Duration, counter);
    //                 size++;
    //               }
    //               else {
    //                 push(&queue, arr[i], arr[i].Burst_Duration);
    //                 counter++;
    //                 printf("added id: %d, added %d\n", arr[i].Process_ID, counter);
    //                 size++;
    //               }
    //             }
    //         }
    //     }
    //     struct ProcessCopy current = peek(&queue);
    //     int burst = peekP(&queue);
    //     pop(&queue);
    //     struct ProcessCopy currentnext;
    //     int burstnext;
    //     if(size != 1) {
    //         currentnext = peek(&queue);
    //         burstnext = peekP(&queue);
    //     }
    //     if(burst == burstnext && current.Process_ID > currentnext.Process_ID && size != 1) {
    //             // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
    //             pop(&queue);
    //             push(&queue, current, burst);
    //             current = currentnext;
    //             burst = burstnext;
    //     }
    //     if(current.Process_ID != gantt[counterg].Process_ID) {
    //         counterg++;
    //         gantt[counterg].Process_ID = current.Process_ID;
    //         gantt[counterg].Arrival_Time = time;
    //         gantt[counterg-1].End_Time = time;
    //     }
    //     burst--;
    //     if(burst != 0 ) {
    //         if(size == 1) {
    //             queue = newNode(current, burst);
    //         }
    //         push(&queue, current, burst);
    //     }
    //     if(burst == 0) {
    //         completed++;
    //         size--;
    //         printf("finished id: %d, completed = %d\n", current.Process_ID, completed);
    //     }
    //     time++;
    // }
    // printf("time %d\n", time );
    // gantt[counterg].End_Time = time;
    //
    // printf("---------------------------------------------------------------------------------------------------\n");
    // struct Gantt newgantt[counterg];
    // for (int i = 0; i < counterg; i++) {
    //     newgantt[i] = gantt[i+1];
    // }
    //
    //
    // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
    // for(int i = 0; i < counterg; i++) {
    //     printf("%10d%10d%10d\n", newgantt[i].Process_ID, newgantt[i].Arrival_Time, newgantt[i].End_Time);
    // }

    //---------End of Processing


}

//---------------------------------------------------------------

//------------------PRIORITY-------------------------------------
void PRIORITY(struct Process Processes[], int number)
{
     //---------Start Processing
     struct ProcessCopy arr[number];
     for (int i = 0; i < number; i++) {
         arr[i].Process_ID = Processes[i].Process_ID;
         arr[i].Arrival_Time = Processes[i].Arrival_Time;
         arr[i].Burst_Duration = Processes[i].Burst_Duration;
         arr[i].Priority = Processes[i].Priority;
         arr[i].TurnAroundTime = Processes[i].TurnAroundTime;
         arr[i].WaitTime = Processes[i].WaitTime;

     }

     // bool flag = true;
     // while(flag == true) {
     //     flag = false;
     //     for (int i = 0; i < number-1; ++i) {
     //         if(arr[i].Arrival_Time > arr[i+1].Arrival_Time) {
     //             // if(copy[i].Process_ID < copy[i+1].Process_ID) {
     //                 struct ProcessCopy temp = arr[i];
     //                 arr[i] = arr[i+1];
     //                 arr[i+1] = temp;
     //                 flag = true;
     //             // }
     //         }
     //     }
     //     if(flag == false) {
     //         break;
     //     }
     // }

     //
     // printf("---------------------------------------------------------------------------------------------------\n");
     // for(int i = 0; i < number; i++) {
     //     printf("%d   %d   %d   %d\n", arr[i].Process_ID, arr[i].Arrival_Time, arr[i].Burst_Duration, arr[i].Priority);
     // }
     struct Gantt gantt[2*number-1];
     // gantt[0].Process_ID = arr[0].Process_ID;
     // gantt[0].Arrival_Time = 0;
     // arr[0].WaitTime = 0;
     int counter = 0;

     heap_t *queue = (heap_t *)calloc(1, sizeof (heap_t));     int time = 0;
     int completed = 0;
     int size = 1;
     int counterg = 0;
     while(completed != number) {
         if(counter != number) {
             for (int i = 1; i < number; i++) {
                 if(arr[i].Arrival_Time == time) {
                       push(&queue, arr[i].Priority,arr[i]);
                       counter++;
                       printf("added id: %d, added %d\n", arr[i].Process_ID, counter);
                       size++;
                 }
             }
         }
         struct ProcessCopy current = pop(queue);
         int burst = current.Burst_Duration;
         int priority = peek(queue);
         struct ProcessCopy currentnext;
         int burstnext;
         int priority2;
         if(size != 1) {
             currentnext = pop(queue);
             burstnext = currentnext.Burst_Duration;
             priority2 = peek(queue);
         }
         if(priority > priority2 && current.Process_ID > currentnext.Process_ID && size != 1) {
                 // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
                 push(queue, priority, current);
                 current = currentnext;
                 burst = burstnext;
                 priority = priority2;
         }
         else {
           push(queue, priority2, currentnext);

         }
         if(current.Process_ID != gantt[counterg].Process_ID) {
             counterg++;
             gantt[counterg].Process_ID = current.Process_ID;
             gantt[counterg].Arrival_Time = time;
             gantt[counterg-1].End_Time = time;
         }
         burst--;
         current.Burst_Duration = burst;
         if(burst != 0 ) {
           push(queue, priority, current);
         }
         if(burst == 0) {
             completed++;
             size--;
             printf("finished id: %d, completed = %d\n", current.Process_ID, completed);
         }
         time++;
     }
     printf("time %d\n", time );
     gantt[counterg].End_Time = time;

     printf("---------------------------------------------------------------------------------------------------\n");
     struct Gantt newgantt[counterg];
     for (int i = 0; i < counterg; i++) {
         newgantt[i] = gantt[i+1];
     }


     printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
     for(int i = 0; i < counterg; i++) {
         printf("%10d%10d%10d\n", newgantt[i].Process_ID, newgantt[i].Arrival_Time, newgantt[i].End_Time);
     }

    //---------End of Processing

}

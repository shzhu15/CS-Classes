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

typedef struct node {
    struct ProcessCopy data;
    int priority;
    struct node* next;
} Node;

Node* newNode(struct ProcessCopy data, int p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}

struct ProcessCopy peek(Node** head) {
    return (*head)->data;
}

int peekP(Node** head) {
    return (*head)->priority;
}

void pop(Node** head) {
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void push(Node** head, struct ProcessCopy data, int p) {
    Node* start = (*head);

    Node* temp = newNode(data, p);
    bool flag = false;
    // printf("---------------comparing p1:(%d,%d) and p2:(%d,%d)\n",(*head)->data.Process_ID,(*head)->priority, data.Process_ID, p);
    // if ((*head)->priority >= p && flag == false) {
    //     if((*head)->data.Process_ID > data.Process_ID) {
    //         printf("added %d first\n", data.Process_ID);
    //         temp->next = *head;
    //         (*head) = temp;
    //         flag = true;
    //     }
    // }
    if ((*head)->priority > p && flag == false) {
            temp->next = *head;
            (*head) = temp;
            flag = true;
    }
    else {
        while (start->next != NULL && start->next->priority < p && start->next->data.Process_ID < data.Process_ID) {
            start = start->next;
        }

        temp->next = start->next;
        start->next = temp;
    }
}

//---------------------SJFP---------------------------------------
void SJFP(struct Process Processes[], int number) {
    //---------Start Processing

    


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
    //  bool flag = true;
    //  while(flag == true) {
    //      flag = false;
    //      for (int i = 0; i < number-1; ++i) {
    //          if(arr[i].Arrival_Time > arr[i+1].Arrival_Time) {
    //              // if(copy[i].Process_ID < copy[i+1].Process_ID) {
    //                  struct ProcessCopy temp = arr[i];
    //                  arr[i] = arr[i+1];
    //                  arr[i+1] = temp;
    //                  flag = true;
    //              // }
    //          }
    //      }
    //      if(flag == false) {
    //          break;
    //      }
    //  }
    // // printf("---------------------------------------------------------------------------------------------------\n");
    // // for(int i = 0; i < number; i++) {
    // //     printf("%d   %d   %d   %d\n", arr[i].Process_ID, arr[i].Arrival_Time, arr[i].Burst_Duration, arr[i].Priority);
    // // }
    // struct Gantt gantt[2*number-1];
    //
    // int counter = 0;
    // int size = 0;
    //
    // Node* queue = newNode(arr[0], arr[0].Burst_Duration);
    // counter++;
    // size++;
    // printf("added id: %d, with burst of %d, counter: %d\n", arr[0].Process_ID, arr[0].Burst_Duration, counter);
    // /*
    // push(&queue, arr[1], arr[1].Burst_Duration);
    // counter++;
    // printf("added id: %d at time %d, with burst of %d, counter: %d\n", arr[1].Process_ID, 0, arr[1].Burst_Duration, counter);
    // size++;
    // */
    // gantt[0].Process_ID = arr[0].Process_ID;
    // gantt[0].Arrival_Time = 0;
    //
    // int time = 0;
    // int completed = 0;
    // int counterg = 1;
    // while(completed != number) {
    //     if(counter != number) {
    //         for (int i = 1; i < number; i++) {
    //             if(arr[i].Arrival_Time == time) {
    //                 push(&queue, arr[i], arr[i].Burst_Duration);
    //                 counter++;
    //                 printf("added id: %d at time %d, with burst of %d, counter: %d\n", arr[i].Process_ID, time, arr[i].Burst_Duration, counter);
    //                 size++;
    //             }
    //         }
    //     }
    //     struct ProcessCopy current = peek(&queue);
    //     int burst = peekP(&queue);
    //     pop(&queue);
    //     struct ProcessCopy currentnext;
    //     int burstnext;
    //     // struct ProcessCopy currentnextnext;
    //     // int burstnextnext;
    //     // if(size != 1) {
    //     //     currentnext = peek(&queue);
    //     //     burstnext = peekP(&queue);
    //         // if(current.Process_ID == 18 || currentnext.Process_ID == 18) {
    //         //     pop(&queue);
    //         //     currentnextnext = peek(&queue);
    //         //     burstnextnext = peekP(&queue);
    //         //     push(&queue, currentnext, burstnext);
    //         // }
    //     //}
    //     struct ProcessCopy temp;
    //     int bursttemp;
    //     while(size > 1) {
    //         temp = peek(&queue);
    //         bursttemp = peekP(&queue);
    //         pop(&queue);
    //         if(bursttemp != burst) {
    //             break;
    //         }
    //         if(bursttemp == burst) {
    //             if(temp.Process_ID < current.Process_ID) {
    //                 push(&queue, current, burst);
    //                 current = temp;
    //                 burst = bursttemp;
    //             }
    //         }
    //         push(&queue, temp, bursttemp);
    //
    //     }
    //
    //     // if(burst == burstnext && current.Process_ID > currentnext.Process_ID && size != 1) {
    //     //         // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
    //     //         pop(&queue);
    //     //         push(&queue, current, burst);
    //     //         current = currentnext;
    //     //         burst = burstnext;
    //     //
    //     // }
    //     // if(current.Process_ID == 4) {
    //     //     printf("                                            current process id: %d\n", current.Process_ID);
    //     //
    //     // }
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
    //         else {
    //             push(&queue, current, burst);
    //         }
    //     }
    //     time++;
    //     if(burst == 0) {
    //         completed++;
    //         size--;
    //         printf("                                         finished id: %d at time %d, completed = %d\n", current.Process_ID, time, completed);
    //     }
    //     //time++;
    // }
    // gantt[counterg].End_Time = time;
    //
    //
    // // int total = 0;
    // // for(int i = 0; i < 2*number-1; i++) {
    // //     total += gantt[i].Arrival_Time - gantt[i].Arrival_Time;
    // // }
    // // printf("waittime: %d\n", total/number);
    // //
    // // for(int i = 0; i < number; i++) {
    // //     for(int j = 0; i < 2*number-1; j++) {
    // //         if(Processes[i].Process_ID == gantt[j].Process_ID) {
    // //             Processes[i].WaitTime = gantt[i].Arrival_Time - Processes[i].Arrival_Time + Processes[i].WaitTime;
    // //             Processes[i].TurnAroundTime =  gantt[i].End_Time - Processes[i].Arrival_Time + Processes[i].TurnAroundTime;
    // //         }
    // //     }
    // // }
    // //
    // //
    // // printf("finished SJFP\n");
    // printf("---------------------------------------------------------------------------------------------------\n");
    // struct Gantt newgantt[counterg];
    // // int newCounter = 0;
    // // for (int i = 2; i < counterg; i++) {
    // //    newgantt[newCounter] = gantt[i];
    // //    newCounter++;
    // // }
    //
    // Display_Output(Processes,number,gantt,counterg,"SJFP");
    //
    // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
    // for(int i = 0; i < counterg; i++) {
    //     // printf("%10d%10d%10d\n", gantt[i].Process_ID, gantt[i].Arrival_Time, gantt[i].End_Time);
    //     // if(gantt[i].Process_ID == 0) {
    //     //     break;
    //     // }
    //     newgantt[i].Process_ID = gantt[i+2].Process_ID;
    //     newgantt[i].Arrival_Time = gantt[i+2].Arrival_Time;
    //     newgantt[i].End_Time = gantt[i+2].End_Time;
    //     if(time == newgantt[i].End_Time) {
    //         break;
    //     }
    // }
    // // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
    // for(int i = 0; i < counterg-1; i++) {
    //     printf("%10d%10d%10d\n", newgantt[i].Process_ID, newgantt[i].Arrival_Time, newgantt[i].End_Time);
    // }
}

//---------------------------------------------------------------

//------------------PRIORITY-------------------------------------
void PRIORITY(struct Process Processes[], int number) {

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

      bool flag = true;
      while(flag == true) {
          flag = false;
          for (int i = 0; i < number-1; ++i) {
              if(arr[i].Arrival_Time > arr[i+1].Arrival_Time) {
                  // if(copy[i].Process_ID < copy[i+1].Process_ID) {
                      struct ProcessCopy temp = arr[i];
                      arr[i] = arr[i+1];
                      arr[i+1] = temp;
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
     //     printf("%d   %d   %d   %d\n", arr[i].Process_ID, arr[i].Arrival_Time, arr[i].Burst_Duration, arr[i].Priority);
     // }
     struct Gantt gantt[2*number-1];

     int counter = 0;
     int size = 0;

     Node* queue = newNode(arr[0], arr[0].Priority);
     counter++;
     size++;
     // printf("added id: %d, with burst of %d, counter: %d\n", arr[0].Process_ID, arr[0].Burst_Duration, counter);
     /*
     push(&queue, arr[1], arr[1].Burst_Duration);
     counter++;
     printf("added id: %d at time %d, with burst of %d, counter: %d\n", arr[1].Process_ID, 0, arr[1].Burst_Duration, counter);
     size++;
     */
     gantt[0].Process_ID = arr[0].Process_ID;
     gantt[0].Arrival_Time = 0;

     int time = 0;
     int completed = 0;
     int counterg = 1;
     while(completed != number) {
         if(counter != number) {
             for (int i = 1; i < number; i++) {
                 if(arr[i].Arrival_Time == time) {
                     push(&queue, arr[i], arr[i].Priority);
                     counter++;
                     // printf("added id: %d at time %d, with burst of %d, counter: %d\n", arr[i].Process_ID, time, arr[i].Priority, counter);
                     size++;
                 }
             }
         }
         struct ProcessCopy current = peek(&queue);
         int priority = peekP(&queue);
         pop(&queue);
         struct ProcessCopy currentnext;
         int prioritynext;
         // struct ProcessCopy currentnextnext;
         // int burstnextnext;
         if(size != 1) {
             currentnext = peek(&queue);
             prioritynext = peekP(&queue);
             // if(current.Process_ID == 18 || currentnext.Process_ID == 18) {
             //     pop(&queue);
             //     currentnextnext = peek(&queue);
             //     burstnextnext = peekP(&queue);
             //     push(&queue, currentnext, burstnext);
             // }
         }
         //
         // if(current.Process_ID == 4  || currentnext.Process_ID == 4) {
         //     printf("************************************comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
         //
         // }
         // if(current.Process_ID == 18 || currentnext.Process_ID == 18) {
         //     printf("-------comparing id (%d,%d), and id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext, currentnextnext.Process_ID, burstnextnext);
         //
         // }


         if(priority == prioritynext && current.Process_ID > currentnext.Process_ID && size != 1) {
                 // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
                 pop(&queue);
                 push(&queue, current, priority);
                 current = currentnext;
                 priority = prioritynext;

         }
         // if(current.Process_ID == 4) {
         //     printf("                                            current process id: %d\n", current.Process_ID);
         //
         // }
         if(current.Process_ID != gantt[counterg].Process_ID) {
             counterg++;
             gantt[counterg].Process_ID = current.Process_ID;
             gantt[counterg].Arrival_Time = time;
             gantt[counterg-1].End_Time = time;
         }
         current.Burst_Duration--;
         if(current.Burst_Duration != 0 ) {
             if(size == 1) {
                 queue = newNode(current, priority);
             }
             else {
                 push(&queue, current, priority);
             }
         }
         time++;
         if(current.Burst_Duration == 0) {
             completed++;
             size--;
             // printf("    finished id: %d at time %d, completed = %d\n", current.Process_ID, time, completed);
         }
         //time++;
     }
     gantt[counterg].End_Time = time;

     // for(int i = 0; i < number; i++) {
     //     for(int j = 0; i < counterg; j++) {
     //         if(Processes[i].Process_ID == gantt[j].Process_ID) {
     //             Processes[i].WaitTime = gantt[i].Arrival_Time - gantt[i].Arrival_Time + Processes[i].WaitTime;
     //             Processes[i].TurnAroundTime =  gantt[i].End_Time - gantt[i].Arrival_Time + Processes[i].TurnAroundTime;
     //         }
     //     }
     // }


     Display_Output(Processes,number,gantt,counterg,"PRIORITY");
     // printf("---------------------------------------------------------------------------------------------------\n");
     // //struct Gantt newgantt[2*counterg-1];
     // //for (int i = 0; i < counterg; i++) {
     // //    newgantt[i] = gantt[i];
     // //}
     //
     //
     // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
     // for(int i = 2; i < counterg+1; i++) {
     //     printf("%10d%10d%10d\n", gantt[i].Process_ID, gantt[i].Arrival_Time, gantt[i].End_Time);
     // }






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
     //  bool flag = true;
     //  while(flag == true) {
     //      flag = false;
     //      for (int i = 0; i < number-1; ++i) {
     //          if(arr[i].Arrival_Time > arr[i+1].Arrival_Time) {
     //              // if(copy[i].Process_ID < copy[i+1].Process_ID) {
     //                  struct ProcessCopy temp = arr[i];
     //                  arr[i] = arr[i+1];
     //                  arr[i+1] = temp;
     //                  flag = true;
     //              // }
     //          }
     //      }
     //      if(flag == false) {
     //          break;
     //      }
     //  }
     //
     //
     // printf("---------------------------------------------------------------------------------------------------\n");
     // for(int i = 0; i < number; i++) {
     //     printf("%d   %d   %d   %d\n", arr[i].Process_ID, arr[i].Arrival_Time, arr[i].Burst_Duration, arr[i].Priority);
     // }
     // struct Gantt gantt[2*number-1];
     //
     // int counter = 0;
     // int size = 0;
     //
     // Node* queue = newNode(arr[0], arr[0].Priority);
     // counter++;
     // size++;
     // printf("added id: %d, with burst of %d, counter: %d\n", arr[0].Process_ID, arr[0].Priority, counter);
     // /*
     // push(&queue, arr[1], arr[1].Burst_Duration);
     // counter++;
     // printf("added id: %d at time %d, with burst of %d, counter: %d\n", arr[1].Process_ID, 0, arr[1].Burst_Duration, counter);
     // size++;
     // */
     // gantt[0].Process_ID = arr[0].Process_ID;
     // gantt[0].Arrival_Time = 0;
     //
     // int time = 0;
     // int completed = 0;
     // int counterg = 1;
     // while(completed != number) {
     //     if(counter != number) {
     //         for (int i = 1; i < number; i++) {
     //             if(arr[i].Arrival_Time == time) {
     //                 push(&queue, arr[i], arr[i].Priority);
     //                 counter++;
     //                 printf("added id: %d at time %d, with Priority of %d, counter: %d\n", arr[i].Process_ID, time, arr[i].Priority, counter);
     //                 size++;
     //             }
     //         }
     //     }
     //     // int hold[3];
     //     // int greater = 1;
     //     struct ProcessCopy current = peek(&queue);
     //     // hold[0] = current.Process_ID;
     //     int priority = peekP(&queue);
     //     pop(&queue);
     //     struct ProcessCopy currentnext;
     //     int prioritynext;
     //     // struct ProcessCopy currentnextnext;
     //     // int prioritynextnext;
     //     if(size != 1) {
     //         currentnext = peek(&queue);
     //         prioritynext = peekP(&queue);
     //         // hold[1] = current.Process_ID;
     //         pop(&queue);
     //         // greater = 2;
     //         // if(size > 2) {
     //         //     currentnextnext = peek(&queue);
     //         //     prioritynextnext = peekP(&queue);
     //         //     pop(&queue);
     //             // hold[2] = current.Process_ID;
     //             // greater = 3;
     //         // }
     //     }
     //     // int choice = 0;
     //     // if(greater == 3) {
     //     //     if(priority == prioritynext && priority == prioritynextnext) {
     //     //         int value = 10000;
     //     //         for(int i = 0; i < 2; i++) {
     //     //             if(hold[i] < value) {
     //     //                 value = hold[i];
     //     //                 choice = i;
     //     //             }
     //     //         }
     //     //         if(choice == 0) {
     //     //             push(&queue, currentnext, prioritynext);
     //     //             push(&queue, currentnextnext, prioritynextnext);
     //     //         }
     //     //         if(choice == 1) {
     //     //             push(&queue, current, priority);
     //     //             push(&queue, currentnextnext, prioritynextnext);
     //     //             current = currentnext;
     //     //             priority = prioritynext;
     //     //         }
     //     //         if(choice == 2) {
     //     //             push(&queue, current, priority);
     //     //             push(&queue, currentnext, prioritynext);
     //     //             current = currentnextnext;
     //     //             priority = prioritynextnext;
     //     //         }
     //     //     }
     //     // }
     //     // if(greater == 2) {
     //     //     if(priority == prioritynext && current.Process_ID > currentnext.Process_ID && size != 1) {
     //     //             // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
     //     //             push(&queue, current, priority);
     //     //             current = currentnext;
     //     //             priority = prioritynext;
     //     //
     //     //     }
     //     // }
     //         if(priority == prioritynext && current.Process_ID > currentnext.Process_ID && size != 1) {
     //                 // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
     //                 push(&queue, current, priority);
     //                 current = currentnext;
     //                 priority = prioritynext;
     //
     //         }
     //     // if(current.Process_ID == 4  || currentnext.Process_ID == 4) {
     //     //     printf("************************************comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
     //     //
     //     // }
     //     // if(current.Process_ID == 18 || currentnext.Process_ID == 18) {
     //     //     printf("-------comparing id (%d,%d), and id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext, currentnextnext.Process_ID, burstnextnext);
     //     //
     //     // }
     //
     //     // if(changed == false) {
     //     //     push(&queue, currentnext, prioritynext);
     //     //     if(greater == true) {
     //     //         push(&queue, currentnextnext, prioritynextnext);
     //     //     }
     //     // }
     //
     //
     //     // if(burst == burstnext && current.Process_ID > currentnext.Process_ID && size != 1) {
     //     //         // printf("comparing id (%d,%d), and id (%d,%d)\n", current.Process_ID, burst, currentnext.Process_ID, burstnext);
     //     //         pop(&queue);
     //     //         push(&queue, current, burst);
     //     //         current = currentnext;
     //     //         burst = burstnext;
     //     //
     //     // }
     //
     //
     //     if(current.Process_ID == 4) {
     //         printf("                                            current process id: %d\n", current.Process_ID);
     //
     //     }
     //     if(current.Process_ID != gantt[counterg].Process_ID) {
     //         counterg++;
     //         gantt[counterg].Process_ID = current.Process_ID;
     //         gantt[counterg].Arrival_Time = time;
     //         gantt[counterg-1].End_Time = time;
     //     }
     //     current.Burst_Duration--;
     //     if(current.Burst_Duration != 0 ) {
     //         if(size == 1) {
     //             queue = newNode(current, priority);
     //         }
     //         else {
     //             push(&queue, current, priority);
     //         }
     //     }
     //     time++;
     //     if(current.Burst_Duration == 0) {
     //         completed++;
     //         size--;
     //         printf("    finished id: %d at time %d, completed = %d\n", current.Process_ID, time, completed);
     //     }
     //     //time++;
     // }
     // printf("time %d\n", time );
     // gantt[counterg].End_Time = time;
     //
     // printf("---------------------------------------------------------------------------------------------------\n");
     // //struct Gantt newgantt[2*counterg-1];
     // //for (int i = 0; i < counterg; i++) {
     // //    newgantt[i] = gantt[i];
     // //}
     //
     //
     // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
     // for(int i = 2; i < counterg+1; i++) {
     //     printf("%10d%10d%10d\n", gantt[i].Process_ID, gantt[i].Arrival_Time, gantt[i].End_Time);
     // }

    //---------End of Processing

}

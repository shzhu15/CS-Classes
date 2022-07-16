#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <queue>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

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
 number is the number of Processes which if not changed during processing, is taken care. count is the number of rows in the Gantt chart.

 Number of Processes will not exceed 1000. Create and array of Gantt chart which can accomodate atleast 1000 process.
 */


// -------------FCFS----------------------------------------
void FCFS(struct Process Processes[], int number) {
    //---------Start Processing
    //getting copy of array
    struct Process copy[number];
    for (int i = 0; i < number; i++) {
        copy[i] = Processes[i];
    }
    struct Gantt gantt[2*number-1];

    //sorting array
    bool flag = true;
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
    //reassigning values
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            if(Processes[i].Process_ID == copy[j].Process_ID) {
                Processes[i].WaitTime = copy[j].WaitTime;
                Processes[i].TurnAroundTime = copy[j].TurnAroundTime;
            }
        }
    }
     Display_Output(Processes,number,gantt,number,(char*)"FCFS");
     // printf("---------------------------------------------------------------------------------------------------\n");
     // printf("PROCESS ID\tARRIVAL TIME\tEND TIME\n");
     // for(int i = 0; i < number; i++) {
     //     printf("%10d%10d%10d\n", gantt[i].Process_ID, gantt[i].Arrival_Time, gantt[i].End_Time);
     // }

     // float total1 = 0;
     // float total2 = 0;
     // for(int i = 0; i < number; i++) {
     //     total1 += Processes[i].WaitTime;
     //     total2 += Processes[i].TurnAroundTime;
     // }
     // printf("Average Wait Time=%f\n",total1/number);
     // printf("TurnAround Time=%f\n",total2/number);

    //---------End of Processing
   //Hint: Call function with arguments shown Display_Output(Processes,number,Rows,count,"FCFS");
}



//---------------------SJFP---------------------------------------
void SJFP(struct Process Processes[], int number)
{
    //---------Start Processing
    struct Gantt gantt[2*number-1];
    bool flag = true;
    //sorting list
    while(flag == true) {
        flag = false;
        for (int i = 0; i < number-1; ++i) {
            if(Processes[i].Arrival_Time > Processes[i+1].Arrival_Time) {
                // if(Processes[i].Process_ID < Processes[i+1].Process_ID) {
                    struct Process temp = Processes[i];
                    Processes[i] = Processes[i+1];
                    Processes[i+1] = temp;
                    flag = true;
                // }
            }
        }
        if(flag == false) {
            break;
        }
    }

    int ganttCounter = 0;
    int finished = 0;
    int time = 0;
    int minmum = 2000000000;
    int shortest_Process = 0;
    int end_time;
    bool ProcessArrived = false;
    int burst[number];

    for(int i = 0; i < number; i++) {
        burst[i] = Processes[i].Burst_Duration;
    }

    while(finished != number) {
        for(int i = 0; i < number; i++) {
            if(Processes[i].Arrival_Time <= time && burst[i] > 0 && burst[i] < minmum) {
                shortest_Process = i;
                minmum = burst[i];
                ProcessArrived = true;
            }
        }

        if(ProcessArrived == false) {
            time++;
            continue;
        }

        burst[shortest_Process]--;
        minmum = burst[shortest_Process];
        if (minmum == 0) {
            minmum = 2000000000;
        }

        if(burst[shortest_Process] == 0) {
            finished++;
            end_time = time + 1;
            ProcessArrived = false;

            Processes[shortest_Process].WaitTime = end_time - Processes[shortest_Process].Arrival_Time - Processes[shortest_Process].Burst_Duration;
            Processes[shortest_Process].TurnAroundTime = end_time - Processes[shortest_Process].Arrival_Time;
            if(Processes[shortest_Process].WaitTime < 0) {
                Processes[shortest_Process].WaitTime = 0;
            }
        }

        if(ganttCounter == 0 || gantt[ganttCounter - 1].Process_ID != Processes[shortest_Process].Process_ID ) {
            ganttCounter++;
        }
        gantt[ganttCounter - 1].Process_ID = Processes[shortest_Process].Process_ID;
        time++;
        if((ganttCounter - 1) == 0) {
            gantt[0].Arrival_Time = 0;
        }
        else {
            gantt[ganttCounter - 1].Arrival_Time = gantt[ganttCounter - 2].End_Time;
        }
        gantt[ganttCounter - 1].End_Time = time;
    }
    Display_Output(Processes,number,gantt,ganttCounter,(char*)"SJFP");

    //---------End of Processing


}

//---------------------------------------------------------------
struct ProcessCopy{
    int Process_ID;
    int Arrival_Time;
    int Burst_Duration;
    int Priority;
    int TurnAroundTime;
    int WaitTime;
    int timer;
    bool done;
};
//------------------PRIORITY-------------------------------------
void PRIORITY(struct Process Processes[], int number)
{

     //---------Start Processing
     struct ProcessCopy copy[number];
     for (int i = 0; i < number; i++) {
         copy[i].Process_ID = Processes[i].Process_ID;
         copy[i].Arrival_Time = Processes[i].Arrival_Time;
         copy[i].Burst_Duration = Processes[i].Burst_Duration;
         copy[i].Priority = Processes[i].Priority;
         copy[i].TurnAroundTime = Processes[i].TurnAroundTime;
         copy[i].WaitTime = Processes[i].WaitTime;
         copy[i].timer = Processes[i].Burst_Duration;
         copy[i].done = false;
     }
     struct Gantt gantt[2*number-1];
     bool flag = true;
     //sorting list
     while(flag == true) {
         flag = false;
         for (int i = 0; i < number-1; ++i) {
             if(copy[i].Arrival_Time > copy[i+1].Arrival_Time) {
                 // if(Processes[i].Process_ID < Processes[i+1].Process_ID) {
                     struct ProcessCopy temp = copy[i];
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

     int ganttCounter = 0;                                  //counter to see how many processes for the gantt chart
     int finished = 0;                                      //counter to check how many process are finished
     int time = 0;                                          //time
     int minmum = 2000000000;                               //minmum PRIORITY
     int current_Process = 0;                               //index of the process
     int end_time;                                          //when a process exits
     bool ProcessArrived = false;                           //check to see if there is a current process

     //to keep running until all processes are finsihed
     while(finished != number) {
         for(int i = 0; i < number; i++) {
             if(copy[i].Arrival_Time <= time && copy[i].Priority < minmum && copy[i].Priority > 0 && copy[i].done == false) {       //if the arrival time is less than time, and the Priority is less than the current Priority
                 ProcessArrived = true;
                 minmum = copy[i].Priority;
                 current_Process = i;
             }
         }
         // printf("current_Process %d, timer is %d\n", current_Process, copy[current_Process].timer);
         // cout << "Press Enter to Continue";
         // cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

         if(ProcessArrived == false) {
             time++;
             continue;
         }

         copy[current_Process].timer--;
         minmum = copy[current_Process].Priority;
         if (minmum == 0) {
             minmum = 2000000000;
         }

         if(copy[current_Process].timer <= 0) {                         //if the process remaining burst time is less than 0, add to gantt
             copy[current_Process].done = true;
             finished++;
             // printf("added to gantt %d\n", finished);
             minmum = 2000000000;                                          //reset Priority
             ProcessArrived = false;
             end_time = time + 1;
             copy[current_Process].WaitTime = end_time - copy[current_Process].Arrival_Time - copy[current_Process].Burst_Duration;
             copy[current_Process].TurnAroundTime = end_time - copy[current_Process].Arrival_Time;
             if(copy[current_Process].WaitTime < 0) {
                 copy[current_Process].WaitTime = 0;
             }
         }

         if(ganttCounter == 0 || gantt[ganttCounter - 1].Process_ID != copy[current_Process].Process_ID ) {     //if the last process is not the same as the current one
             ganttCounter++;
         }
         gantt[ganttCounter - 1].Process_ID = copy[current_Process].Process_ID;
         time++;
         if((ganttCounter - 1) == 0) {
             gantt[0].Arrival_Time = 0;
         }
         else {
             gantt[ganttCounter - 1].Arrival_Time = gantt[ganttCounter - 2].End_Time;
         }
         gantt[ganttCounter - 1].End_Time = time;
     }
     for (int i = 0; i < number; i++) {
         for (int j = 0; j < number; j++) {
             if(Processes[i].Process_ID == copy[j].Process_ID) {
                 Processes[i].WaitTime = copy[j].WaitTime;
                 Processes[i].TurnAroundTime = copy[j].TurnAroundTime;
             }
         }
     }
     Display_Output(Processes,number,gantt,ganttCounter,(char*)"PRIORITY");
    //---------End of Processing

}

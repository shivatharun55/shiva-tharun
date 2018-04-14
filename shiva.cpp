#include<stdio.h> 
#include<conio.h>
#include<stdlib.h>
struct process
{
	int pid;
	int burst_time;
	int waiting_time;

};
typedef struct process Process;

int total_waiting_time;

void sort_process_by_burst_time(Process p[], int n);
void calculate_waiting_time(Process p[], int n);
void print_gantt_chart(Process p[], int n);
void sort_process_by_burst_time(Process p[], int n)
{
    int i, j;
    Process temp;
    for(i=0; i<n-1; i++) {
        for(j=0; j<n-1-i; j++) {
            if(p[j].burst_time > p[j+1].burst_time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
   void print_gantt_chart(Process p[], int n)
{
    int i, j;
    int last = p[n-1].burst_time + ( n== 1 ? 0 : p[n-1].waiting_time);
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time-1; j++) printf(" ");
        printf("p%d", p[i].pid);
        for(j=0; j<p[i].burst_time-1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");
    int minus = 0;
    for(i=0; i<n; i++) {
        if(p[i].waiting_time>9) printf(" ");
        printf("%d", p[i].waiting_time);
        if(p[i+1].waiting_time>9){
          minus = 1;
        }
        if(i+1 == n )  if (last>9) minus = 1;
        for(j=0; j<p[i].burst_time-minus; j++) printf("  ");

    }
    if(last>9) printf(" ");
    printf("%d\n", last);
}

int main() 
{ 
 
  int count,j,n,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  
  remain=n; 
  for(count=0;count<n;count++) 
  { 
  
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1); 
   // if(at[count]==0)
   // {
   // 	printf("Error! Do not enter zero");
    	
   //}
   //else
	
    scanf("%d",&at[count]); 
    scanf("%d",&bt[count]); 
    
    rt[count]=bt[count]; 
  } 
  
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(at[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}

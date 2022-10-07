/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int x=0;
int count=0;

void time (int signum){
  printf("The program ran for %d seconds \n",count);
  exit(1);
}

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  x+=1;
  count+=1;
}

int main(int argc, char * argv[])
{
  while(1){
    signal(SIGINT,time);
    signal(SIGALRM,handler); //register handler to handle SIGALRM
    alarm(1); //Schedule a SIGALRM for 1 second
    while(x==0); //busy wait for signal to be delivered
    printf("Turing was right!\n");
    x=0;
  }
  return 0; //never reached
}
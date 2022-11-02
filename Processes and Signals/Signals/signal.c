/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int x=0;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  x+=1;
}

int main(int argc, char * argv[])
{
  while(1){
    signal(SIGALRM,handler); 
    alarm(1); 
    while(x==0); 
    printf("Turing was right!\n");
    x=0;
  }
  return 0; 
}
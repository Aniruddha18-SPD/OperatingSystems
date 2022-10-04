#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define   BUF_SIZE   100

void  main(void) {
  pid_t  pid1,pid2,pid;

  int status;
  char   buf[BUF_SIZE];
  int lower=1, upper=30;
  srand(time(0));
  int max1 = (rand() %
        (upper - lower + 1)) + lower;
  int max2 = (rand() %
        (upper - lower + 1)) + lower;
  printf("max1=%d,max2=%d\n" ,max1,max2);

  pid1 = fork();
  if (pid1==0){
     int pidc = getpid();
     int ppid = getppid();
     int   i;
     
     for (i = 1; i <= max1; i++){
          printf("Child Pid: %d is going to sleep!\n", pidc);
          srand(time(NULL));
          int time = (rand() % (10)) + 1;
          sleep(time);
          printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",pidc,ppid);
     }
     exit(0);
  }

  else{
    pid2=fork();
    if (pid2==0){
     int pidc = getpid();
     int ppid = getppid();
     int   i;

     
     for (i = 1; i <= max2; i++){
          printf("Child Pid: %d is going to sleep!\n", pidc);
          srand(time(NULL));
          int time = (rand() % (10)) + 1;
          sleep(time);
          printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",pidc,ppid);
     }
     exit(0);
  }
  }


write(1, buf, strlen(buf));
pid = wait(&status);
sprintf(buf, "Child Pid: %d has completed\n", pid);
write(1, buf, strlen(buf));
pid = wait(&status);
printf("Child Pid: %d has completed\n", pid);

}
  

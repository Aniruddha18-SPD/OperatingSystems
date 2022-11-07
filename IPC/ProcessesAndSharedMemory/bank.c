#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void  ChildProcess(int []);
void  ParentProcess(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;

     ShmID = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (main) ***\n");
          exit(1);
     }
     printf("Process has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (main) ***\n");
          exit(1);
     }
     printf("Process has attached the shared memory...\n");

     ShmPTR[0] = 0;
     ShmPTR[1] = 0;
     printf("Bank initialized to: %d\n",ShmPTR[0]);

     printf("Bank is about to fork a main process...\n");
     pid = fork();
     if (pid < 0) {
        printf("*** fork error (main) ***\n");
        exit(1);
     }
     else if (pid == 0) {
        ChildProcess(ShmPTR);
        exit(0);
     } else {
       ParentProcess(ShmPTR);
     }

     wait(&status);
     printf("Process has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Process has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Process has removed its shared memory...\n");
     printf("Process exits...\n");
    //  exit(0);
}

void  ChildProcess(int  SharedMem[])
{
  int account, balance;
  srand(getpid());
  for (int i=0; i<25; i++) {
    sleep(rand()%6);
    while(SharedMem[1] != 1);
		account = SharedMem[0];
    balance = rand() % 51;
    printf("Poor Student needs $%d\n", balance);
    if (balance <= account) {
      account -= balance;
      printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, account);
    } else {
      printf("Poor Student: Not Enough Cash ($%d)\n", account );
    }
    SharedMem[0] = account;
    SharedMem[1] = 0;
  }
}

void  ParentProcess(int SharedMem[]) {
  int account, balance;
  srand(getpid());

  for (int i=0; i<25; i++) {
    sleep(rand()%6);
    account = SharedMem[0];
    while(SharedMem[1] != 0);
    if (account <= 100) {
      balance = rand()%101;
      if (balance % 2 == 0) {
        account += balance;
        printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, account);
        
      } else {
        printf("Dear old Dad: Doesn't have any money to give\n");
      }
      SharedMem[0] = account;
    } else {
      printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
    }
    SharedMem[1] = 1;
  }

}
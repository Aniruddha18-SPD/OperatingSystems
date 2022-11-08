#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
//help from ujjwal adhikari

void ChildProcess(int []);
void ParentProcess(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;

     ShmID = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of two integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Process has attached the shared memory...\n");

     ShmPTR[0] = 0;
     ShmPTR[1] = 0;
     int BannkAccount = ShmPTR[0];

     printf("Orig Bank Account = %d\n",
            BannkAccount);

     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          ChildProcess(ShmPTR);
          exit(0);
     }

     else{
       ParentProcess(ShmPTR);
     }

     wait(&status);
     shmdt((void *) ShmPTR);
     shmctl(ShmID, IPC_RMID, NULL);
     exit(0);
}

void  ParentProcess(int  SharedMem[])
{
  //int BannkAccount = SharedMem[0];
  //int Turn = SharedMem[1];
  int account;
  int balance;
  srand(getpid());
  for (int i=0; i<25; i++){
    int x = rand()%6;
    sleep(x);
    account=SharedMem[0];
    while (SharedMem[1] !=0);
      if (account<=100){
        int add = rand()%101;
        balance=add;
        if (balance%2==0){
          account+=balance;
          printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, account);
        }
        else if (balance%2==1){
          printf("Dear old Dad: Doesn't have any money to give \n");
        }
      SharedMem[0]=account;
      }
      else {
        printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account);
      }    
      SharedMem[1]=1;
  }
}


void  ChildProcess(int  SharedMem[])
{
  //int BannkAccount = SharedMem[0];
  //int Turn = SharedMem[1];
  int account;
  int balance;
  srand(getpid());
  for (int i=0; i<25; i++){
    int x = rand()%6;
    sleep(x);
    while (SharedMem[1] !=1);
      account=SharedMem[0];
      int add = rand()%51;
      balance=add;
      printf("Poor Student needs $%d\n", balance);
      if (balance<=account){
        account=account-balance;
        printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, account);
      }
      else {
        printf("Poor Student: Not Enough Cash ($%d)\n", account );
      }
    SharedMem[0]=account;
    SharedMem[1]=0;
  }
}
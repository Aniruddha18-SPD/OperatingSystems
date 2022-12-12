#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>
#include <errno.h>
#include <limits.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int random_num();

int  main(int argc, char **argv) {
  pid_t pid;
  int status;

  int fd, i, zero=0, *BankAccount;
  sem_t *mutex;

  if (argc != 3) {
    printf("Use: %s #1 #2\n", argv[0]);
    exit(1);
  }

  

  fd = open("log2.txt", O_RDWR | O_CREAT, S_IRWXU);
  write(fd,&zero,sizeof(int));
  BankAccount = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);
  
  
 if ((mutex = sem_open("shm_proc2maphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }

  
  for (i = 0; i < atoi(argv[2]); i++) { 
    pid = fork();
    if (pid < 0) {
      exit(1);
    }
    else if (pid == 0) { 
      int x;
      for (x = 0;; x++) {
        sleep(random_num(0, 5));
        printf("Poor Student #%d: Attempting to Check Balance\n", i+1);
        sem_wait(mutex);

        int localBalance = *BankAccount;
        if (localBalance % 2 == 0) {
          // Withdraw money
          int need = random_num(0, 50);
          printf("Poor Student #%d needs $%d\n", i+1, need);

          if (need <= localBalance) {
            localBalance -= need;
            printf("Poor Student: Withdraws $%d / Balance = $%d\n", need, localBalance);
          }
          else {
            printf("Poor Student #%d: Not Enough Cash ($%d)\n", i+1, localBalance);
          }
          *BankAccount = localBalance;
        }  
        else {
          printf("Poor Student #%d: Last Checking Balance = $%d\n", i+1, localBalance);
        }
        sleep(2);
        sem_post(mutex);
        sleep(1);
      }
      exit(0);
    }
  }
  
  
  for (i = 0;; i++) {
    sleep(random_num(0, 5));
    printf("Dear Old Dad: Attempting to Check Balance\n");
    sem_wait(mutex);

    int localBalance = *BankAccount;
    int num = random_num(0, INT_MAX);

    if (num % 2 == 0) {
      if (localBalance < 100) {
        // Deposit money
        int amount = random_num(0, 100);

        if (amount % 2 == 0) {
          localBalance += amount;
          printf("Dear old Dad: Deposits $%d / Balance = $%d\n", amount, localBalance);
          *BankAccount = localBalance;
        }
        else {
          printf("Dear old Dad: Doesn't have any money to give\n");
        }
      }
      else {
        printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", localBalance);
      }
    }  
    else {
      printf("Dear old Dad: Last Checking Balance = $%d\n", localBalance);
    }
    sleep(2);
    sem_post(mutex);
    sleep(1);
  }
  exit(0);
}

  
int random_num(int lower, int upper)
{
  srand(time(0));

  int num = (rand() % (upper - lower + 1)) + lower;

  return num;
}
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char **argv){
  char* grep_arg = argv[1];
  int pipefd[2], pid;

  if (pipe(pipefd) == -1){
    fprintf(stderr, "pipe Failed!");
    return -1;
  }

  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", grep_arg, NULL};

  pid = fork();

  if (pid == 0)
  {
    int pipefd1[2], pid1;
    if (pipe(pipefd1) == -1){
      fprintf(stderr, "pipe Failed!");
      return -1;
    }
    char *sort_args[] = {"sort", NULL};

    close(pipefd[1]);

    pid1 = fork();

    if (pid1 == 0){
      dup2(pipefd1[0], 0);
      close(pipefd1[1]);
      execvp("sort", sort_args);
    }

    else{
      dup2(pipefd[0], 0);
      close(pipefd[1]);
      dup2(pipefd1[1], 1);
      close(pipefd1[0]);
      execvp("grep", grep_args);
    }
  }
  else{

    dup2(pipefd[1], 1);

    close(pipefd[0]);

    execvp("cat", cat_args);

  }
}
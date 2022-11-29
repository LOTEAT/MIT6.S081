#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int parent_pipe[2];
  int child_pipe[2];
  pipe(parent_pipe);
  pipe(child_pipe);
  char message[] = {"6"};
  
  // child process
  if(fork() == 0){
    close(parent_pipe[1]);
    close(child_pipe[0]);
    if(read(parent_pipe[0], message, 1) != 1){
      fprintf(2, "read error\n");
      exit(1);
    }
    printf("%d: received ping\n", getpid());
    if(write(child_pipe[1], message, 1) != 1){ 
      fprintf(2, "write error\n");
      exit(1);
    }
    exit(0);
  } 
  close(parent_pipe[0]);
  close(child_pipe[1]);
  if(write(parent_pipe[1], message, 1) != 1){
    fprintf(2, "write error\n");
    exit(1);
  }
  if(read(child_pipe[0], message, 1) != 1){
    fprintf(2, "read error\n");
    exit(1);
  }
  printf("%d: received pong\n", getpid());
  wait(0);
  exit(0);
}

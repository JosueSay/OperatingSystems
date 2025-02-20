#include <unistd.h>
#include <stdio.h>

int main()
{

  fork();
  fork();
  fork();
  fork();

  printf("Proceso PID: %d, PPID: %d\n", getpid(), getppid());

  return 0;
}
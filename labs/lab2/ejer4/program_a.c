#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{

  pid_t pid = fork();

  if (pid > 0)
  {
    // padre
    while (true)
    {
    }
  }
  else if (pid == 0)
  {
    printf("Soy el proceso hijo con pid = %d", getpid());
  }
  else
  {

    perror("Error en fork()");
    return -1;
  }

  return 0;
}
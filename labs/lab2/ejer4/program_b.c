#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{

  pid_t pid = fork();
  int count = 4000000;

  if (pid > 0)
  {
    // padre
    while (true)
    {
    }
  }
  else if (pid == 0)
  {
    for (size_t i = 0; i < count; i++)
    {
      printf("El contador va por %d\n", count + 1);
    }
  }
  else
  {

    perror("Error en fork()");
    return -1;
  }

  return 0;
}
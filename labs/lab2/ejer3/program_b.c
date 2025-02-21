#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

  pid_t pid, pid_s, pid_gs;
  clock_t timer1, timer2;
  int count = 1000000;
  double result;

  timer1 = clock();
  pid = fork();

  if (pid > 0)
  {
    // padre
    wait(NULL);
    timer2 = clock();
    result = (double)(timer2 - timer1) / CLOCKS_PER_SEC;
    printf("El resultado de la resta de clock = %fs", result);
  }
  else if (pid == 0)
  {
    pid_s = fork();

    if (pid_s > 0)
    {
      // hijo
      for (size_t i = 0; i < count; i++)
      {
        printf("%zu", i);
      }
      wait(NULL);
    }
    else if (pid_s == 0)
    {
      pid_gs = fork();

      if (pid_gs > 0)
      {
        // nieto
        for (size_t i = 0; i < count; i++)
        {
          printf("%zu", i);
        }
        wait(NULL);
      }
      else if (pid_gs == 0)
      {
        // bisnieto
        for (size_t i = 0; i < count; i++)
        {
          printf("%zu", i);
        }
      }
      else
      {
        perror("Error en fork()");
        return -1;
      }
    }
    else
    {
      perror("Error en fork()");
      return -1;
    }
  }
  else
  {
    perror("Error en fork()");
    return -1;
  }

  return 0;
}

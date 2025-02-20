#include <unistd.h>
#include <stdio.h>

int main()
{
  int count_p = 0;

  fork();
  fork();
  fork();
  fork();

  count_p++;

  printf("La cantidad de contador de procesos fue %d", count_p);

  return 0;
}
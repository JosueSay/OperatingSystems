#include <unistd.h>
#include <stdio.h>

int main()
{
  int count_p = 0;
  int count = 4;

  for (size_t i = 0; i < count; i++)
  {
    fork();
  }

  count_p++;

  printf("La cantidad de contador de procesos fue %d", count_p);

  return 0;
}
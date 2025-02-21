#include <stdio.h>
#include <time.h>

int main()
{
  clock_t timer1, timer2;
  int count = 1000000;
  double result;

  timer1 = clock();
  for (size_t i = 0; i < count; i++)
  {
    // printf("%zu", i);
  }

  for (size_t i = 0; i < count; i++)
  {
    // printf("%zu", i);
  }

  for (size_t i = 0; i < count; i++)
  {
    // printf("%zu", i);
  }
  timer2 = clock();

  result = (double)(timer2 - timer1) / CLOCKS_PER_SEC;

  printf("El resultado de la resta de clock = %fs", result);

  return 0;
}

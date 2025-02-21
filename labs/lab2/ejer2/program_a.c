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
  }

  for (size_t j = 0; j < count; j++)
  {
  }

  for (size_t k = 0; k < count; k++)
  {
  }
  timer2 = clock();

  result = (double)(timer2 - timer1);

  printf("El resultado de la resta de clock = %f", result);

  return 0;
}

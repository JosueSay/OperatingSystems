#include <unistd.h>
#include <stdio.h>

int main()
{
  int count = 4;

  for (size_t i = 0; i < count; i++)
  {
    fork();
  }

  return 0;
}
#include <unistd.h>

int main()
{

  int count = 4;

  for (size_t i = 0; i < count; i++)
  {
    forkk();
  }

  return 0;
}
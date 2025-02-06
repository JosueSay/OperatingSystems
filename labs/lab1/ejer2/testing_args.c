
/*
  Código exploratorio para ver funcionamiento de argc y argv
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  int contador = argc;
  int selector = 1;

  while (contador > 1)
  {
    printf("%s - %d - %d\n", argv[selector], contador, selector);
    contador--;
    selector++;
  }

  return 0;
}

#include <stdio.h>
#include <unistd.h>
int main()
{
  int f = fork();

  if (f == 0)
  {
    execl("./a.exe", "a", (char *)NULL); // Se adjunta un arg, para evitar los warings en consola
  }
  else
  {
    printf("%d\n", (int)getpid());
    execl("./a.exe", "a", (char *)NULL);
  }

  return 0;
}

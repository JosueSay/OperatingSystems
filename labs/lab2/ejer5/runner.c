#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork();

  if (pid == -1)
  {
    perror("Error en fork()");
    exit(1);
  }
  else if (pid == 0)
  {
    // Hijo ejecuta 'b'
    printf("I am b\n");
    execl("./ipc.exe", "ipc", "2", "b", (char *)NULL);
    perror("Error al ejecutar ipc con 'b'");
    exit(1);
  }
  else
  {
    // Esperar a que 'b' termine antes de ejecutar 'a'
    wait(NULL);
    sleep(1); // Pequeña espera para sincronización

    // Padre ejecuta 'a'
    printf("I am a\n");
    execl("./ipc.exe", "ipc", "3", "a", (char *)NULL);
    perror("Error al ejecutar ipc con 'a'");
    exit(1);
  }

  return 0;
}

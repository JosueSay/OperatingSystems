#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 20

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);
  char x = argv[2][0];

  int fd;
  int pipefd[2];

  // Crear un pipe para comunicación
  if (pipe(pipefd) == -1)
  {
    perror("Error al crear el pipe");
    exit(1);
  }

  // Intentamos abrir o crear la memoria compartida
  fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (fd == -1)
  {
    perror("Error al abrir/crear la memoria compartida");
    exit(1);
  }

  // Ajustar el tamaño de la memoria compartida
  if (ftruncate(fd, SHM_SIZE) == -1)
  {
    perror("Error al ajustar tamaño de la memoria compartida");
    exit(1);
  }

  printf("[Proceso padre] Creando la memoria compartida con file descriptor: %d\n", fd);

  // Crear proceso hijo
  pid_t pid = fork();

  if (pid == -1)
  {
    perror("Error al hacer fork()");
    exit(1);
  }
  else if (pid == 0)
  { // Proceso hijo
    close(pipefd[1]);

    // Mapear memoria compartida
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
      perror("Error al mapear la memoria compartida en el hijo");
      exit(1);
    }

    printf("[Proceso hijo] Memoria compartida mapeada correctamente.\n");

    // Leer del pipe y escribir en la memoria compartida
    char received_char;
    int index = 0;
    while (read(pipefd[0], &received_char, sizeof(received_char)) > 0)
    {
      ((char *)shm_ptr)[index++] = received_char;
      if (index >= SHM_SIZE)
        break; // No exceder el tamaño
    }

    close(pipefd[0]);
    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    exit(0);
  }
  else
  { // Proceso padre
    close(pipefd[0]);

    // Mapear memoria compartida
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
      perror("Error al mapear la memoria compartida en el padre");
      exit(1);
    }

    printf("[Proceso padre] Memoria compartida mapeada correctamente.\n");

    // Ciclo de iteraciones
    for (int i = 1; i <= SHM_SIZE; i++)
    {
      if (i % n == 0)
      {
        if (write(pipefd[1], &x, sizeof(x)) == -1)
        {
          perror("Error al escribir en el pipe");
          exit(1);
        }
      }
    }

    close(pipefd[1]);

    wait(NULL);

    // Imprimir el contenido de la memoria compartida
    printf("[Proceso padre] Contenido de la memoria compartida:\n");
    for (int i = 0; i < SHM_SIZE; i++)
    {
      if (((char *)shm_ptr)[i] != '\0')
      { // Imprimir solo posiciones escritas
        printf("%c", ((char *)shm_ptr)[i]);
      }
    }
    printf("\n");

    // Limpiar recursos
    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    shm_unlink(SHM_NAME);

    printf("[Proceso padre] Recursos limpiados correctamente.\n");
  }

  return 0;
}

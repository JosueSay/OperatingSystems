#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 1024

int main(int argc, char *argv[])
{
  int fd;
  int pipefd[2];

  // Crear un pipe para comunicación
  if (pipe(pipefd) == -1)
  {
    perror("Error al crear el pipe");
    exit(1);
  }

  // Se abre la memoria compartida, si no, se crea segun el file descriptor
  // con tamaño SHM_SIZE, de lo contrario se imprime un mensaje que ya existe (fue abierto por otro proceso)

  fd = shm_open(SHM_NAME, O_RDWR, 0666);

  if (fd == -1)
  {
    printf("Creando memoria compartida...\n");
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
    {
      perror("Error al crear la memoria compartida");
      exit(1);
    }
    ftruncate(fd, SHM_SIZE);
  }
  else
  {
    printf("Memoria compartida encontrada, usando la existente.\n");
  }

  printf("File descriptor de la memoria compartida: %d\n", fd);

  // Crear un proceso hijo y que este obtenga el file descriptor por la comunicación con el padre
  pid_t pid = fork();

  if (pid == -1)
  {
    perror("Error al hacer fork()");
    exit(1);
  }
  else if (pid == 0)
  {

    close(pipefd[1]); // Cierra el extremo de escritura del pipe
    int received_fd;
    read(pipefd[0], &received_fd, sizeof(received_fd));
    close(pipefd[0]);

    printf("Proceso hijo: Recibí el file descriptor %d\n", received_fd);

    // Mapear la memoria compartida (no usar el fd)
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, received_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
      perror("Error al mapear la memoria compartida en el hijo");
      exit(1);
    }

    printf("Proceso hijo: Memoria compartida mapeada correctamente.\n");
  }
  else
  {
    // Si es el proceso padre este envia el fd al hijo
    close(pipefd[0]); // Cierra el extremo de lectura del pipe
    write(pipefd[1], &fd, sizeof(fd));
    close(pipefd[1]);

    printf("Proceso padre: Envié el file descriptor %d al hijo.\n");

    // Mapear la memoria compartida (no usar el df)
    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
      perror("Error al mapear la memoria compartida en el padre");
      exit(1);
    }

    printf("Proceso padre: Memoria compartida mapeada correctamente.\n");

    wait(NULL); // Esperar el hijo
  }

  return 0;
}

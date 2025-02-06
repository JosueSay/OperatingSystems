/*
Este programa copia el contenido de un archivo de origen a un archivo de destino usando `open()`, `close()`, `read()` y `write()`.
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    fprintf(stderr, "Se deben pasar exactamente 2 parámetros: archivo_origen y archivo_destino.\n");
    return 1;
  }

  // Abrir el archivo de origen
  int descriptorFile = open(argv[1], O_RDONLY);
  if (descriptorFile == -1)
  {
    perror("Error al abrir el archivo de origen");
    return 1;
  }

  // Obtener el tamaño del archivo de origen
  struct stat st;
  if (fstat(descriptorFile, &st) == -1)
  {
    perror("Error al obtener el tamaño del archivo de origen");
    return 1;
  }

  size_t fileSize = st.st_size;

  // Crear un buffer para almacenar el archivo completo
  char *buffer = malloc(fileSize + 1);

  if (buffer == NULL)
  {
    perror("Error al asignar memoria para el buffer");
    return 1;
  }

  // Leer el archivo completo en el buffer
  ssize_t bRead = read(descriptorFile, buffer, fileSize);
  if (bRead == -1)
  {
    perror("Error al leer el archivo de origen");
    return 1;
  }

  buffer[bRead] = '\n'; // Agregar salto de línea al final del contenido

  // printf("Lei %ld bytes del archivo de origen.\n", bRead);

  // Abrir el archivo de destino
  int descriptorDest = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0777);
  if (descriptorDest == -1)
  {
    perror("Error al abrir el archivo de destino");
    return 1;
  }

  // Escribir el contenido del buffer en el archivo de destino
  ssize_t bWrite = write(descriptorDest, buffer, bRead + 1);
  if (bWrite == -1)
  {
    perror("Error al escribir en el archivo de destino");
    return 1;
  }

  // Liberar memoria y cerrar los descriptores
  free(buffer);
  close(descriptorFile);
  close(descriptorDest);

  return 0;
}

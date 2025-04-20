// Referencia:
// 1. https://stackoverflow.com/questions/15598698/why-does-subtracting-0-in-c-result-in-the-number-that-the-char-is-representing
// 2. https://es.stackoverflow.com/questions/271213/c-recorrer-arreglo-bidimensional-usando-punteros

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <omp.h>

#define SIZE 9
#define SUBGRID_SIZE 3

int sudokuGrid[SIZE][SIZE];

// Cargar la grilla Sudoku desde un archivo
void loadSudokuGridFromFile(char *fileData)
{
  for (int i = 0; i < SIZE * SIZE; i++)
  {
    sudokuGrid[i / SIZE][i % SIZE] = fileData[i] - '0';
  }
}

// Imprimir el Sudoku cargado
void printSudoku()
{
  printf("Sudoku Grid:\n");
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      printf("%d ", sudokuGrid[i][j]);
    }
    printf("\n");
  }
}

// Validar si una fila contiene todos los números del 1 al 9
int validateRow(int row)
{
  int seen[SIZE] = {0};
  for (int col = 0; col < SIZE; col++)
  {
    int num = sudokuGrid[row][col];
    if (num < 1 || num > 9 || seen[num - 1]++)
      return 0;
  }
  return 1;
}

// Validar si una columna contiene todos los números del 1 al 9
int validateColumn(int col)
{
  int seen[SIZE] = {0};
  for (int row = 0; row < SIZE; row++)
  {
    int num = sudokuGrid[row][col];
    if (num < 1 || num > 9 || seen[num - 1]++)
      return 0;
  }
  return 1;
}

// Validar si un subarreglo 3x3 contiene todos los números del 1 al 9
int validateSubgrid(int startRow, int startCol)
{
  int seen[SIZE] = {0};
  for (int i = 0; i < SUBGRID_SIZE; i++)
  {
    for (int j = 0; j < SUBGRID_SIZE; j++)
    {
      int num = sudokuGrid[startRow + i][startCol + j];
      if (num < 1 || num > 9 || seen[num - 1]++)
        return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[])
{
  pid_t pid;
  char pid_str[10];

  if (argc < 2)
  {
    printf("\033[1;33mNota:\033[0m el programa se debe utilizar como \033[1;36m%s <archivo_sudoku>\033[0m\n", argv[0]);
    return 1;
  }

  int dp_fsudoku = open(argv[1], O_RDONLY);
  if (dp_fsudoku == -1)
  {
    perror("No se pudo abrir el archivo");
    return 1;
  }

  char *fileData = mmap(NULL, SIZE * SIZE, PROT_READ, MAP_PRIVATE, dp_fsudoku, 0);
  if (fileData == MAP_FAILED)
  {
    perror("Error en mmap");
    close(dp_fsudoku);
    return 1;
  }

  // Llenar la grilla Sudoku desde el archivo y mostrar el proceso que lo hizo
  loadSudokuGridFromFile(fileData);
  printf("PID del proceso: %d\n", getpid());

  pid = fork();

  if (pid > 0)
  {
    pthread_t thread_col;
    int columnas_validas = 1;

    // Función del hilo que valida columnas
    void *threadValidateColumns(void *arg)
    {
      int *result = (int *)arg;
      int local_result = 1;
      printf("El thread que ejecuta el método para ejecutar la revisión de columnas es: %ld\n", syscall(SYS_gettid));
      int i;

#pragma omp parallel for private(i) reduction(&& : local_result)
      for (int i = 0; i < SIZE; i++)
      {
        if (!validateColumn(i))
          local_result = 0;

        printf("Thread en ejecución durante validación de columnas: %ld\n", syscall(SYS_gettid));
      }

      *result = local_result;
      pthread_exit(0);
    }

    // Crear thread u esérar a que termine
    pthread_create(&thread_col, NULL, threadValidateColumns, &columnas_validas);
    pthread_join(thread_col, NULL);
    printf("El thread en el que se ejecuta main es: %ld\n", syscall(SYS_gettid));

    // Esperar al hijo que ejecutó ps
    wait(NULL);

    // Validar filas
    int filas_validas = 1;
    int i;
#pragma omp parallel for private(i) reduction(&& : filas_validas)
    for (int i = 0; i < SIZE; i++)
    {
      if (!validateRow(i))
        filas_validas = 0;
    }

    // Validar subarreglo
    int subgrids_validos = 1;
    int j;
#pragma omp parallel for collapse(2) private(i, j) reduction(&& : subgrids_validos)
    for (int i = 0; i < SIZE; i += 3)
    {
      for (int j = 0; j < SIZE; j += 3)
      {
        if (!validateSubgrid(i, j))
          subgrids_validos = 0;
      }
    }

    if (filas_validas && columnas_validas && subgrids_validos)
      printf("Sudoku resuelto!\n");
    else
      printf("Sudoku inválido.\n");

    // Segundo fork para ejecutar ps de nuevo
    printf("Antes de terminar el estado del proceso y sus threads:\n");
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
      char pid_str[10];
      snprintf(pid_str, sizeof(pid_str), "%d", getppid());
      execlp("ps", "ps", "-p", pid_str, "-lLf", (char *)NULL);
      perror("execlp falló");
      exit(1);
    }
    else if (pid2 > 0)
    {
      wait(NULL);
    }
  }
  else if (pid == 0)
  {
    // Hijo
    snprintf(pid_str, sizeof(pid_str), "%d", getppid());
    execlp("ps", "ps", "-p", pid_str, "-lLf", (char *)NULL);
    perror("execlp falló");
    exit(1);
  }
  else
  {
    perror("Error al hacer fork");
    exit(1);
  }

  printSudoku();

  munmap(fileData, SIZE * SIZE);
  close(dp_fsudoku);
  return 0;
}
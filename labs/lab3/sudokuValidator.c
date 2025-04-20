// Referencia:
// 1. https://stackoverflow.com/questions/15598698/why-does-subtracting-0-in-c-result-in-the-number-that-the-char-is-representing
// 2. https://es.stackoverflow.com/questions/271213/c-recorrer-arreglo-bidimensional-usando-punteros

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

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

  // Llenar la grilla Sudoku desde el archivo
  loadSudokuGridFromFile(fileData);

  // Mostrar la grilla cargada
  printSudoku();

  munmap(fileData, SIZE * SIZE);
  close(dp_fsudoku);
  return 0;
}

# Ejercicio 1

## Parte a

**El código está en el archivo `a.c`.**

```bash
cd .\labs\lab1\ejer1\
```

### Explicación

- **`#include`**: Permite importar código de bibliotecas externas. En este caso, `stdio.h` se usa para operaciones de entrada y salida, y `unistd.h` para el manejo de procesos y llamadas al sistema.
- **Compilación**: Los archivos `.c` se convierten en código objeto `.o` o ejecutables `.exe`, y el **linker** une estos archivos para crear el ejecutable.
- **`main`**: Es el punto de entrada del programa, el retorno es obligado y el valor 0 para ejecución exitosa y != 0 para ejecución NO exitosa.
- **`printf`**: Imprime texto en la salida estándar.
- **`getpid()`**: Obtiene el identificador del proceso (PID) actual.

## Parte b

**El código está en el archivo `b.c`.**

```bash
cd .\labs\lab1\ejer1\
```

### Explicación

#### Fork

`fork()` crea un nuevo proceso.

- El **proceso padre** recibe el PID del hijo.
- El **proceso hijo** recibe `0`, indicando que es hijo.

```c
int pFork = fork();
if (pFork != 0) {
    // Código del padre
} else {
    // Código del hijo
}
```

#### Exec

`exec` reemplaza el proceso actual por otro programa.

##### Sintaxis de `execl`

```c

/*
  El arg puede ser opcional ya que el ejecutable que manda a llamar no necesita un arg pero para evitar
  warnings en consola se agregó como buena práctica el mismo nombre del ejecutable.
*/

int execl(const char *path, const char *arg0, ..., (char *)NULL);
```

## Parte c

Se compilaron los dos archivos c:

```bash
gcc a.c -o a.exe
gcc b.c -o b.exe
```

Se ejecutaron los archivos correspondientes:

```bash
./a.exe
./b.exe
```

- **¿Por qué aparecen números diferentes al ejecutar el primer programa varias veces?**
  - ![Ejecución Programa 1a](../images/ejecucion_part1a.png "Ejecución Programa 1a")
  - Cada ejecución recibe un PID único asignado por el sistema.

- **¿Por qué aparecen dos números distintos en el segundo programa?**
  - ![Ejecución Programa 1b](../images/ejecucion_part1b.png "Ejecución Programa 1b")
  - `fork()` crea un proceso hijo que ejecuta el mismo código que el padre.

- **¿Por qué el primer y segundo número son iguales?**
  - El mismo proceso imprime su PID antes y después de `execl()`.

- **¿Para qué sirve el proceso con PID 1 en [`top`](https://vagga-readthedocs-io.translate.goog/en/latest/pid1mode.html?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=sge#:~:text=%C2%BFQu%C3%A9%20tiene%20de%20especial%20el,tienen%20una%20para%20PID%201.)?**
  - ![Comando top](../images/comando_top.png "Comando top")
  - Es el primer proceso iniciado por el kernel y adopta procesos huérfanos; además si el PID 1 muere, todos los demás procesos también lo harán.

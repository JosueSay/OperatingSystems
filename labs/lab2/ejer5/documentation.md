# Documentación Adicional

## Enlaces

1. [**Parámetros como argumentos**](https://platzi.com/tutoriales/1740-lenguaje-c-2019/5915-entendiendo-la-estructura-de-int-mainint-argh-char-argh/)
2. [**Conversión de enteros**](https://es.stackoverflow.com/questions/581608/c%C3%B3mo-convertir-char-de-varios-caracteres-a-int-y-float-en-c)
3. [**Memoria compartida**](https://www-cs-unibo-it.translate.goog/~sacerdot/doc/C/corso2/node27.html?_x_tr_sch=http&_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=sge#:~:text=h%20%3E.-,C%C3%B3mo%20acceder%20a%20un%20segmento%20de%20memoria%20compartida,(0);%20%7D%20...)

## Pasar Parámetros

Los siguientes parámetros son necesarios cuando se desean enviar argumentos al código a ejecutar:

```c
int main(int argc, char *argv[])
```

- **int argc** (argument count) es el contador de argumentos. Contiene la cantidad total de argumentos pasados a la función, incluyendo el nombre del programa (en este caso, `./archivi.o`), que se cuenta como el primer argumento.

- **char *argv[]** (argument vector) es un arreglo de cadenas de caracteres (strings) que apunta a los espacios de memoria donde se almacenan los argumentos pasados al programa.

Por lo tanto, si se quieren pasar dos parámetros, donde el primero (`n`) es un número y el segundo (`x`) es una letra, se utilizaría el siguiente código:

```c
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int n = atoi(argv[1]);
  char x = argv[2][0];

  return 0;
}
```

> **Nota:** Para `x`, se utiliza `argv[2][0]` porque se quiere obtener el primer carácter del segundo parámetro, que es una letra. Es importante recordar que, en C, todos los parámetros pasados al `main` están terminados por un carácter `null` (`'\0'`). Esto significa que si se pasa una letra, el `main` recibirá la cadena `"a\0"`. Como solo nos interesa la letra misma, se obtiene el primer carácter de esa cadena (`argv[2][0]`).
>
> En los enlaces se muestra cómo convertir un valor a entero utilizando la librería `stdlib.h` para asegurar que el contenido de `n` sea un número entero.

## IPC: Memoria Compartida

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Abrir espacio de memoria compartida
    int shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Error al abrir la memoria compartida");
        exit(1);
    }

    // Enviar el file descriptor a la otra instancia (por ejemplo, mediante un pipe)
    printf("File descriptor de memoria compartida: %d\n", shmid);

    // Aquí, deberías implementar el código para enviar el file descriptor
    // a la otra instancia, quizás mediante un pipe o socket.

    // Mapeo de la memoria compartida, pero no debes usar el file descriptor aquí.
    // Lo puedes hacer solo para usar los datos en memoria.

    return 0;
}
```

### Memoria Compartida

La memoria compartida es una técnica que permite que varios procesos accedan a la misma región de memoria, de manera que puedan compartir datos.

### Abrir un Espacio Para Memoria Compartida

Se usan funciones como `shmget()` y `shmat()`, que están en la biblioteca `sys/shm.h`.

- **`shmget()`**: Crea o abre un segmento de memoria compartida.
- **`shmat()`**: Mapea el segmento de memoria compartida a la memoria de tu proceso.

#### Mapear

**Mapear** en este contexto significa **asociar** un segmento de memoria compartida con la memoria de tu proceso, de modo que un proceso pueda leer o escribir directamente en esa área. Usando **`shmat()`**, se "mapea" la memoria compartida al espacio de memoria, lo que te permite trabajar con ella como si fuera una variable normal.

**¿Para qué sirve?**  
Te permite acceder a datos en memoria compartida entre varios procesos de manera rápida y eficiente, sin tener que pasar información entre ellos de otra forma.

Es como si el archivo (o memoria compartida) fuera un gran espacio y, al **mapear**, le **asignas** una parte de ese espacio a un proceso A, de modo que pueda acceder y manipular esos datos directamente. Es como darle al proceso A una **ventana** para que vea y trabaje con una parte del archivo o memoria.

Entonces:

- El **archivo o la memoria compartida** es como un recurso grande.
- Al **mapear**, se hace que **el proceso A pueda acceder a una porción específica** de ese recurso, como si estuviera trabajando con su propia memoria.

#### ¿Cómo se sabe si ya fue abierto por otro proceso?

Cuando se usa`shmget()`, si el segmento ya existe, devolverá un file descriptor de ese segmento. Si la memoria no existe, este retorna `-1` en caso no se haya programado un evento para crearlo en caso de que no exista

¿Esto que tiene que ver si el proceso si el segmento fue abierto? se sabe que si la función anterior devuelve un número entonces significa que fue abierto por un proceso.

### File Descriptor

Un file descriptor es un número entero que el sistema operativo utiliza para identificar archivos abiertos (o áreas de memoria compartida). Sirve como un  "pase" que permite acceder a un recurso abierto, como un archivo o un segmento de memoria.

CCuando se abre un archivo o un segmento de memoria en un programa, el sistema operativo te retorna un file descriptor. Con este descriptor, se puede leer, escribir o manipular ese recurso.

### Enviar File Descriptor a otra Instancia

Para enviar el file descriptor a otra instancia del programa, se puede usar mecanismos como **pipes** o **sockets**. Uno de los procesos creará la memoria compartida y el otro la recibirá usando el descriptor. Se debe enviar este descriptor (como un número entero) a través de algún canal de comunicación.

Dado que se pasa el File Descriptor por un medio de comunicación, significa que no se debe utilizar el file descriptor directamente para acceder a la memoria compartida a través de funciones como `shmat()`. El file descriptor se utiliza solo para identificar el segmento de memoria, pero no se debe usar para leer o escribir en él.

Es decir que solo se use el file descriptor como un identificador y no como un medio para acceder directamente a la memoria compartida en ese proceso.

#### Mostrar en Pantalla el evento

Dado que el otro proceso recibió el file descriptor, este podría mostrarlo en pantalla con un imprimir en la pantalla usando `printf()`.

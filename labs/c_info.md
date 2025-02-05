# 🖥️ Lenguaje C

El lenguaje **C** es un lenguaje de programación que sigue los paradigmas **imperativo** y **procedural**. Es ampliamente utilizado debido a su eficiencia y control sobre los recursos del sistema.

## 🔹 Paradigmas de C

### 🔧 Imperativo

En este paradigma, la ejecución de una secuencia de instrucciones modifica el estado del programa.

```c
int x = 10;
x = x + 5;  // Se modifica el valor de x
```

### 🔄 Procedural

El código se organiza en funciones para mejorar la estructura y la reutilización, facilitando el mantenimiento y la modularidad del programa.

```c
#include <stdio.h>

void saludo() {
    printf("¡Hola, mundo!\n");
}

int main() {
    saludo();
    return 0;
}
```

## 🖥️ Llamadas a Sistemas

### 🔀 [Fork](https://campusvirtual.ull.es/ocw/pluginfile.php/2173/mod_resource/content/0/perlexamples/node66.html#:~:text=Cuando%20se%20llama%20la%20funci%C3%B3n,un%20cero%20al%20proceso%20hijo.)

`fork` es una llamada al sistema que permite crear un nuevo proceso.

#### ⚙️ Funcionamiento

Un proceso ejecuta un bloque de código, y a este proceso se le denomina **proceso padre** (o proceso original). Cuando el proceso padre llama a `fork()`, lo que ocurre es que se crea un **nuevo proceso** llamado **proceso hijo**, que es un clon del padre. La función `fork()` devuelve dos valores distintos dependiendo de si está en el proceso padre o en el hijo.

- En el **proceso padre**, `fork()` devuelve el **PID del hijo**.
- En el **proceso hijo**, `fork()` devuelve **0**, lo que indica que es el proceso hijo.

Es importante aclarar que, en este contexto, el término "padre" se refiere al proceso original que realizó el `fork()`, pero el proceso hijo también puede actuar como "padre" si, a su vez, realiza un `fork()`.

#### 🔄 Flujo de ejecución

Después de la llamada a `fork()`, ambos procesos, el **padre** y el **hijo**, continuarán ejecutando el código a partir del punto en que se hizo la bifurcación. Sin embargo, hay una distinción clave: el **padre** recibe el PID del hijo, mientras que el **hijo** recibe un 0 como valor para indicar que es hijo. Esto se refleja en el siguiente código:

```c
  int pFork = fork();

  if (pFork != 0) {
    // Instrucciones del proceso padre
  } else {
    // Instrucciones del proceso hijo
  }
```

#### 📌 Ejemplo con procesos

Imaginemos un proceso original **A** con un PID de ejemplo `1`. Al ejecutar `fork()`, este crea un nuevo proceso **B** con un PID de ejemplo `2`. En este caso, el valor retornado por `fork()` se almacena en la variable `pFork`.

- En el **proceso padre (A)**, `pFork` será `2` (el PID del hijo).
- En el **proceso hijo (B)**, `pFork` será `0` (indicando que es un hijo).

Es importante notar que, aunque el hijo tiene un retorno del fork, el hijo **no ejecutó el `fork()`**. El `fork()` es único, pero se comporta de manera diferente en cada proceso: el padre obtiene el PID del hijo, y el hijo obtiene el 0.

#### 👶 El hijo puede ser también "padre"

Para que el proceso hijo (B) sea considerado "padre", debe realizar su propio `fork()`, creando un nuevo proceso (C). Este nuevo proceso será un **nieto** del proceso original **A**, pero **B** actuará como su "padre" en este contexto. Así, el proceso **A** es el abuelo de **C**.

### 🚀 [Exec](https://www.geeksforgeeks.org/exec-family-of-functions-in-c/)

`exec` es una llamada al sistema que permite a un proceso ejecutar otro programa, reemplazando el proceso original con el nuevo.

Una variante de `exec` es `execl`, que ejecuta un programa externo con la misma lógica de `exec`. La principal diferencia entre estas funciones radica en la forma en que se pasan los parámetros.

#### 📝 Sintaxis de `execl`

```c
int execl(const char *path, const char *arg0, ..., (char *)NULL);
```

## Open

## Close

## Read

## Write

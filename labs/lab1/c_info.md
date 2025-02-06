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

### [Close - Open - Read - Write](https://pasky.wordpress.com/2009/08/04/funciones-openclose-y-readwrite-en-c/)

> Nota: El descriptor es la referencia al archivo abierto que asigna el kernel.

#### 🔹 Open

Es una llamada a sistema que abre un archivo, este necesita la libreria `fcntl.h`.

##### 📌 **Sintaxis:**

```c
#include <fcntl.h>
#include <unistd.h>

int open(const char *pathname, int flags, mode_t mode);
```

##### 📌 **Descripción:**

- **`pathname`**: Ruta del archivo que se desea abrir.
- **`flags`**: Modos de apertura del archivo.
- **`mode`** *(opcional)*: Permisos del archivo si se crea uno nuevo (cuando se usa `O_CREAT`).

##### 📌 **Valor de retorno:**

- Devuelve un **descriptor de archivo** (un entero) si tiene éxito.
- Devuelve `-1` en caso de error y establece `errno` con el código de error.

##### 🔹 **Flags de `open()`**

Las **flags** determinan cómo se abre el archivo. Se pueden combinar usando `|`.

##### 📌 **Modos de apertura:**

| Flag            | Descripción |
|----------------|------------|
| `O_RDONLY`     | Solo lectura. |
| `O_WRONLY`     | Solo escritura. |
| `O_RDWR`       | Lectura y escritura. |

##### 📌 **Opciones adicionales:**

| Flag             | Descripción |
|-----------------|------------|
| `O_CREAT`       | Crea el archivo si no existe (requiere `mode`). |
| `O_TRUNC`       | Si el archivo existe y es de escritura, lo vacía. |
| `O_APPEND`      | Escribe al final del archivo sin sobrescribir. |
| `O_EXCL`        | Falla si el archivo ya existe (se usa con `O_CREAT`). |
| `O_NONBLOCK`    | Modo no bloqueante. |

---

#### 🔹 Close

Es una llamada a sistema que cierra un archivo, este necesita la libreria `unistd.h`.

##### 📌 **Sintaxis:**

```c
#include <unistd.h>

int close(int fd);
```

##### 📌 **Descripción:**

- **`fd`**: Descriptor del archivo a cerrar.

##### 📌 **Valor de retorno:**

- Devuelve `0` si se cierra correctamente.
- Devuelve `-1` en caso de error y establece `errno`.

Si un archivo se abre y **no se cierra**, pueden ocurrir varias cosas dependiendo del sistema operativo y del contexto del programa. Vamos a analizar diferentes escenarios.  

---

#### 🔹 **¿Qué pasa si se abre un archivo y no se cierra?**

1. **Fuga de descriptores de archivo:**  
   - Cada archivo abierto consume un descriptor de archivo del sistema.  
   - Si un programa abre muchos archivos sin cerrarlos, se puede alcanzar el **límite de descriptores** y el sistema ya no permitirá abrir más archivos.  
   - Esto puede hacer que el programa o incluso el sistema dejen de funcionar correctamente.

2. **Uso innecesario de recursos del sistema:**  
   - Mantener un archivo abierto ocupa memoria y recursos del sistema operativo.  
   - En programas de larga duración, esto puede reducir el rendimiento.

3. **Bloqueo de archivos:**  
   - En algunos sistemas, si un archivo es abierto con ciertos flags (como `O_WRONLY` o `O_RDWR`), otros procesos pueden no poder modificarlo hasta que se cierre.  
   - Si el archivo nunca se cierra, otros procesos pueden quedar bloqueados.

---

#### 🔹 **¿Qué pasa si hay un error al cerrar un archivo?**

La función `close(fd)` devuelve `-1` si ocurre un error, y se puede revisar `errno` para saber la causa.

##### 📌 **Ejemplo de manejo de errores al cerrar un archivo:**

```c
if (close(fd) == -1) {
    perror("Error al cerrar el archivo");
}
```

##### 📌 **Posibles errores (`errno`):**

| Código de error | Descripción |
|---------------|------------|
| `EBADF`      | `fd` no es un descriptor de archivo válido. |
| `EIO`        | Error de entrada/salida al cerrar. |
| `EINTR`      | Se interrumpió la llamada antes de cerrar. |

Si `close()` falla, puede que el sistema operativo aún mantenga el archivo abierto hasta que el programa termine.

---

#### 🔹 **¿Qué pasa si el programa termina antes de cerrar el archivo?**

1. **El sistema cierra automáticamente los archivos:**  
   - En la mayoría de los sistemas operativos, cuando un programa finaliza, el kernel **cierra automáticamente** todos los descriptores de archivo abiertos por el proceso.  
   - Sin embargo, esto **no es una buena práctica** porque:
     - Puede provocar **pérdida de datos** si el sistema no ha sincronizado la escritura en disco.
     - Puede afectar a otros procesos que intentan acceder al archivo.

2. **Posible corrupción de datos:**  
   - Si un archivo estaba en proceso de escritura y el programa termina abruptamente, los datos pueden quedar corruptos o incompletos.

3. **Archivos temporales bloqueados:**  
   - En algunos sistemas, si un programa usa archivos temporales y no los cierra, pueden quedar bloqueados hasta que el sistema libere la memoria.

---

#### 🔹 **Buenas prácticas**

- **Siempre cerrar los archivos con `close(fd);`**  
- **Comprobar errores al cerrar con `if (close(fd) == -1) perror(...);`**  
- **Usar `fsync(fd);` para asegurar que los datos se guarden antes de cerrar (para evitar pérdida de datos).**  

---

#### 🔹 **Ejemplo completo con manejo de errores**

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("archivo.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    if (write(fd, "Hola, mundo\n", 12) == -1) {
        perror("Error al escribir en el archivo");
    }

    // Sincronizar datos antes de cerrar
    if (fsync(fd) == -1) {
        perror("Error al sincronizar datos");
    }

    // Cerrar el archivo correctamente
    if (close(fd) == -1) {
        perror("Error al cerrar el archivo");
    }

    return 0;
}
```

#### 🔹 Read

Son llamadas a sistema que se usan para leer archivos.

##### 📌 **Sintaxis:**

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

##### 📌 **Descripción:**

- **`fd`**: Descriptor de archivo desde el que se lee.
- **`buf`**: Buffer donde se almacenarán los datos leídos.
- **`count`**: Número máximo de bytes que se desean leer.

##### 📌 **Valor de retorno:**

- **Éxito**: Devuelve el número de bytes leídos.
- **Error**: Devuelve `-1` y establece `errno` con el código de error.

---

#### 🔹 **Errores comunes al usar `read()`**

Si `read()` falla, devuelve `-1` y configura `errno` para indicar el error.

##### 📌 **Posibles errores (`errno`) al usar `read()`**

| Código de error | Descripción |
|----------------|------------|
| `EBADF`        | El descriptor de archivo no es válido. |
| `EFAULT`       | `buf` apunta a una dirección de memoria incorrecta. |
| `EINVAL`       | El valor de `count` es inválido. |
| `EIO`           | Error de entrada/salida al leer. |
| `EAGAIN`       | El descriptor de archivo está en modo no bloqueante, y no hay datos disponibles. |

---

#### 🔹 Write

##### 📌 **Sintaxis:**

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

##### 📌 **Descripción:**

- **`fd`**: Descriptor de archivo donde se va a escribir.
- **`buf`**: Buffer que contiene los datos a escribir.
- **`count`**: Número de bytes a escribir.

##### 📌 **Valor de retorno:**

- **Éxito**: Devuelve el número de bytes escritos.
- **Error**: Devuelve `-1` y establece `errno` con el código de error.

#### 🔹 **Errores comunes al usar `write()`**

Si `write()` falla, devuelve `-1` y configura `errno`.

##### 📌 **Posibles errores (`errno`) al usar `write()`**

| Código de error | Descripción |
|----------------|------------|
| `EBADF`        | El descriptor de archivo no es válido. |
| `EFAULT`       | `buf` apunta a una dirección de memoria incorrecta. |
| `EINVAL`       | El valor de `count` es inválido. |
| `EIO`           | Error de entrada/salida al escribir. |
| `EAGAIN`       | El descriptor de archivo está en modo no bloqueante y no puede escribir. |

---

#### 🔹 **¿Qué pasa si no se usan correctamente `read()` o `write()`?**

##### 📌 **No leer o escribir correctamente puede tener varios efectos:**

1. **Lectura incompleta o errónea:**
   - Si no se maneja adecuadamente el número de bytes leídos, puedes obtener datos parciales o incorrectos.
   - Si el buffer no es lo suficientemente grande para almacenar la cantidad de datos a leer, se perderán datos.

2. **No escribir correctamente:**
   - Si no se verifica cuántos bytes se escribieron, puede que no se escriban todos los datos del buffer.
   - Si el archivo se encuentra en modo no bloqueante y no se pueden escribir todos los datos en un solo intento, es posible que algunos bytes no se escriban.

---

#### 🔹 **¿Qué pasa si hay un error durante la lectura o escritura?**

1. **En caso de error en `read()` o `write()`, ambas funciones devuelven `-1`.**  
   El código de error específico estará disponible en `errno`, y se recomienda **siempre** manejar los errores adecuadamente.

2. **El programa debería verificar el retorno de estas funciones** y, si se produce un error, debe tomar las medidas adecuadas (como liberar recursos o informar al usuario).

3. **Si el programa termina antes de completar una operación de lectura o escritura**, los datos pueden quedar incompletos o corrompidos.  
   Los descriptores de archivo abiertos se cierran automáticamente al finalizar el programa, pero los datos pendientes pueden perderse si no se han guardado correctamente.

---

#### 🔹 **Buenas prácticas**

- Siempre verificar el retorno de `read()` y `write()` para manejar posibles errores.
- Asegurarse de que el número de bytes escritos o leídos es el esperado.
- Usar `fsync(fd)` para asegurarse de que los datos se guardan en el disco antes de cerrar el archivo.
- Si el archivo se encuentra en modo no bloqueante, puede ser necesario realizar la operación en varias etapas.

Aquí tienes el código mejorado para incluir tanto la lectura como la escritura en el archivo:

#### 📌 **Ejemplo: Open - Close - Read - Write**

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Abrimos el archivo en modo lectura y escritura
    int fd = open("archivo.txt", O_CREAT | O_RDWR, 0644);  // Crear o abrir para lectura y escritura
    if (fd == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    // Escribimos en el archivo
    write(fd, "Hola, mundo\n", 12);  // Escribimos "Hola, mundo" en el archivo

    // Volver al principio del archivo para leerlo
    lseek(fd, 0, SEEK_SET);  // Desplazamos el puntero de lectura/escritura al inicio del archivo
    
    // Leemos desde el archivo
    char buffer[128];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);  // Leemos los datos
    if (bytes_read == -1) {
        perror("Error al leer el archivo");
        close(fd);
        return 1;
    }
    
    // Añadimos un terminador nulo para imprimir la cadena
    buffer[bytes_read] = '\0';
    printf("Contenido leído: %s", buffer);  // Mostramos el contenido leído
    
    close(fd);  // Cerramos el archivo
    return 0;
}
```

📌 **Explicación del ejemplo:**

- Usamos `O_CREAT | O_RDWR` para crear el archivo si no existe y abrirlo en modo de lectura y escritura.
- `0644` define permisos de lectura/escritura para el propietario y solo lectura para otros.
- Primero, escribimos "Hola, mundo" en el archivo.
- Luego, usamos `lseek()` para volver al inicio del archivo antes de leerlo.
- Se lee el contenido del archivo usando `read()` y se muestra por pantalla.
- Finalmente, cerramos el archivo con `close()`.

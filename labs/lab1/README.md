# Lab01 - Uso de C

## Ejercicio 1 - Parte a

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

## Ejercicio 1 - Parte b

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

## Ejercicio 1 - Parte c

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
  - ![Ejecución Programa 1a](./images/ejecucion_part1a.png "Ejecución Programa 1a")
  - Cada ejecución recibe un PID único asignado por el sistema.

- **¿Por qué aparecen dos números distintos en el segundo programa?**
  - ![Ejecución Programa 1b](./images/ejecucion_part1b.png "Ejecución Programa 1b")
  - `fork()` crea un proceso hijo que ejecuta el mismo código que el padre.

- **¿Por qué el primer y segundo número son iguales?**
  - El mismo proceso imprime su PID antes y después de `execl()`.

- **¿Para qué sirve el proceso con PID 1 en [`top`](https://vagga-readthedocs-io.translate.goog/en/latest/pid1mode.html?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=sge#:~:text=%C2%BFQu%C3%A9%20tiene%20de%20especial%20el,tienen%20una%20para%20PID%201.)?**
  - ![Comando top](./images/comando_top.png "Comando top")
  - Es el primer proceso iniciado por el kernel y adopta procesos huérfanos; además si el PID 1 muere, todos los demás procesos también lo harán.

## Ejercicio 2 - Parte a

| Función | Descripción |
|---------|------------|
| `open()`  | Abre o crea un archivo. |
| `close()` | Cierra un archivo. |
| `read()`  | Lee datos desde un archivo. |
| `write()` | Escribe datos en un archivo. |

>**Nota:** La investigación mas detallada esta en el archivo `documentation_c.md`.

## Ejercicio 2 - Parte b

**El código está en el archivo `b.c`.**

```bash
cd .\labs\lab1\ejer2\
gcc .\b.c -o b.exe
.\b.exe origen.txt destino.txt
```

![Ejecución Programa 2a](./images/ejecucion_part2b.png "Ejecución Programa 2a")

![Ejecución2 Programa 2a](./images/ejecucion2_part2b.png "Ejecución2 Programa 2a")

### Explicación

1. **Verificación de argumentos:**  
   - El programa requiere dos argumentos: `archivo_origen` y `archivo_destino`.  
   - Si no se proporcionan, muestra un mensaje de error y termina.  

2. **Abrir el archivo de origen:**  
   - `open(argv[1], O_RDONLY)`: Abre el archivo en modo solo lectura.  
   - Si falla, se muestra un error.  

3. **Obtener tamaño del archivo:**  
   - `fstat(descriptorFile, &st)`: Llena la estructura `stat` con información del archivo.  
   - `st.st_size`: Contiene el tamaño del archivo en bytes.  

4. **Asignación de memoria:**  
   - `malloc(fileSize + 2)`: Reserva memoria para almacenar el contenido del archivo más un `\n`.  
   - Si `malloc` falla, muestra un error y termina.  

5. **Leer el contenido del archivo:**  
   - `read(descriptorFile, buffer, fileSize)`: Carga el contenido en `buffer`.  
   - Si falla, se muestra un error.  
   - Se agrega un salto de línea `buffer[bRead] = '\n';`.  

6. **Abrir el archivo de destino:**  
   - `open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0777)`:  
     - `O_WRONLY`: Modo escritura.  
     - `O_CREAT`: Crea el archivo si no existe.  
     - `O_APPEND`: Agrega contenido al final del archivo.  
     - `0777`: Permisos de lectura, escritura y ejecución para todos.  

7. **Escribir en el archivo de destino:**  
   - `write(descriptorDest, buffer, bRead + 1)`: Escribe el contenido leído más el salto de línea.  
   - Si falla, muestra un error.  

8. **Liberar recursos:**  
   - `free(buffer)`: Libera la memoria asignada.  
   - `close(descriptorFile)`: Cierra el archivo de origen.  
   - `close(descriptorDest)`: Cierra el archivo de destino.  

## Ejercicio 2 - Parte c

### [¿Qué es Strace?](https://wiki.ubuntu.com/Strace)

Comandos para rastrear llamadas a sistemas y señales de un proceso para depurar y analizar como se comporta un programa a nivel de sistema operativo.

### Instalando `strace`

```bash
sudo apt update
sudo apt upgrade
sudo apt-get install strace
```

![Instalacióon de strace](./images/instalacion_strace.png "Instalacióon de strace")

## Ejercicio 2 - Parte d

Ejecute los siguientes comandos:

```bash
cd .\labs\lab1\ejer2\
gcc .\b.c -o b.o
strace ./b.o origen.txt destino.txt | tee logB.txt
```

### Observaciones

1. **Resultado del comando `strace`**  
   Se observará el retorno del comando `strace`, el archivo modificado `destino.txt` y el `logB.txt` para ver el resultado de la instrucción `strace`.

2. **Verificación y compilación de archivos**  

   ![Verificando Archivos](./images/verificando_archivos.png "Verificando Archivos")

3. **Ejecución de la instrucción `strace`**  

   ![Ejecutando Instrucción Strace](./images/ejeucion_strace.png "Ejecutando Instrucción Strace")

4. **Resultado del archivo destino**  

   ![Resultado Archivo Destino](./images/archivo_destino.png "Resultado Archivo Destino")

### [Preguntas](https://opensource.com/article/19/10/strace)

1. **Primera llamada a `execve`**  
   - ¿Por qué la primera llamada que aparece es `execve`?

      ```bash
      execve("./b.o", ["./b.o", "origen.txt", "destino.txt"], 0x7ffeeb54dbe0 /* 48 vars */) = 0
      ```

      - **R:** [`execve`](https://www.quora.com/What-is-the-execve-system-call-in-the-C-programming-language) es una llamada a sistema para ejecutar un nuevo programa, en lugar de ejecutar el programa directamente, lo que se hace es ejecutarlo a través de strace. Esto implica que strace se encarga de rastrear las llamadas al sistema que realiza el programa durante su ejecución; entre sus argumentos está la path del archivo objeto, nombre del archivo objeto y los argumentos para su ejecución.

2. **Llamadas de sistema realizadas por usted**  
   - Ubique las llamadas de sistema que ha realizado.  

      ```bash
      openat(AT_FDCWD, "origen.txt", O_RDONLY) = 3
      fstat(3, {st_mode=S_IFREG|0664, st_size=26, ...}) = 0
      ...
      read(3, "Hola mundo esto es ORIGEN.", 26) = 26
      openat(AT_FDCWD, "destino.txt", O_WRONLY|O_CREAT|O_APPEND, 0777) = 4
      write(4, "Hola mundo esto es ORIGEN.\n", 27) = 27
      close(3)                                = 0
      close(4)                                = 0
      ```

   - ¿Qué significan los resultados (números que aparecen después del signo `=`)?

      - **R:** Es el valor de retorno de la llamada a sistema. Como se menciono en `documentation_c.md` las llamadas a sistemas tienen diferentes retornos dependiendo de lo que ocurrió:

      | **Función** | **Valor de retorno** |
      |-------------|----------------------|
      | `open()`    | Un entero (descriptor de archivo) si tuvo éxito, `-1` en caso de error |
      | `fstat()`   | `0` si tuvo éxito, `-1` si hubo un error |
      | `read()`    | La cantidad de bytes leídos si tuvo éxito, `-1` en caso de error |
      | `write()`   | La cantidad de bytes escritos si tuvo éxito, `-1` en caso de error |
      | `close()`   | `0` si se cerró correctamente el archivo, `-1` si hubo un error |

3. **Llamada `read` vacía**  
   - ¿Por qué entre las llamadas realizadas por usted hay una llamada `read` sin datos?
      - **R:** No hay ninguna llamada `read` vacía en el trace. Supondría una lectura sin datos en caso existiera algo como `read(3, "", 0) = 0` ocurriendo al final del archivo porque ya leyó todos los datos.

4. **Servicios del sistema operativo identificados en el `strace`**  

   - **1. Gestión de memoria**
      - **Llamadas a sistema**: `brk`, `mmap`, `mprotect`, `munmap`.  
      - **Descripción**: El sistema operativo asigna y gestiona la memoria para la ejecución del programa. Las funciones `brk` y `mmap` permiten gestionar la memoria dinámica y el mapeo de archivos o bibliotecas en la memoria del proceso.

      **Ejemplo**:

      - **1. `brk()`**
         - **Descripción**:
            - **`brk(NULL)`** → Obtiene la dirección actual del final del heap.
            - **`brk(nueva_direccion)`** → Ajusta el límite superior del heap, expandiendo o reduciendo la memoria disponible.

         - **Ejemplo en el `strace`**:

            ```bash
            brk(NULL) = 0x5d510f0c4000
            brk(0x5d510f0e5000) = 0x5d510f0e5000
            ```

            - `brk()` se usa para gestionar la región de **heap**, el área de memoria dinámica donde se asignan bloques de memoria con funciones como `malloc()`, `calloc()` y `realloc()`.
            - **`brk(NULL)`** consulta el final actual del heap, mientras que **`brk(0x5d510f0e5000)`** ajusta el límite superior del heap para permitir la asignación de más memoria, que podría ser usada por `malloc()` para asignar memoria dinámica.

      - **2. `mmap()`**
         - **Descripción**:  
            - Reserva una región de memoria en el espacio de direcciones del proceso. Se utiliza para:
            - Asignación de memoria anónima (sin respaldo en archivos).
            - Mapeo de archivos en memoria (por ejemplo, bibliotecas compartidas).
            - Creación de stack y heap dinámicos.

         - **Ejemplo en el `strace`**:

            ```bash
            mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7eba39f91000
            mmap(NULL, 2227672, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7eba39c00000
            ```

            - La primera llamada a `mmap()` reserva 8192 bytes de memoria anónima para su uso en el programa. Esto se usa para la asignación de memoria dinámica, similar a lo que hace `malloc()`.
            - La segunda llamada a `mmap()` mapea la biblioteca estándar de C (`libc.so.6`) en la memoria, lo cual es necesario para ejecutar el programa. También puede ser usado por `malloc()` para gestionar grandes bloques de memoria fuera del heap tradicional.

      - **3. `munmap()`**
         - **Descripción**:  
            - Libera una región de memoria previamente asignada con `mmap()`. Ayuda a evitar el desperdicio de memoria.

         - **Ejemplo en el `strace`**:

            ```bash
            munmap(0x7eba39f82000, 60631) = 0
            ```

            - `munmap()` libera bloques de memoria previamente asignados por `mmap()`, lo cual es útil para liberar la memoria dinámica que ya no se necesita. Aunque `munmap()` no es invocado directamente por `malloc()`, se puede usar para liberar grandes bloques de memoria asignados con `mmap()` durante la ejecución del programa.

   - **2. Manejo de archivos**
      - **Llamadas a sistema**: `openat`, `read`, `write`, `close`.
      - **Descripción**: El sistema operativo proporciona servicios para abrir, leer, escribir y cerrar archivos en el sistema.

      **Ejemplo**:
      - **`openat(AT_FDCWD, "origen.txt", O_RDONLY) = 3`**  
         → Abre el archivo `origen.txt` en modo solo lectura.
      - **`read(3, "Hola mundo esto es ORIGEN.", 26) = 26`**  
         → Lee 26 bytes del archivo `origen.txt`.
      - **`write(4, "Hola mundo esto es ORIGEN.\n", 27) = 27`**  
         → Escribe 27 bytes en `destino.txt`.

   - **3. Carga de ejecutables y bibliotecas**

      - **Llamadas a sistema**: `execve`, `mmap`.
      - **Descripción**: El sistema operativo permite la carga de ejecutables y bibliotecas necesarias para ejecutar programas.

      **Ejemplo**:
      - **`execve("./b.o", ["./b.o", "origen.txt", "destino.txt"], 0x7ffeeb54dbe0 /* 48 vars */) = 0`**  
         → Ejecuta el programa `b.o` con los argumentos `origen.txt` y `destino.txt`.
      - **`openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3`**  
         → Abre la biblioteca estándar de C (`libc.so.6`), necesaria para ejecutar el programa.
      - **`mmap(NULL, 2227672, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7eba39c00000`**  
         → Mapea la biblioteca `libc.so.6` en la memoria.

# Funciones/Estructuras Utilizadas

## ¿Qué es `struct stat`?

En C, la estructura `stat` se utiliza para almacenar información sobre un archivo, como su tamaño, tipo, permisos, fechas de acceso/modificación y más. Esta estructura se define en el encabezado `<sys/stat.h>`.

### 📌 Campos comunes de `struct stat`

- **`st_mode`**: Indica los permisos y el tipo del archivo (archivo regular, directorio, enlace simbólico, etc.).
- **`st_size`**: Representa el tamaño del archivo en bytes.
- **`st_atime`**: Almacena la fecha y hora del último acceso al archivo.
- **`st_mtime`**: Indica la fecha y hora de la última modificación del contenido del archivo.
- **`st_ctime`**: Representa la fecha y hora del último cambio en el estado del archivo (por ejemplo, cambios en permisos o propietario).
- **`st_uid`**: Identifica el ID del usuario propietario del archivo.
- **`st_gid`**: Indica el ID del grupo propietario del archivo.

### 📌 Uso del tamaño del archivo (`st_size`)

El tamaño del archivo se almacena en el campo `st_size` de la estructura `stat`. Se puede acceder de la siguiente manera:

```c
size_t fileSize = st.st_size;
```

---

## Asignación de Memoria (`malloc`)

### ¿Qué es `malloc`?

`malloc` (Memory Allocation) se utiliza en C para asignar memoria dinámicamente durante la ejecución del programa.

### 📌 Características de `malloc`

- Reserva un bloque de memoria del tamaño especificado en bytes.
- Devuelve un puntero al comienzo del bloque de memoria asignado.
- Si la asignación es exitosa, el puntero apunta a la memoria reservada.
- Si la asignación falla (por falta de memoria disponible), `malloc` devuelve `NULL`.

---

## Estado del Archivo (`fstat`)

### ¿Qué es `fstat`?

La función `fstat` se usa para obtener información sobre un archivo abierto y almacenarla en una estructura `stat`.

### 📌 Características de `fstat`

- Llena una estructura de tipo `stat` con la información del archivo.
- Se aplica sobre un descriptor de archivo abierto.
- Devuelve `-1` en caso de error y configura `errno` para indicar la causa del fallo.

### 📌 Uso de `fstat`

Es útil cuando se trabaja con descriptores de archivos en lugar de nombres de archivos, como en archivos abiertos mediante `open()`.

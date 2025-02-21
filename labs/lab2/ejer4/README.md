# Ejercicio 4  

Los resultados se encuentran en la carpeta `labs/lab2/ejer4` del [**repositorio**](https://github.com/JosueSay/OperatingSystems/tree/main/labs/lab2), almacenados como archivos de texto (`.txt`). Estos archivos contienen los registros obtenidos para cada caso:  

```bash
/ejer4
├── log1.txt     # Registro del Inciso 1  
├── log2.txt     # Registro del Inciso 2 antes de hacer kill al proceso padre del programa en ejecución  
└── log2_1.txt   # Registro del Inciso 2 después de hacer kill al proceso padre del programa en ejecución  
```  

## [*PS*](https://manpages.ubuntu.com/manpages/oracular/en/man1/ps.1posix.html) y [*KILL*](https://manpages.ubuntu.com/manpages/noble/en/man1/kill.1.html)

- **`ps`** forma parte de la **librería `procps`** en sistemas Linux.  
- **`ps`** muestra información sobre los procesos en ejecución.  
- **`-ael`** significa:  
  - `-a` → Muestra procesos de todos los usuarios.  
  - `-e` → Muestra todos los procesos del sistema.  
  - `-l` → Usa formato extendido con más detalles.

- **`kill`** forma parte de la **librería `util-linux`** en sistemas Linux.  
  - **`kill -9 <num_proceso>`** envía la señal **SIGKILL (9)** para **forzar la terminación inmediata** del proceso.  
  - **`-9` (SIGKILL)** significa que el proceso **no puede ignorar ni manejar la señal**, terminando de inmediato.  

### Columnas de PS

| **Columna** | **Significado** |
|------------|----------------|
| **F**  | Flags del proceso (0 = normal, 4 = carga de usuario, 1 = alta prioridad, etc.) |
| **S**  | Estado del proceso:<br>`R` = Running (Ejecutando)<br> `S` = Sleeping (Durmiendo, esperando evento)<br> `I` = Idle (Inactivo, usualmente procesos del kernel)<br> `Z` = Zombie (Terminado, pero no recogido por su padre) |
| **UID** | ID del usuario propietario del proceso |
| **PID** | ID del proceso |
| **PPID** | ID del proceso padre |
| **C**  | Uso de CPU del proceso (valores altos indican uso intensivo) |
| **PRI** | Prioridad del proceso (más bajo = mayor prioridad) |
| **NI**  | Niceness (qué tan "amable" es el proceso con otros en cuanto a CPU, valores negativos = más prioridad) |
| **ADDR** | Dirección de memoria del proceso (generalmente no se usa en sistemas modernos) |
| **SZ**  | Tamaño del proceso en páginas de memoria |
| **WCHAN** | En qué está esperando el proceso (si está dormido) |
| **TTY** | Terminal asociada al proceso (si aplica) |
| **TIME** | Tiempo total de CPU usado por el proceso |
| **CMD** | Nombre del comando que inició el proceso |

## Inciso 1 - Proceso Zombi  

Se creó un programa que ejecuta un `fork()`, en el cual el proceso padre permanece en un bucle infinito (`while`), mientras que el proceso hijo imprime un mensaje. Dicho programa fue ejecutado y, a su vez, se utilizó el comando `ps -ael` para mostrar información detallada sobre los procesos en ejecución en el sistema. El resultado generado por el comando se puede observar en el archivo `log1.txt`.

### Preguntas  

- **¿Qué significa la Z y a qué se debe?**
  - La Z indica que el proceso es un [**zombie**](https://www.ibm.com/docs/es/aix/7.1?topic=processes-). Esto significa que el proceso ha terminado su tarea, pero su entrada sigue en la tabla de procesos porque el padre no ha recogido su estado con `wait()`. Esto sucede cuando el hijo, está imprimiendo el mensaje y el padre está en un ciclo infinito (nunca termina). Como el padre no espera al hijo, el hijo permanece en la tabla de procesos, ocupando espacio.

## Inciso 2 - Proceso Huérfano  

Se modificó el programa para que, en lugar de que el hijo solo muestre un mensaje, realice un conteo desde 1 hasta 4,000,000 (variando este límite) con el objetivo de que el proceso dure entre 5 y 15 segundos en completarse. Durante la ejecución, se utilizó el comando `ps -ael` y, antes de que el programa finalizara, se ejecutó el comando `kill -9 <pid_padre_programa>`, es decir, se eliminó el proceso padre antes de que el programa terminara. Para ello se utilizó el comando:

```bash
ps -ael | head -1 > log2.txt && while true; do 
  ps -ael | grep pb.exe | grep -v grep
  ps -ael | grep systemd
  date
  sleep 1
done | tee -a log2.txt
```

1. **`ps -ael | head -1 > log2.txt`**:
   - **`ps -ael`**: Muestra todos los procesos que están en ejecución en el sistema.
   - **`|`**: Pasa la salida del comando anterior (`ps -ael`) al siguiente comando.
   - **`head -1`**: Toma solo la primera línea de la salida (que es el encabezado de los procesos).
   - **`> log2.txt`**: Guarda esa primera línea (encabezado) en el archivo `log2.txt`, sobrescribiendo cualquier contenido previo en ese archivo.

2. **`&&`**:
   - Esto asegura que el siguiente comando solo se ejecute si el comando anterior (`ps -ael | head -1 > log2.txt`) tuvo éxito. Es una forma de encadenar comandos.

3. **`while true; do ... done`**:
   - **`while true`**: Inicia un bucle que se ejecutará infinitamente (ya que `true` siempre devuelve verdadero).
   - **`do`**: Comienza el bloque de comandos que se ejecutarán en cada ciclo del bucle.

4. **`ps -ael | grep pb.exe | grep -v grep`**:
   - **`ps -ael`**: Muestra todos los procesos en ejecución.
   - **`grep pb.exe`**: Filtra la salida para mostrar solo las líneas que contienen `pb.exe` (busca ese proceso).
   - **`grep -v grep`**: Excluye la línea que muestra el propio comando `grep`, evitando que aparezca en los resultados.

5. **`ps -ael | grep systemd`**:
   - **`ps -ael`**: Muestra todos los procesos en ejecución.
   - **`grep systemd`**: Filtra la salida para mostrar solo las líneas que contienen `systemd`.

6. **`date`**:
   - Muestra la fecha y hora actual.

7. **`sleep 1`**:
   - Hace una pausa de 1 segundo antes de repetir el ciclo.

8. **`done`**:
   - Marca el final del bucle `while`, por lo que se repite el ciclo infinitamente hasta que lo interrumpas manualmente.

9. **`| tee -a log2.txt`**:
   - **`|`**: Pasa la salida del bucle al siguiente comando (`tee`).
   - **`tee -a log2.txt`**: Muestra la salida en la terminal y la agrega al final de `log2.txt` sin sobrescribir el archivo.

### Preguntas  

Para este inciso, se utilizaron los archivos `log2.txt` y el comando mencionado.

- **¿Qué sucede en la ventana donde ejecutó su programa?**

  - sds

- **Al volver a ejecutar `ps -ael`, ¿quién es el padre del proceso que quedó huérfano?**
  
  

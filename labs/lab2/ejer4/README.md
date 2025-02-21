# Ejercicio 4  

Los resultados se encuentran en la carpeta `labs/lab2/ejer4` del [*repositorio*](https://github.com/JosueSay/OperatingSystems/tree/main/labs/lab2), almacenados como archivos de texto (`.txt`). Estos archivos contienen los registros obtenidos para cada caso:  

```bash
/ejer4
├── log1.txt     # Registro del Inciso 1  
├── log2.txt     # Registro del Inciso 2 antes de hacer kill al proceso padre del programa en ejecución  
└── log2_1.txt   # Registro del Inciso 2 después de hacer kill al proceso padre del programa en ejecución  
```  

## Inciso 1 - Proceso Zombi  

Se creó un programa que ejecuta un `fork()`, en el cual el proceso padre permanece en un bucle infinito (`while`), mientras que el proceso hijo imprime un mensaje. Dicho programa fue ejecutado y, a su vez, se utilizó el comando `ps -ael` para mostrar información detallada sobre los procesos en ejecución en el sistema. El resultado generado por el comando se puede observar en el archivo `log1.txt`.

### Preguntas  

- **¿Qué significa la Z y a qué se debe?**  

## Inciso 2 - Proceso Huérfano  

Se modificó el programa para que, en lugar de que el hijo solo muestre un mensaje, realice un conteo desde 1 hasta 4,000,000 (variando este límite) con el objetivo de que el proceso dure entre 5 y 15 segundos en completarse. Durante la ejecución, se utilizó el comando `ps -ael` y, antes de que el programa finalizara, se ejecutó el comando `kill -9 <pid_padre_programa>`, es decir, se eliminó el proceso padre antes de que el programa terminara.  

### Preguntas  

Para este inciso, se utilizaron los archivos `log2.txt` y `log2_1.txt`.  

- **¿Qué sucede en la ventana donde ejecutó su programa?**  
- **Al volver a ejecutar `ps -ael`, ¿quién es el padre del proceso que quedó huérfano?**  

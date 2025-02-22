# Ejercicio 5

1. **Hacer un programa que reciba dos parámetros: un número (n) y una letra (x)**
2. **Crear una memoria compartida que tanto el proceso padre e hijo puedan acceder a él corroborando que ya existe una memoria compartida abierta y transmitiendo el paso (file descriptor) por medio de un medio de comunicación**
3. **Acción de escritura del hijo mediante el aviso del padre usando un medio de comunicación**
4. **Hacer un runner para ejecutar un fork que mande una letra y cantidades diferentes al ipc**

## Preguntas

1. **¿Qué diferencia hay entre realizar comunicación usando memoria compartida en lugar de usando un archivo de texto común y corriente?**

   La memoria compartida permite la comunicación directa entre procesos a través de un área de memoria común, mientras que los archivos de texto comunes requieren la escritura y lectura secuencial.

2. **¿Por qué no se debe usar el file descriptor de la memoria compartida producido por otra instancia para realizar el mmap?**

   El file descriptor de la memoria compartida debe ser único para cada proceso que lo use. Usar un file descriptor de otra instancia puede resultar en una asignación de memoria incorrecta o en la corrupción de datos.

3. **¿Es posible enviar el output de un programa ejecutado con exec a otro proceso por medio de un pipe? Investigue y explique cómo funciona este mecanismo en la terminal (e.g., la ejecución de `ls | less`).**

4. **¿Cómo puede asegurarse de que ya se ha abierto un espacio de memoria compartida con un nombre determinado? Investigue y explique `errno`.**

   Si el valor de `errno` es `EEXIST`, significa que el espacio de memoria compartida ya ha sido creado y abierto por otro proceso.

5. **¿Qué pasa si se ejecuta `shm_unlink` cuando hay procesos que todavía están usando la memoria compartida?**

6. **¿Cómo puede referirse al contenido de un espacio en memoria al que apunta un puntero? Observe que su programa deberá tener alguna forma de saber hasta dónde ha escrito su otra instancia en la memoria compartida para no escribir sobre ello.**

   Se puede mantener un índice o marcador en la memoria compartida que indique hasta qué posición se ha escrito. Este índice puede ser actualizado por los procesos para asegurarse de que no se sobrescriban datos.

7. **Imagine que una ejecución de su programa sufre un error que termina la ejecución prematuramente, dejando el espacio de memoria compartida abierto y provocando que nuevas ejecuciones se queden esperando el file descriptor del espacio de memoria compartida. ¿Cómo puede liberar el espacio de memoria compartida “manualmente”?**

   Se puede cerrar el file descriptor con `close`. Para liberar manualmente un espacio de memoria compartida dejado abierto debido a una ejecución errónea, se puede utilizar `shm_unlink` para eliminar el nombre del espacio de memoria compartida.

8. **Observe que el programa que ejecute dos instancias de `ipc.c` debe cuidar que una instancia no termine mucho antes que la otra para evitar que ambas instancias abran y cierren su propio espacio de memoria compartida. ¿Aproximadamente cuánto tiempo toma la realización de un `fork()`? Investigue y aplique `usleep`.**

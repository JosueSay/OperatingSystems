# Implementación de paralelismo

En esta etapa se implementó la directiva `#pragma omp parallel for` sobre los ciclos `for` que validan filas, columnas y subgrillas del Sudoku. El objetivo fue distribuir las iteraciones de manera paralela entre múltiples hilos.  

Para evitar **race conditions**, se utilizó la cláusula `private(i)` en las variables de iteración que se declararon fuera del ciclo `for`, y la cláusula `reduction(&& : resultado)` en las variables que acumulan el resultado de cada validación. Esto garantiza que cada hilo trabaje con su propia copia local de las variables, y que el resultado se combine de forma segura al finalizar la ejecución paralela.

```c
int i;
#pragma omp parallel for private(i) reduction(&& : columnas_validas)
for (i = 0; i < SIZE; i++) {
    if (!validateColumn(i)) columnas_validas = 0;
}
```

Esto permitió observar la ejecución concurrente de múltiples hilos, evidenciado por la impresión de distintos identificadores de thread (TID) durante la validación de columnas. Aunque los hilos de OpenMP no siempre aparecen reflejados en el resultado del comando `ps`, su actividad es comprobable mediante los mensajes desplegados en consola.

## Observaciones de ejecución

Durante la ejecución se observaron los siguientes comportamientos:

### 1. `TID` de múltiples threads

Se imprimieron distintos `TID` al ejecutar la validación de columnas en paralelo, lo que confirma que OpenMP lanzó múltiples hilos.

### 2. Primer `ps` (tras `pthread_join()`)

```bash
NLWP = 1
```

➡️ Los hilos de OpenMP ya habían terminado, por eso no aparecen en ese momento.

### 3. Segundo `ps` (antes de terminar el programa)

```bash
NLWP = 12
```

➡️ Los hilos seguían activos al momento de ejecutar `ps`, por eso se capturaron todos los LWP en ese instante.

| Momento del `ps`                     | ¿LWP múltiples?     | ¿Por qué?                                                |
|--------------------------------------|---------------------|----------------------------------------------------------|
| Justo después del `pthread_join()`   | Solo 1 LWP          | Los hilos de OpenMP ya terminaron.                       |
| Antes de finalizar (segundo `fork`)  | 12 LWP              | Los hilos de OpenMP seguían activos al ejecutar `ps`.    |

- El sistema **sí está usando hilos reales**: múltiples `TID` y LWP.
- OpenMP distribuyó las tareas de validación en paralelo correctamente.
- El uso de `private` y `reduction` eliminó riesgos de condiciones de carrera.
- La segunda ejecución del comando `ps` confirmó la existencia de múltiples hilos activos durante el procesamiento.

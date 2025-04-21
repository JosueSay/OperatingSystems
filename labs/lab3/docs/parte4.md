# Fase: Configuración de `omp_set_num_threads`, `schedule(dynamic)` y `omp_set_nested(true)`

En esta fase se aplicaron varias configuraciones adicionales al paralelismo con OpenMP para ajustar el comportamiento de los hilos y facilitar su análisis con herramientas del sistema operativo.

## Cambios realizados

- Se añadió `omp_set_num_threads(1);` al inicio de `main()` para establecer inicialmente un solo hilo.
- Se insertó `omp_set_num_threads(9);` al inicio de la función encargada de validar columnas, ya que el ciclo recorre 9 columnas.
- Se activó el anidamiento de hilos con `omp_set_nested(true);` dentro de la misma función del thread.
- Se aplicó la directiva `schedule(dynamic)` en todos los ciclos `for` paralelizados con `#pragma omp parallel for`, para distribuir dinámicamente las iteraciones entre los hilos disponibles.
- Se mantuvieron las cláusulas `private()` y `reduction()` para evitar condiciones de carrera.

## Observaciones durante la ejecución

```bash
Thread en ejecución durante validación de columnas: 141421
Thread en ejecución durante validación de columnas: 141423
Thread en ejecución durante validación de columnas: 141426
Thread en ejecución durante validación de columnas: 141428
Thread en ejecución durante validación de columnas: 141427
Thread en ejecución durante validación de columnas: 141425
Thread en ejecución durante validación de columnas: 141422
Thread en ejecución durante validación de columnas: 141424
Thread en ejecución durante validación de columnas: 141429
```

Se observaron 9 hilos (TID distintos) durante la revisión de columnas, lo que confirma el uso de OpenMP en paralelo con asignación dinámica de iteraciones.

## Número de LWP registrados

### Durante la revisión de columnas (`ps` después del `pthread_join()`)

```bash
NLWP = 1
```

Solo se observó un LWP. Los hilos de OpenMP finalizaron antes de que se ejecutara el comando `ps`, por lo tanto ya no estaban activos.

### Antes de finalizar el programa (`ps` en el segundo `fork()`)

```bash
NLWP = 1
```

De nuevo se registra un solo LWP. Esto refuerza la observación de que los hilos de OpenMP son efímeros y terminan antes de ser capturados por `ps`.

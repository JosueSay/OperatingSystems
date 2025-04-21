# Respuestas a Preguntas del Laboratorio

## 1. ¿Qué es una race condition y por qué hay que evitarlas?

Esto ocurre cuando dos o más hilos acceden y modifican una misma variable compartida sin sincronización. Hay que evitarlas porque pueden causar errores sobre variables compartidas.

En el código se evita mediante:

- `private()` en variables de los ciclos `for`.
- `reduction()` para combinar resultados de forma segura.

## 2.  ¿Cuál es la relación, en Linux, entre pthreads y clone()? ¿Hay diferencia al crear threads con uno o con otro? ¿Qué es más recomendable?

`pthread_create()` internamente usa la syscall `clone()` en Linux para crear un nuevo hilo (LWP). `clone()` permite compartir recursos como memoria entre hilos del mismo proceso.

**Diferencia**:

- `clone()` es a bajo nivel.
- `pthread` es más portable y sencillo de usar.

Linux usa `tasks`, representadas por estructuras `task_struct`.

- **`fork()`**: copia el proceso.
- **`clone()`**: permite compartir recursos, se usa para threads.
- Cada thread tiene:
  - ID, registros, pila de usuario y kernel, TLS.

## 3. ¿Dónde hay paralelismo de tareas y de datos?

- **Paralelismo de datos:** mismas operaciones en datos diferentes, uso de `#pragma omp parallel for` para recorrer filas, columnas y subgrillas en paralelo, aplicando la misma función sobre distintos datos.
- **Paralelismo de tareas:** distintas operaciones en los mismos datos, uso de `pthread` para delegar validación de columnas a otro hilo.

## 4. ¿Cuántos LWP’s hay abiertos antes de terminar y durante la revisión de columnas?

- **Antes de terminar `main()`**: `NLWP = 12`  
- **Durante revisión de columnas (en primer `ps`)**: `NLWP = 1`

Esto se debe a que los hilos de OpenMP terminan muy rápido y no son visibles en el momento en que se ejecuta `ps`.

**User threads esperados**:

- 1 (main) + 1 (`pthread`) + 9 (OpenMP) = 11–12 hilos (1:1 model en Linux)

## 5. ¿Qué pasa al limitar los threads en `main()` a 1?

- Durante revisión de columnas: `NLWP = 1`
- Antes del cambio (por defecto): `NLWP = 12` o más

OpenMP por defecto puede usar tantos hilos como núcleos lógicos disponibles en el sistema.

## 6. ¿Qué significa la primera columna del comando `ps`? ¿Qué LWP está inactivo?

- Primera columna (`F`) indica flags del proceso.
- El LWP inactivo es el hilo principal (`main`) porque está esperando (`WCHAN = do_wai`) a que terminen los hijos.
- Los demás están en `futex_`, esperando en sincronización interna de OpenMP.

## 7. ¿Qué es un thread team en OpenMP? ¿Cuál es el master thread?

- **Thread team**: conjunto de hilos gestionados por OpenMP para una región paralela.
- **Master thread**: el hilo que entra primero a la región paralela (por defecto, el que ejecuta `main()`).

Un hilo puede aparecer como "activo" pero no hacer trabajo real si está en **busy-wait** (esperando trabajo).

OpenMP usa un **thread pool** y reusa hilos para evitar el costo de creación y destrucción constante.

## 8. ¿Qué se observó tras agregar `schedule(dynamic)`?

- Se observaron más TIDs distintos en cada ejecución.
- Mayor distribución del trabajo entre hilos.
- Antes de usar `schedule(dynamic)`, algunos hilos ejecutaban varias iteraciones seguidas.

Deducción: OpenMP usa distribución estática por defecto, lo cual puede generar desequilibrio de carga. Con `dynamic`, el reparto es más equitativo.

## 9. ¿Qué pasó al agregar `omp_set_num_threads()` sin `omp_set_nested()`?

- Se observaron menos hilos activos.
- Menor concurrencia visible.
- No necesariamente mejor desempeño: más hilos ≠ más velocidad si la carga no lo justifica.

La concurrencia depende del número de hilos y cómo se balancea la carga.

## 10. ¿Qué efecto tuvo `omp_set_nested(true)`?

- Permite crear regiones paralelas dentro de otras.
- En este caso, permite que el `pthread` cree un equipo de hilos para OpenMP sin conflictos.
- Aumenta la concurrencia **y** complejidad de planificación.

Este ajuste **facilitó paralelismo anidado**, necesario al mezclar `pthread` y OpenMP en distintos niveles.

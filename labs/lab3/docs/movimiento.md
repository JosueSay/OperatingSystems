# Recorrido de un arreglo bidimensional

Cuando recorres un arreglo bidimensional linealizado en memoria, se usa una fórmula para calcular las posiciones de fila y columna de un elemento. A continuación, explicamos cómo funciona este proceso utilizando las operaciones de división y módulo.

## Conceptos clave

- **Fila**: La operación `i / SIZE` te dice cuántas filas completas has recorrido hasta el índice `i`. Esto se logra dividiendo `i` entre el número de columnas (SIZE).
  
- **Columna**: La operación `i % SIZE` te da el índice de la columna dentro de la fila correspondiente. Esto se obtiene aplicando el operador módulo a `i` con el tamaño de la fila.

## Ejemplo con un arreglo 3x3

Imagina un arreglo 3x3 que se almacena linealmente de la siguiente manera:

```bash
[1, 2, 3, 4, 5, 6, 7, 8, 9]
```

### Iteraciones

**Iteración 1: i = 0**

- **Fila**: `0 / 3 = 0` → Primera fila
- **Columna**: `0 % 3 = 0` → Primera columna
  - Elemento: 1

**Iteración 2: i = 1**

- **Fila**: `1 / 3 = 0` → Primera fila
- **Columna**: `1 % 3 = 1` → Segunda columna
  - Elemento: 2

**Iteración 3: i = 2**

- **Fila**: `2 / 3 = 0` → Primera fila
- **Columna**: `2 % 3 = 2` → Tercera columna
  - Elemento: 3

**Iteración 4: i = 3**

- **Fila**: `3 / 3 = 1` → Segunda fila
- **Columna**: `3 % 3 = 0` → Primera columna
  - Elemento: 4

**Iteración 5: i = 4**

- **Fila**: `4 / 3 = 1` → Segunda fila
- **Columna**: `4 % 3 = 1` → Segunda columna
  - Elemento: 5

**Iteración 6: i = 5**

- **Fila**: `5 / 3 = 1` → Segunda fila
- **Columna**: `5 % 3 = 2` → Tercera columna
  - Elemento: 6

**Iteración 7: i = 6**

- **Fila**: `6 / 3 = 2` → Tercera fila
- **Columna**: `6 % 3 = 0` → Primera columna
  - Elemento: 7

**Iteración 8: i = 7**

- **Fila**: `7 / 3 = 2` → Tercera fila
- **Columna**: `7 % 3 = 1` → Segunda columna
  - Elemento: 8

**Iteración 9: i = 8**

- **Fila**: `8 / 3 = 2` → Tercera fila
- **Columna**: `8 % 3 = 2` → Tercera columna
  - Elemento: 9

## ¿Por qué funciona?

- **División**: Al dividir `i / SIZE`, obtenemos cuántas filas completas se han recorrido, lo que nos indica en qué fila estamos.
  
- **Módulo**: Al aplicar `i % SIZE`, obtenemos el residuo de la división, lo que nos da la columna dentro de la fila actual.

Este método permite recorrer de manera eficiente un arreglo bidimensional almacenado linealmente en memoria.

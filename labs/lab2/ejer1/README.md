# Ejercicio 1

Usando una máquina virtual con más de un proceso (recomendación de 4 procesos).

Cree un programa en C que ejecute cuatro `fork()s` consecutivos. Luego cree otro programa en C que ejecute `fork()` dentro de un ciclo for de cuatro iteraciones.

## Preguntas

- ¿Cuántos procesos se crean en cada uno de los programas?
  
  | Fork          | Proceso(s) que lo ejecuta(n)              | Procesos creados           | Resultado final                          |
  |--------------|---------------------------------|---------------------------|------------------------------------------|
  | Primer fork  | p0                             | p1                        | p0, p1                                  |
  | Segundo fork | p0, p1                         | p2, p3                     | p0, p1, p2, p3                          |
  | Tercer fork  | p0, p1, p2, p3                 | p4, p5, p6, p7             | p0, p1, p2, p3, p4, p5, p6, p7           |
  | Cuarto fork  | p0, p1, p2, p3, p4, p5, p6, p7 | p8, p9, p10, ..., p14, p15 | p0, p1, ..., p14, p15                    |

  Dando un total de 16 procesos, siguiendo la lógica de que cada proceso ejecutado crea un hijo. En cada iteración, tendremos $2^k$ procesos resultantes cada vez que se ejecuta un `fork`, donde $k$ es la cantidad de veces que se ha ejecutado el `fork`. Por ejemplo, si se ejecutan 4 forks, se tendrán $2^4 = 16$ procesos.

- ¿Por qué hay tantos procesos en ambos programas cuando uno tiene cuatro llamadas fork() y el otro sólo tiene una?
  
  Como se explicó en el inciso anterior, cada `fork()` genera como resultado dos procesos. Por lo tanto, en el primer ejercicio, con 4 forks, el resultado será un total de 16 procesos creados por su ejecución. Sin embargo, en el caso del `for`, aunque solo haya una instancia, esta se encuentra dentro de una iteración en la que igualmente se ejecutarán 4 forks, por lo que se obtendrá el mismo resultado de 16 procesos.

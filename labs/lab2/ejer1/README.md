# Ejercicio 1

Usando una máquina virtual con más de un proceso (recomendación de 4 procesos).

Cree un programa en C que ejecute cuatro `fork()s` consecutivos. Luego cree otro programa en C que ejecute `fork()` dentro de un ciclo for de cuatro iteraciones.

## Preguntas

- ¿Cuántos procesos se crean en cada uno de los programas?
  - *R* Se activan por cada proceso 
- ¿Por qué hay tantos procesos en ambos programas cuando uno tiene cuatro llamadas fork() y el otro sólo tiene una?

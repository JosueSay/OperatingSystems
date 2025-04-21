# Ejercicio 2

## Preguntas

**¿Cuál es la diferencia en C entre un método que no recibe parámetros y uno que recibe void?**

- `int funcion()` → El compilador **no puede garantizar** que no se reciban argumentos.
- `int funcion(void)` → Especifica explícitamente que **no recibe ningún parámetro**. Es la forma correcta y segura.

**¿Qué diferencia hay entre `printk` y `printf`?**

- `printf()` es para **programas en espacio de usuario** (como `main.c`).
- `printk()` es para **espacio de kernel**, y se usa para imprimir mensajes que pueden verse con `dmesg`.

**¿Qué es y para qué sirve `KERN_INFO`?**

- `KERN_INFO` es un **nivel de prioridad** de mensajes del kernel (informativo). Sirve para **clasificar el mensaje** en los logs del sistema.

## Referencias

1. **[Void como parámetro](https://es.stackoverflow.com/questions/160095/void-como-par%C3%A1metro-de-una-funci%C3%B3n)**
2. **[Printk y Printf](https://www.quora.com/What-is-the-difference-between-Printk-and-Printf-in-Linux)**
3. **[Kern Info](https://stackoverflow.com/questions/59626722/what-exactly-expands-the-kern-info-and-where-it-is-implemented)**

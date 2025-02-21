# Cambios de Contexto

El comando `sudo apt-get install sysstat` se usa para instalar el paquete **sysstat** en sistemas basados en Debian, como Ubuntu.

El paquete **sysstat** incluye herramientas para monitorear el rendimiento del sistema, como:

- **`iostat`**: muestra estadísticas sobre el uso de CPU y las operaciones de entrada/salida de dispositivos.
- **`mpstat`**: muestra el uso de la CPU por cada procesador individual.
- **`pidstat`**: proporciona estadísticas sobre procesos individuales.
- **`sar`**: recopila, reporta y guarda estadísticas de rendimiento del sistema a lo largo del tiempo.
- **`tload`**: muestra una representación gráfica de la carga del sistema.

El comando `pidstat -w 1` muestra información sobre los procesos en tu sistema, con un enfoque en las estadísticas relacionadas con el intercambio de contexto (context switches) y los tiempos de espera de los procesos. Aquí hay una explicación de cada columna:

- **UID**: El ID de usuario del proceso.
- **PID**: El ID del proceso.
- **cswch/s**: El número de cambios de contexto voluntarios por segundo (voluntary context switches), es decir, cuántas veces un proceso ha cedido voluntariamente la CPU.
- **nvcswch/s**: El número de cambios de contexto no voluntarios por segundo (involuntary context switches), es decir, cuántas veces el sistema operativo ha interrumpido un proceso para que otro tome la CPU.
- **Command**: El nombre del comando o proceso que está siendo ejecutado.

Este comando se actualiza cada segundo (debido a `-w 1`), por lo que muestra información en tiempo real. Los cambios de contexto pueden ocurrir cuando un proceso no tiene tiempo de CPU disponible, y el sistema operativo lo interrumpe para darle tiempo a otro proceso.

## Glosario

- **Contexto:** es toda la información que define el estado de un proceso en un momento dado, es decir, lo que está haciendo y qué recursos está utilizando.

- **Cambio de contexto** es cuando el sistema guarda lo que está haciendo un proceso y lo reemplaza por otro proceso, para que ambos puedan compartir el tiempo del CPU. Es como cambiar de tarea en una lista, guardando lo que hiciste para retomar más tarde.

## Involuntario

Sucede cuando el sistema operativo decide cambiar el contexto de un proceso sin que este lo haya solicitado. Esto generalmente ocurre porque el proceso ha agotado su tiempo asignado para usar el CPU. El sistema operativo interrumpe el proceso para darle a otro proceso la oportunidad de ejecutarse.

## Voluntario

Ocurre cuando un proceso decide ceder el control del CPU de manera voluntaria. Esto puede suceder, por ejemplo, cuando un proceso termina su tarea o cuando decide esperar por algo (como una entrada del usuario o acceso a un recurso).

## Ejemplo

- **Sistema Operativo = Gasolinera/Jefe**: El que organiza y administra el trabajo de los procesos (trabajadores).
- **Procesos = Trabajadores**: Son las entidades que realizan las tareas en el sistema (lavar vidrios, llenar gas, etc.).
- **Contexto = Tareas**: El estado de cada proceso en un momento dado, como lo que están haciendo.
- **Recursos = Cliente**: Las condiciones externas que requieren que se cambien las tareas de los trabajadores.
- **Cambio de Contexto**: Cuando un trabajador cambia de tarea (voluntariamente o involuntariamente) según las necesidades del sistema.

### Cambio de Contexto

Cuando llega un cliente que necesita gas y también inflar llantas, el trabajador que limpia vidrios debe dejar su tarea (guardar su **contexto**) y empezar a inflar las llantas (cambiar de contexto), pero solo mientras dure esa tarea. Después de que termine, vuelve a su tarea original de limpiar vidrios.

### Cambio de Contexto Voluntario

Imaginemos que el trabajador que está **llenando gas** termina su tarea y se acerca al jefe (el sistema operativo) para decir: "He terminado de llenar el tanque. ¿Qué más hago?" El jefe, entonces, puede decidir lo que le asignará a continuación, como ir a **almorzar** o **ayudar a otro trabajador** (hacer otra tarea, como limpiar vidrios o barrer). En este caso, el **trabajador voluntariamente** cede el control de su tarea porque ya la terminó y está listo para una nueva. Este es el **cambio de contexto voluntario** porque el trabajador decide cambiar su tarea.

### Cambio de Contexto Involuntario

Aquí, el **cambio de contexto involuntario** ocurre cuando el jefe observa que el trabajador que está **limpiando vidrios** está tardando demasiado en su tarea. El jefe decide que **ya no puede esperar más** y **cambia al trabajador a otra tarea**. Esto puede suceder por varias razones, por ejemplo:

1. **El cliente está esperando mucho tiempo**: Tal vez el cliente se impacienta porque quiere irse pronto, y solo tiene un vidrio limpio. El jefe decide que para cumplir con las expectativas del cliente, tiene que cambiar la tarea del trabajador.
2. **El trabajador es lento o tiene problemas**: Tal vez el trabajador no está haciendo bien su trabajo o está más lento que otros, por lo que el jefe decide asignarle una tarea que pueda hacer más rápido (como barrer), y poner a otro trabajador más rápido a limpiar los vidrios.

>Nota: Se habló de CPU como recurso de control pero puede ser también memoria, pero se puede englobar como gestión de recursos en general.

# Ejercicio 3

Se ejecutaron los siguientes comandos en una distribución Ubuntu utilizando la librería `sysstat`:

1. Este comando obtiene datos del proceso y cambios de estado cada segundo sin finalizar:

    ```bash
    pidstat -w 1 | tee -a log.txt
    ```

2. Este comando obtiene los datos del proceso y cambios de estado en un intervalo de 1 segundo:

    ```bash
    pidstat -w 1 1 | tee -a log.txt
    ```

Los resultados se encuentran en la carpeta `labs/lab2/ejer3/` del [**repositorio**](https://github.com/JosueSay/OperatingSystems/tree/main/labs/lab2) utilizado como archivos de texto (`.txt`), los cuales contienen los registros obtenidos para cada caso:

```bash
/ejer3
├── log1.txt          # Registro sin realizar ninguna acción adicional
├── log2.txt          # Registro moviendo la terminal en la interfaz
├── log3.txt          # Registro escribiendo en la terminal donde se ejecutó el comando
├── log_combine.txt   # Registro ejecutando `program_a.c`, moviendo la terminal y escribiendo en la terminal
├── log_cons.txt      # Registro ejecutando el segundo comando y `program_a.c`
└── log_conc.txt      # Registro ejecutando el segundo comando y `program_b.c`
```

## Preguntas

### Explorando pidstats

Para esta parte se analizarán los archivos `log1.txt`, `log2.txt` y `log3.txt` que se pueden observar en el [**repositorio**](https://github.com/JosueSay/OperatingSystems/tree/main/labs/lab2).

- **`log1.txt`** servirá como referencia para observar el comportamiento del sistema sin interacción adicional.  
- **`gnome-terminal-` y `gnome-shell`** son procesos clave, ya que `gnome-terminal` maneja la interfaz de la terminal y `gnome-shell` gestiona la parte visual. Ambos estarán presentes en todos los registros.

- **¿Qué tipo de cambios de contexto aumentan notablemente en cada caso y por qué?**

  - En **`log2.txt`**, donde se movió la terminal en la interfaz, se observó un aumento significativo en cambios de contexto para`gnome-shell`. Esto ocurre porque `gnome-shell` controla la parte visual, incluyendo el movimiento de ventanas. Además, apareció `Xwayland`, ya que este actúa como un intermediario cuando la interfaz necesita redibujar elementos. En comparación, en `log1.txt` no se registra la presencia de `Xwayland` como se menciona en esta [*documentación*](https://wiki-gnome-org.translate.goog/Initiatives(2f)Wayland(2f)Xwayland.html?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=sge#:~:text=Xwayland%20is%20a%20fully%20fledged,protocols%20for%20implementing%20certain%20functionality.), lo que confirma que solo aparece cuando hay cambios gráficos.

  - En **`log3.txt`**, donde se escribió en la terminal mientras `pidstat` estaba en ejecución, se detectó un incremento de cambios de contexto en `ibus-daemon`. Este proceso gestiona la entrada de texto en el sistema, como se menciona en la siguiente [*documentación*](https://manpages-ubuntu-com.translate.goog/manpages/jammy/man1/ibus-daemon.1.html?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=sge#:~:text=DESCRIPTION,to%20develop%20input%20method%20easily.). Por lo tanto, era esperable que fuera el proceso con más cambios de contexto en este caso.

  Los cambios de contexto **voluntarios** aumentaron significativamente para los procesos mencionados, ya que estos eventos eran manejados eficientemente por el procesador sin necesidad de interrupciones forzadas. En consecuencia, los cambios de contexto **involuntarios** fueron menores, pero aun así aumentaron en comparación con otros procesos debido a la mayor actividad del sistema.

### Usando pidstats con programas

Para esta parte se analizarán los archivos `log_conc.txt` y `log_cons.txt` que se pueden observar en el [**repositorio**](https://github.com/JosueSay/OperatingSystems/tree/main/labs/lab2).

- El programa que uso `for's` consecutivos fue `b.exe` sus logs son `log_cons.txt`.
- El programa que uso `for's` concurrentes fue `a.exe` sus logs son `log_conc.txt`.

1. **¿Qué diferencia hay en el número y tipo de cambios de contexto entre programas?**  

   El programa **concurrente (b.exe)** tiene **más cambios de contexto voluntarios e involuntarios** en comparación con el programa **secuencial (a.exe)**.  

   - **En b.exe (con fork())**:
     - Aparecen **4 instancias del proceso** debido a la creación de **3 procesos hijos** mediante fork(), lo que genera un mayor número de cambios de contexto.
     - Un proceso (b.exe) tiene **0 cambios de contexto**, lo cual sugiere que es el **proceso padre**, que simplemente espera a sus hijos con wait().
     - Los procesos hijos tienen una mayor variabilidad en los cambios de contexto, dependiendo de la ejecución del código en cada uno.

   - **En a.exe (secuencial, sin fork())**:
     - Se ejecuta como un único proceso, pero tiene **cambios de contexto involuntarios más elevados**, lo que indica que el sistema operativo está **interrumpiendo su ejecución** para dar tiempo esos recursos como CPU a otros procesos.
     - El número de cambios de contexto es más **consistente y predecible**, ya que a.exe sigue un flujo lineal sin creación de nuevos procesos.

2. **¿A qué puede atribuir los cambios de contexto voluntarios realizados por sus programas?**  

   - En **b.exe (concurrente con fork())**, los cambios voluntarios son altos porque:
     - Cada proceso padre **espera a su propio hijo con wait()**, lo que provoca cambios voluntarios de recursos mientras esperan su finalización e incluso aumentan y superan a los de los secuenciales porque además de esperar imprime son otras operacioines que el proceso finaliza.

   - En **a.exe (secuencial, sin fork())**, los cambios voluntarios son menores porque:
     - como se mencionó anteriormente las llamadas a sistemas como prints son operacioens que al momento de terminarlas libera recurso. Por lo tanto como es la misma en las iteraciones tiene sentido que fueran constantes.

3. **¿A qué puede atribuir los cambios de contexto involuntarios realizados por sus programas?**

   - En **a.exe (secuencial)**:
     - Tiene **más cambios de contexto involuntarios**, lo que indica que está **usando completamente su tiempo de recursos como CPU** y el sistema operativo lo interrumpe para repartir esos reecuros entre otros procesos.

   - En **b.exe (concurrente con fork())**:
     - Al igual que el programa secuencial puede ocurrir porque estaba usando recursos y el sistema operativo los necesita para otro proceso, pero notemos que estos son menores y puede ser debido a que hay más procesos con menos carga cada uno, pudiendo hacer que no estas interrupciones por el sistema operativo disminuyan.

4. **¿Por qué el reporte de cambios de contexto para su programa con fork() muestra cuatro procesos, uno de los cuales reporta cero cambios de contexto?**  

   El programa `b.exe` utiliza **tres fork()**, lo que crea **cuatro procesos en total** (padre, hijo, nieto y bisnieto). En el reporte de pidstat, **uno de los procesos muestra 0 cambios de contexto** pudiendo ser el padre porque:
   Esto ocurre porque:

   - **El proceso padre (b.exe) solo ejecuta wait() y no realiza trabajo computacional** significativo a comparación de los hijos que hacen más cosas como los prints y for.

### Usando pidstas con programas + otras actividades

Para esta parte se analizarán el archivo `log_combinae.txt` que se pueden observar en el [**repositorio**](https://github.com/JosueSay/OperatingSystems/tree/main/labs/lab2); la actividad fuerte está entre lineas 69-151.

- **¿Qué efecto percibe sobre el número de cambios de contexto de cada tipo?**

  En un punto se puede observar que difieren entre los procesos mencionados antes:

  - **Cuando se escribe en la terminal**, se observan **más cambios de contexto voluntarios** (`cswch/s`) debido a la interacción de escritura en la terminal.
  - **Cuando se mueve la terminal en la interfaz gráfica**, los cambios de contexto **involuntarios (`nvcswch/s`) aumentan** porque el sistema operativo redibuja y gestiona eventos en `gnome-shell` y `Xwayland`.
  - **Cuando se ejecuta el programa con `for` secuenciales (`a.exe`)**, los cambios de contexto **involuntarios (`nvcswch/s`) son altos pero especialmente los voluntarios son bajos** porque el sistema operativo interrumpe el proceso intensivo en recursos para dar tiempo a otros procesos.

# 🐧 Linux

Linux no es un sistema operativo, sino un **kernel**.

## 🔍 ¿Qué es el kernel?

El **kernel** es el núcleo de un sistema operativo, encargado de gestionar los recursos del hardware y permitir la comunicación entre el software y los componentes físicos de la computadora. Es la base sobre la que se construyen los sistemas operativos.

Debido a que es código abierto, cualquier empresa o persona puede modificarlo libremente y construir su propio sistema operativo basado en él. A estos sistemas operativos se les conoce como **distribuciones** o **distros**.

## 🌍 Distribuciones de Linux

Las distribuciones de Linux se diferencian en varios aspectos, como la organización de archivos y carpetas, los programas preinstalados y la configuración del sistema. Esto permite que cada distro tenga un enfoque particular según las necesidades del usuario.

### 🏆 Ubuntu: Una de las más populares

Ubuntu es una de las distribuciones de Linux más utilizadas. Es mantenida por la empresa **Canonical** y está diseñada para ser accesible y fácil de usar, especialmente para quienes vienen de Windows.

Ubuntu cuenta con varias versiones especializadas:

- **Ubuntu Desktop** 🖥️ → Para computadoras personales con interfaz gráfica.
- **Ubuntu Server** 🖧 → Para servidores, sin interfaz gráfica por defecto.
- **Ubuntu Core** 📡 → Para dispositivos IoT.

### 📌 Distribuciones generales (para uso diario)

Estas distribuciones son ideales para uso cotidiano y ofrecen estabilidad junto con una comunidad activa:

- **Ubuntu** – Fácil de usar, con gran comunidad y soporte.
- **Debian** – Estable y confiable, base de muchas otras distros.
- **Fedora** – Innovadora, incorpora las últimas tecnologías.
- **openSUSE** – Flexible, con herramientas avanzadas para administración de sistemas.
- **Linux Mint** – Basada en Ubuntu, enfocada en la facilidad de uso.

## 🖥️ Máquinas Virtuales

Las máquinas virtuales funcionan como un **emulador de sistemas operativos**, permitiendo probar diferentes entornos sin afectar el sistema principal.

> ⚠️ **Nota:** Si instalas una máquina virtual con **Oracle VirtualBox**, puedes configurar la cantidad de **RAM** y **CPU**, pero estos recursos solo se utilizarán mientras la máquina virtual esté encendida. Se recomienda asignar **8GB de RAM** y **4 núcleos de CPU**. En cuanto al disco, se establece un límite máximo, pero no se reserva completamente; si es necesario, se ampliará hasta el tope marcado. Se recomienda **25GB de almacenamiento**.

### 🎨 Configurar terminal Ubuntu (colores y transparencia)

Para exportar y listar la configuración actual de la terminal:

```bash
dconf dump /org/gnome/terminal/legacy/profiles:/ > terminal_config.txt
dconf list /org/gnome/terminal/legacy/profiles:/
```

Ejemplo de respuesta:

```bash
# Respuesta:
:12345_code/
12345_code/
```

Configurar la paleta de colores:

```bash
UUID="12345_code"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/palette "['#21222C', '#FF5555', '#50FA7B', '#F1FA8C', '#BD93F9', '#FF79C6', '#8BE9FD', '#F8F8F2', '#6272A4', '#FF6E6E', '#69FF94', '#FFFFA5', '#D6ACFF', '#FF92DF', '#A4FFFF', '#FFFFFF']"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/background-color "'#2A2B37'"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/foreground-color "'#F8F8F2'"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/bold-color "'#FFFFFF'"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/cursor-color "'#FF79C6'"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/use-theme-colors "false"
```

Habilitar **transparencia (90%)**:

```bash
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/use-transparent-background "true"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/background-transparency-percent "10"
```

Habilitar una fuente personalizada (**debe estar descargada**):

```bash
fc-list | grep "FiraCode"

UUID="12345_code"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/font "'FiraCode Nerd Font Mono 14'"
dconf write /org/gnome/terminal/legacy/profiles:/:$UUID/use-system-font "false"
```

Revertir cambios a la configuración predeterminada:

```bash
dconf reset -f /org/gnome/terminal/legacy/profiles:/
```

Para **añadir márgenes** en la terminal:

```bash
mkdir -p ~/.config/gtk-3.0
nano ~/.config/gtk-3.0/gtk.css
```

Contenido del archivo `gtk.css`:

```css
VteTerminal, vte-terminal {
    padding: 20px; /* Cambia el valor según el margen que desees */
    -VteTerminal-inner-border: 20px;
}
```

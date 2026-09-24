# NeyBox

Esto es NeyBox: un pequeño proyecto que empecé porque quería tener mi propia toolbox de UNIX y un shell básico, todo escrito en C y metido en un solo binario. Nada de andar dependiendo de veinte ejecutables sueltos — todo vive junto.

Lo hice pensando sobre todo en ARM64/AArch64, porque uso mucho Termux en Android y quería algo ligero que funcionara bien ahí y también en entornos GNU/Linux.

## ¿Qué trae?

Un montón de utilidades clásicas de línea de comandos, todas metidas dentro del mismo binario:

**Archivos y directorios**
`ls`, `cat`, `cp`, `mv`, `rm`, `mkdir`, `rmdir`, `touch`, `stat`, `ln`, `readlink`, `basename`, `dirname`, `realpath`

**Texto**
`head`, `tail`, `grep`, `wc`, `sort`, `uniq`, `cut`, `tr`, `tee`

**Sistema**
`uname`, `hostname`, `whoami`, `id`, `date`, `uptime`, `free`, `df`, `du`

**Procesos**
`ps`, `kill`, `sleep`

**Shell interno**
`cd`, `pwd`, `echo`, `printf`, `export`, `unset`, `env`, `history`, `which`, `type`, `true`, `false`, `clear`, `help`, `version`

También tiene pipes, redirecciones, variables de entorno e historial de comandos — lo básico para que se sienta como un shell de verdad.

## Cómo está armado por dentro

Elegí un diseño monolítico: todas las utilidades son parte del mismo ejecutable, no un montón de binarios separados. El código que se publica aquí está en `neybox.c`. (Yo trabajo también con una versión local, `main.c`, en mi propio Termux, pero lo que compartes y compila desde este repo es `neybox.c`.)

Traté de que fuera relativamente sencillo de compilar, modificar y portar — nada de arquitecturas raras de código.

## ¿Dónde funciona?

Por ahora, NeyBox está pensado y probado en **AArch64 / ARM64**, específicamente en:

- Termux / Android
- GNU/Linux ARM64
- Debian 12 (Bookworm) ARM64
- Ubuntu 23.10 ARM64, vía proot-distro

Ojo: aunque Termux y GNU/Linux comparten arquitectura (ARM64), no son intercambiables — usan entornos de ejecución, bibliotecas y rutas distintas. Un paquete hecho para uno no vas a poder usarlo tal cual en el otro.

## Cómo compilarlo

**En Termux:**
```bash
pkg install clang make
make
make PREFIX=$PREFIX install
```

**En GNU/Linux, con GCC:**
```bash
gcc -std=c11 -O2 -Wall -Wextra neybox.c -o neybox
```

**O con Clang:**
```bash
clang -std=c11 -O2 -Wall -Wextra neybox.c -o neybox
```

**Paquetes .deb:** también distribuyo NeyBox como paquete `.deb` para ARM64. Igual que con los binarios, un paquete hecho para Termux no es compatible directo con Debian o Ubuntu, aunque los tres sean ARM64.

## Repositorio APT

Este repo incluye lo necesario para mantener un repositorio APT propio, con la estructura estándar de Debian:

```
apt/
├── dists/
└── pool/
```

## ¿En qué va el proyecto?

La versión actual del paquete `.deb` es **0.3.0**, y la considero estable para usar ya.

Lo que viene:

- **0.4.0** (prevista para el 1 de noviembre de 2026): la actualización grande. Sumo soporte para ARM32, x86 y x86_64, y para las distros Arch Linux y Fedora/Red Hat, además de más utilidades y funciones.
- **0.5.0** (noviembre): más soporte de repos, para acompañar todas las arquitecturas nuevas.
- **1.0.0** (año nuevo de 2027): la que ya sentiría "completa". Vas a poder personalizar el tema con GNU nano, editando un archivo de configuración llamado `config`. Al instalar, además, se genera automáticamente un README.md con un tutorial para que no te pierdas. El soporte de WSL en esta versión sigue siendo casi nulo — si usas WSL, mejor tira de una VM por ahora.
- **1.0.1** (12 de enero): soporte medio de WSL.
- **2.0** (2030): ahí sí, soporte completo de WSL y de todas las arquitecturas/distros planeadas. También para esa fecha quiero tener lista **PlantOS**, una distro propia basada en Debian 14 "Forky", pensada para recuperar PCs viejas — empieza solo con x86/x86_64, sin entorno de escritorio por defecto (necesitarías añadir X11 o Wayland aparte si quieres uno), y con un logo de una planta. Se sumaría a proot-distro con NeyBox integrado por defecto.

## Lo que todavía no hace

Quiero ser honesta con esto: NeyBox no intenta ser un shell POSIX completo ni competir con GNU Coreutils, BusyBox o ToyBox. Por ahora:

- La expansión de comandos es limitada
- No hay job control completo
- No hay globbing completo
- No soporta `&&` ni `||`
- Las redirecciones son limitadas
- El `printf` es simplificado
- Algunas utilidades tienen implementaciones bastante básicas
- El historial no es persistente (se pierde al cerrar)
- Las capacidades pueden variar según la plataforma

Todo esto puede cambiar (y va a cambiar) en versiones futuras — está en la lista de pendientes.

## Por qué lo hago así

Lo que busco con NeyBox es simplicidad, portabilidad y bajo consumo de recursos. Código en C relativamente directo, pensado para ARM64/AArch64 y entornos Linux ligeros, con Termux como compañero de siempre.

## Licencia

BSD-2-Clause. La elegí porque es simple y permisiva: puedes usar, modificar y redistribuir el código como quieras, incluso en proyectos cerrados o comerciales — lo único que pido es que mantengas el aviso de copyright original. Si lo copias, dame el crédito.

## Autor

NeyBox Project — hecho por [Ney-Cantillo](https://github.com/Ney-Cantillo)

Repo oficial: https://github.com/Ney-Cantillo/NeyBox-Project

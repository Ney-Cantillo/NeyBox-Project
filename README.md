# NeyBox

NeyBox es una pequeña UNIX Toolbox y shell escrita en C. El proyecto reúne varias utilidades de línea de comandos en un único binario y está orientado principalmente a sistemas ARM64/AArch64 y entornos ligeros como Termux y GNU/Linux.

# Características

NeyBox incluye utilidades para:

Gestión de archivos y directorios

Manipulación de texto

Información del sistema

Procesos

Variables de entorno

Pipes y redirecciones

Comandos internos de shell

Historial de comandos

Utilidades básicas con estilo UNIX


Entre las utilidades disponibles se encuentran:

ls
cat
cp
mv
rm
mkdir
rmdir
touch
stat
ln
readlink
basename
dirname
realpath

head
tail
grep
wc
sort
uniq
cut
tr
tee

uname
hostname
whoami
id
date
uptime
free
df
du

ps
kill
sleep

cd
pwd
echo
printf
export
unset
env
history
which
type
true
false
clear
help
version

# Arquitectura

NeyBox utiliza un diseño monolítico. Las diferentes utilidades forman parte del mismo ejecutable en lugar de depender de numerosos binarios independientes.

El código principal se encuentra en:

main.c

El proyecto está escrito en C y busca mantener una implementación relativamente sencilla de compilar, modificar y portar.

# Plataformas

La arquitectura principal actualmente soportada es:

AArch64 / ARM64

NeyBox se ha probado en:

Termux / Android

GNU/Linux ARM64

Debian ARM64

Ubuntu ARM64 mediante proot-distro


Los binarios y paquetes de Termux y GNU/Linux no son necesariamente intercambiables. Aunque ambos utilizan ARM64/AArch64, utilizan diferentes entornos de ejecución, bibliotecas y rutas del sistema.

# Compilación

Termux

pkg install clang make
make
make PREFIX=$PREFIX install

GNU/Linux

Con GCC:

gcc -std=c11 -O2 -Wall -Wextra main.c -o neybox

Con Clang:

clang -std=c11 -O2 -Wall -Wextra main.c -o neybox

Paquetes .deb

NeyBox también puede distribuirse mediante paquetes .deb para ARM64.

El paquete debe corresponder al entorno de destino. Un paquete construido para Termux no debe asumirse compatible directamente con Debian o Ubuntu, aunque todos utilicen la arquitectura ARM64.

# Repositorio APT

El proyecto incluye los archivos necesarios para mantener un repositorio APT para los paquetes de NeyBox.

La estructura utiliza el formato estándar de un repositorio Debian:

apt/
├── dists/
└── pool/

# Estado del proyecto

Versión actual: 0.3.0

NeyBox 0.3.0 se considera la versión estable actual del proyecto.

La versión 0.4.0 está planificada como una expansión importante de la toolbox y del shell, con más utilidades y funciones.

# Limitaciones

NeyBox todavía no pretende implementar todas las características de un shell POSIX completo ni reemplazar herramientas maduras como GNU Coreutils, BusyBox o ToyBox.

Entre las limitaciones actuales se encuentran:

Expansión de comandos limitada

Sin job control completo

Sin globbing completo

Sin && y ||

Redirecciones limitadas

printf simplificado

Algunas utilidades tienen implementaciones básicas

El historial no es persistente

Las capacidades pueden variar según la plataforma


Estas limitaciones pueden cambiar en versiones posteriores.

# Filosofía

NeyBox busca experimentar con la idea de reunir herramientas UNIX básicas y una interfaz de shell en un único programa.

El proyecto prioriza:

Simplicidad

Portabilidad

Bajo consumo de recursos

Código C relativamente directo

ARM64/AArch64

Entornos Linux ligeros

Compatibilidad con Termux


# Licencia

Este proyecto utiliza la licencia especificada en los archivos del repositorio.

# Autor

NeyBox Project

Repositorio oficial:

https://github.com/kassandraruaortega-del/NeyBox-Project

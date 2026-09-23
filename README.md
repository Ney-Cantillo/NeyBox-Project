# NeyBox

NeyBox es una pequeña UNIX Toolbox y shell escrita en C, diseñada para proporcionar un conjunto de utilidades de línea de comandos dentro de un único binario.

El proyecto está orientado principalmente a sistemas ARM64/AArch64 y a entornos ligeros como Termux y distribuciones GNU/Linux.

## Características

NeyBox incluye utilidades para:

- Gestión de archivos y directorios
- Manipulación de texto
- Información del sistema
- Procesos
- Variables de entorno
- Redirecciones y pipes
- Comandos internos de shell
- Historial de comandos
- Utilidades básicas compatibles con el estilo UNIX

Algunas utilidades disponibles actualmente incluyen:

```text
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

Arquitectura

NeyBox utiliza un diseño monolítico: las diferentes utilidades forman parte del mismo ejecutable en lugar de depender de numerosos binarios independientes.

El código principal se encuentra actualmente en:

main.c

El proyecto utiliza C estándar y está pensado para mantenerse pequeño, compilable y relativamente fácil de modificar.

Plataformas

La arquitectura principal actualmente soportada es:

AArch64 / ARM64

NeyBox puede compilarse para diferentes entornos ARM64 siempre que dispongan de las bibliotecas y APIs necesarias.

Se ha probado en:

Termux / Android

GNU/Linux ARM64

Debian

Ubuntu mediante proot-distro


Los binarios y paquetes no son necesariamente intercambiables entre Termux y GNU/Linux, ya que utilizan diferentes entornos de ejecución y rutas del sistema.

Instalación en Termux

Para compilar desde el código fuente:

pkg install clang make
git clone https://github.com/kassandraruaortega-del/NeyBox-Project.git
cd NeyBox-Project
make

Para instalarlo:

make PREFIX=$PREFIX install

Después puede ejecutarse con:

neybox

Compilación en GNU/Linux

En una distribución GNU/Linux ARM64 con GCC:

gcc -std=c11 -O2 -Wall -Wextra main.c -o neybox

También puede utilizarse Clang:

clang -std=c11 -O2 -Wall -Wextra main.c -o neybox

Paquetes .deb

El proyecto también incluye paquetes Debian para ARM64/AArch64.

El formato de paquete depende del entorno de destino. Un paquete preparado para Termux no debe asumirse compatible directamente con Debian o Ubuntu, aunque ambos utilicen ARM64.

Estado del proyecto

Versión actual: 0.3.0

NeyBox 0.3.0 se considera una versión estable del proyecto actual.

La versión 0.4.0 está planteada como una expansión importante de la toolbox y del shell, con más utilidades y funciones.

Limitaciones actuales

NeyBox todavía no pretende implementar todas las características de un shell POSIX completo ni reemplazar herramientas maduras como GNU Coreutils, BusyBox o ToyBox.

Entre las limitaciones actuales pueden encontrarse:

Expansión de comandos limitada

Sin job control completo

Sin globbing completo

Sin && y ||

Redirecciones limitadas

printf simplificado

Algunas utilidades tienen implementaciones básicas

El historial no es persistente

Las capacidades pueden variar según la plataforma


Estas limitaciones forman parte del estado actual del proyecto y pueden cambiar en versiones posteriores.

Filosofía

NeyBox busca experimentar con la idea de reunir herramientas UNIX básicas y una interfaz de shell en un único programa pequeño.

El proyecto prioriza:

Simplicidad

Portabilidad

Código C relativamente directo

Bajo consumo de recursos

ARM64/AArch64

Entornos Linux ligeros

Compatibilidad con Termux


Licencia

Este proyecto utiliza la licencia especificada en los archivos del repositorio.

Autor

NeyBox Project

Repositorio:

https://github.com/kassandraruaortega-del/NeyBox-Project

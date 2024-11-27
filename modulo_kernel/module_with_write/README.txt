Nombre del Proyecto: Dispositivo de Carácter UCSP

Descripción:
  - Este proyecto implementa un módulo del kernel de Linux que crea un dispositivo de carácter simple.
  - Permite escribir mensajes desde el espacio de usuario y almacenarlos en el kernel para su posterior lectura.
  - Es ideal para comprender cómo interactuar con dispositivos de carácter y módulos del kernel.
  
Requisitos:
  - Linux con soporte para módulos del kernel.
  - Encabezados del kernel instalados.
  - Permisos de superusuario.

Pasos:
  1. Compilar con `make`.
  2. Cargar con `sudo insmod chardev.ko`.
  3. Crear dispositivo con `sudo mknod /dev/UCSP c <Major> 0` (ver número en `dmesg`).
  4. Cambiar permisos con `sudo chmod 666 /dev/UCSP`.

Uso:
  - Leer: `cat /dev/UCSP`
  - Escribir: `echo "mensaje" > /dev/UCSP`

Características:
  - Mensajes de hasta 80 caracteres.
  - Gestión segura de acceso concurrente.

Comandos útiles:
  - Ver mensajes del kernel: `dmesg`
  - Descargar módulo: `sudo rmmod chardev`
  - Limpiar: `make clean`



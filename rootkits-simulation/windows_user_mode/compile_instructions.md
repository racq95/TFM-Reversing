# Instrucciones de Compilación y Ejecución – Simulación de Rootkit (Windows User-Mode)

Este documento explica cómo compilar y ejecutar el archivo `rootkit_sim.c` en un entorno Windows controlado para simular técnicas clásicas de persistencia, anti-debug y ocultamiento de procesos.

## 🔧 Requisitos

- Sistema operativo: Windows 10 o 11 (64 bits)
- Entorno de prueba virtualizado (VM)
- [MinGW](https://osdn.net/projects/mingw/releases/) o TDM-GCC instalado
- Opcional: Visual Studio Code para edición

## 📥 Compilación

1. Abre la terminal de MinGW o Git Bash con acceso a `gcc`.
2. Navega a la carpeta donde se encuentra el archivo `rootkit_sim.c`.
3. Ejecuta el siguiente comando:

```bash
gcc rootkit_sim.c -o rootkit_sim.exe

# Creación de Volcado de Memoria (Memory Dump) para Análisis Forense

Este documento describe el procedimiento seguido para capturar una imagen de memoria RAM del sistema Windows comprometido, simulando un entorno con artefactos persistentes y comportamientos anómalos relacionados con técnicas usadas por rootkits modernos.

---

## 🧪 Entorno de origen

- **Sistema operativo:** Windows 10 Pro x64 (versión 21H2)
- **Entorno:** Máquina virtual VirtualBox
- **Ejecutable activo:** `infected_sample.exe` (simulación de binario con artefactos en memoria)
- **Estado:** El binario fue ejecutado y permaneció activo en memoria durante al menos 2 minutos antes del volcado.

---

## 🧰 Herramienta utilizada para captura

**Herramienta:** [DumpIt (by Comae Technologies)](https://www.comae.com/)

- Versión: 3.0
- Método: Línea de comandos
- Requiere privilegios de administrador

---

## 🧾 Procedimiento paso a paso

1. Descargar y colocar `DumpIt.exe` en el escritorio o cualquier ruta accesible.
2. Ejecutar como administrador (`clic derecho > Ejecutar como administrador`).
3. Confirmar cuando el programa lo solicite. El volcado tomará varios segundos.
4. Se genera un archivo `.raw` (o `.mem`) en la misma carpeta.  
   Ejemplo: `MEMORY_DUMP_2025-08-02_15-30.raw`

---

## 📦 Ubicación del archivo de volcado

> ⚠️ **Nota:** El volcado de memoria es confidencial y no se comparte públicamente. Se utiliza únicamente para análisis académico dentro del entorno de laboratorio.

Archivo almacenado en:  
`/memory_forensic_case/setup/dumps/MEMORY_DUMP.raw`

---

## ✅ Validación

- Se verificó que el archivo de volcado supera los 4 GB (coherente con la memoria de la VM).
- El hash MD5 fue calculado para garantizar su integridad.

```bash
CertUtil -hashfile MEMORY_DUMP.raw MD5

# Análisis de Volcado de Memoria con Volatility 3

Este documento resume los comandos utilizados en Volatility 3 para analizar el volcado de memoria capturado con DumpIt, e identificar posibles indicios de actividad anómala atribuible a rootkits en modo usuario o kernel.

---

## 🧰 Entorno de análisis

- **Sistema operativo del analista:** Kali Linux 2024.2 (x64) / Ubuntu 22.04 LTS
- **Volatility:** Volatility 3 – commit estable (agosto 2025)
- **Volcado de memoria:** `MEMORY_DUMP.raw` (extraído de VM Windows 10)

---

## 🔎 1. Identificar perfil del sistema

```bash
vol.py -f MEMORY_DUMP.raw windows.info

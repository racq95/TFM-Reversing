# Instrucciones de Compilación – Binario Simulado `infected_sample.exe`

Este documento explica cómo compilar el binario `infected_sample.c`, utilizado en el segundo caso práctico del TFM, que tiene como objetivo dejar artefactos en memoria RAM para posterior análisis con herramientas forenses.

---

## 📦 Requisitos

- Windows con MinGW instalado (gcc en PATH)
- Librerías `Ws2_32.lib` (incluidas por defecto en MinGW)
- Opcional: Visual Studio Code o editor similar

---

## 📁 Estructura esperada

```plaintext
setup/
├── infected_sample.c
├── sample_hider.c

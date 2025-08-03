# TFM-Reversing
# Simulación y Análisis de Técnicas de Rootkits en Entornos Controlados

Este repositorio acompaña el Trabajo Fin de Máster titulado:

**"Estudio de técnicas de ofuscación y persistencia utilizadas por Rootkits: Análisis de Técnicas de Ofuscación y Persistencia Utilizadas por Rootkits en Sistemas Modernos"**  
Autor: Alfonso Ricardo Carranza Quino  
Universidad Católica de Murcia (UCAM)  
Departamento de Seguridad Informática  
Fecha de entrega: 31 de agosto de 2025

---

## 🎯 Objetivo

El propósito de este repositorio es documentar y compartir el código fuente, evidencia y configuraciones utilizadas en dos simulaciones prácticas orientadas a analizar técnicas comunes utilizadas por rootkits de modo usuario, y cómo estas pueden ser detectadas mediante herramientas forenses y de monitoreo.

---

## 🧪 Estructura del Repositorio

```plaintext
rootkits-simulation/
├── windows_user_mode/          # Caso 1 – Simulación de rootkit clásico en Windows
│   ├── rootkit_sim.c
│   ├── compile_instructions.md
│   ├── evidences/
│   └── analysis_notes.md
├── memory_forensic_case/       # Caso 2 – Análisis forense de dump de memoria infectada
│   ├── setup/
│   ├── analysis/
│   └── notes.md
└── tools/                      # Guías breves de herramientas utilizadas

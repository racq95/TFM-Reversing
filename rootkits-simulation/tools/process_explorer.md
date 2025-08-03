# Process Explorer – Análisis de Procesos en Tiempo Real

**Process Explorer** es una herramienta avanzada de monitoreo de procesos desarrollada por Sysinternals/Microsoft. Permite observar detalles exhaustivos de los procesos activos en un sistema Windows, incluyendo firmas, jerarquía, descriptores, argumentos, DLLs cargadas y más.

---

## 🛠 Instalación

1. Descargar desde el sitio oficial:
   - https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer
2. Descomprimir y ejecutar `procexp64.exe` como administrador.

Versión utilizada en el TFM: 17.05 (junio 2025)

---

## 🚀 Uso básico

- Mostrar todos los procesos (`Ctrl + D`)
- Activar columnas útiles:
  - **Command Line**
  - **Verified Signer**
  - **Image Path**
- Buscar procesos (`Ctrl + F`) por nombre, path o PID
- Resaltar procesos recientes o anómalos por color

---

## 🔍 Aplicación en el caso práctico

Durante la ejecución de `rootkit_sim.exe` se observó:

- El proceso aparece con su nombre original, aunque puede modificarse su `window title` o `command line` para parecer legítimo.
- Se confirmó su carga en memoria y visibilidad en herramientas avanzadas.
- Se validó la entrada en el registro a través de la pestaña **"Image" → "Autostart Location"** (cuando está disponible).

📸 Captura de la ejecución:
- `process_explorer_name_obfuscation.png`

---

## ⚠️ Limitaciones

- No detecta procesos que hayan sido ocultados mediante manipulación de estructuras EPROCESS (técnicas de kernel-mode rootkits).
- No identifica hooks o código inyectado directamente (para eso se usa GMER o Volatility).

---

## ✅ Recomendaciones

- Siempre ejecutar como administrador para obtener visibilidad completa.
- Usar en combinación con Autoruns y GMER para validación cruzada.
- Verificar firmas digitales de procesos sospechosos.

---

## 📚 Recursos

- [Documentación oficial de Sysinternals](https://learn.microsoft.com/en-us/sysinternals/)
- [Process Explorer FAQ](https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer#faq)

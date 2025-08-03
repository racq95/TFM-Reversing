# Notas de Análisis – Simulación de Rootkit en Modo Usuario (Windows)

Este documento detalla el proceso de observación y análisis del comportamiento del binario `rootkit_sim.exe` ejecutado en un entorno Windows 10 virtualizado.

---

## 📝 1. Validación de persistencia

**Herramienta utilizada:** Autoruns / Regedit

- Ruta esperada:  
  `HKCU\Software\Microsoft\Windows\CurrentVersion\Run`

- Clave creada por el binario:  
  `SystemUpdater -> C:\Users\Usuario\Desktop\rootkit_sim.exe`

- Resultado:  
  ✅ Entrada persistente confirmada en el registro tras la ejecución.  
  ✅ Autoruns la marcó como válida sin firma digital.

📸 Captura guardada en:  
`/windows_user_mode/evidences/autoruns_persistence.png`

---

## 🧪 2. Comprobación de evasión de depuradores

**Herramienta utilizada:** x64dbg

- El binario fue abierto desde x64dbg.
- Se observó que, al iniciarse, inmediatamente llama a `IsDebuggerPresent()` y termina el proceso si retorna verdadero.
- Se verificó que sin depurador el binario continúa normalmente durante 60 segundos.

📸 Captura guardada en:  
`/windows_user_mode/evidences/debugger_detection.png`

---

## 🔍 3. Observación del proceso en ejecución

**Herramienta utilizada:** Process Explorer

- Se ejecutó `rootkit_sim.exe` manualmente.
- Aparece con el nombre de archivo original, pero si se modifica el título de ventana o el descriptor, puede simular un nombre menos sospechoso (esto puede ampliarse en versiones futuras).
- El proceso se mantiene activo durante un minuto para facilitar análisis en vivo.

📸 Captura guardada en:  
`/windows_user_mode/evidences/process_explorer_name_obfuscation.png`

---

## 💡 Observaciones adicionales

- La técnica de persistencia funciona correctamente en la clave `HKCU\Run`, que es accesible sin privilegios elevados.
- La técnica de anti-debugging es simple pero efectiva contra herramientas estándar.
- No se observaron hooks activos en GMER (porque el binario no inyecta código en funciones del sistema), lo cual es esperado en esta simulación básica.

---

## ✅ Conclusión

Este experimento demuestra cómo un binario no malicioso, con técnicas sencillas y sin necesidad de privilegios elevados, puede lograr:
- Persistencia en el sistema
- Evasión de análisis por debugging
- Actividad sigilosa a nivel de usuario

Estas capacidades, si fueran combinadas con cargas útiles reales, podrían servir como base para rootkits más sofisticados.


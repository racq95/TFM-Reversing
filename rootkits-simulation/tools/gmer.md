# GMER – Detección de Rootkits en Windows

**GMER** es una herramienta gratuita diseñada para detectar y analizar rootkits y modificaciones ocultas en sistemas Windows. Es especialmente útil para identificar hooks, drivers no firmados, procesos ocultos y manipulaciones en la tabla SSDT o IDT.

---

## 🛠 Instalación y uso básico

### 1. Descarga

- Sitio oficial: http://www.gmer.net
- Versión utilizada: 2.2.19882 (última estable compatible con Windows 10)

⚠️ GMER puede ser detectado como falso positivo por algunos antivirus. Se recomienda ejecutarlo en un entorno controlado o VM sin protección activa.

---

## 🚀 Ejecución

1. Ejecutar `gmer.exe` como administrador.
2. Al abrirse, automáticamente comenzará un escaneo de drivers, hooks y entradas ocultas.
3. Se puede personalizar el escaneo desactivando opciones innecesarias (por ejemplo, “Files”, “Registry”) si solo se desea analizar hooks o módulos.

---

## 🔍 Observaciones relevantes (caso práctico)

En la simulación con `rootkit_sim.exe`:

- **No se detectaron hooks activos**, lo cual es esperado, ya que el binario no manipula funciones del sistema ni modifica la tabla SSDT o IDT.
- GMER se utilizó principalmente para confirmar la ausencia de técnicas más agresivas de ocultamiento.

📸 Capturas asociadas:
- `gmer_clean_before.png`
- `gmer_scan_after.png`

---

## 📝 Recomendaciones

- Usar GMER como complemento a otras herramientas como Autoruns o Process Explorer.
- Comparar el escaneo antes y después de ejecutar binarios sospechosos.
- Si se detectan entradas en rojo, analizarlas manualmente antes de asumir que se trata de un rootkit.

---

## 📚 Recursos

- Sitio oficial: http://www.gmer.net
- Manual de uso avanzado (no oficial):  
  [GMER Rootkit Detection Guide (Archived)](https://www.geekstogo.com/forum/topic/246134-gmer-tutorial-how-to-run-a-scan/)


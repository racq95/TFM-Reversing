# Notas de Análisis – Caso de Estudio Forense en Memoria

Este archivo complementa el análisis forense realizado sobre el volcado de memoria obtenido desde un sistema Windows comprometido. La simulación tenía como objetivo replicar el comportamiento de rootkits modernos que priorizan el ocultamiento en memoria y la evasión de técnicas de detección convencionales.

---

## 🧩 Descripción del escenario

- Se ejecutó un binario simulado (`infected_sample.exe`) que permaneció residente en memoria, sin generar archivos persistentes en disco.
- La infección se produjo en una máquina virtual Windows 10 x64 con configuraciones estándar.
- El sistema se encontraba operativo, con conexión de red y múltiples procesos activos al momento del volcado.

---

## 🔍 Objetivos específicos del análisis

1. **Detectar artefactos que no se observan con herramientas convencionales.**
2. **Comparar lo visible en listas activas (`pslist`) con lo rastreado directamente en memoria (`psscan`).**
3. **Identificar conexiones de red activas no asociadas a procesos legítimos.**
4. **Detectar módulos del kernel cargados de forma anómala.**

---

## 🧪 Hallazgos clave

- Un proceso (`sample_hider.exe`) fue identificado por `psscan` pero no por `pslist`, lo que sugiere ocultamiento en estructuras de EPROCESS.
- Se detectó un módulo de kernel en una dirección inusual, sin nombre legible.
- Una conexión saliente por el puerto 443 no tenía proceso visible asociado, lo cual indica técnicas de evasión o proxy inverso en memoria.
- No se detectaron modificaciones en SSDT, lo que concuerda con el hecho de que la simulación no empleó rootkits a nivel kernel profundo.

---

## 📌 Lecciones aprendidas

- Las técnicas modernas de rootkits tienden a evitar modificaciones evidentes en disco y registro, favoreciendo el residir únicamente en memoria.
- Herramientas como Volatility permiten detectar estas anomalías mediante análisis comparativo y bajo nivel.
- Muchas soluciones EDR convencionales no monitorean adecuadamente los hooks de memoria ni los módulos no firmados cargados dinámicamente.

---

## ✅ Conclusión

Este estudio de caso reafirma la necesidad de contar con capacidades de análisis forense en memoria dentro de las estrategias de defensa modernas. Aunque el caso fue una simulación, las técnicas observadas reflejan tácticas empleadas por malware persistente avanzado (APT), y permiten ilustrar con claridad los retos actuales de detección en tiempo real.


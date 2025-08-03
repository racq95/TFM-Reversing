# Volatility 3 – Guía de Uso para Análisis Forense de Memoria

**Volatility 3** es un framework de análisis forense de memoria diseñado para extraer información crítica desde volcados RAM. Esta herramienta fue utilizada en el segundo caso práctico del TFM para detectar artefactos vinculados a técnicas de rootkits modernos.

---

## 🧰 Requisitos

- Python 3.8+
- SO recomendado: Linux (Kali, Ubuntu) o Windows con WSL
- Archivo de volcado de memoria (`.raw`, `.mem`, etc.)

---

## 📦 Instalación (en Linux)

```bash
git clone https://github.com/volatilityfoundation/volatility3.git
cd volatility3
pip install -r requirements.txt

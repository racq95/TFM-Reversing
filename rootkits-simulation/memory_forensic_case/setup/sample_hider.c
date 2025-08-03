// sample_hider.c
// Proceso simulado "oculto" para análisis de memoria con Volatility
// Su objetivo es permanecer activo en RAM sin generar actividad visible

#include <windows.h>

int main() {
    // Cambia el título de la consola para simular una tarea legítima
    SetConsoleTitleA("System Idle Task");

    // Simula inactividad prolongada (para permanecer en la memoria)
    Sleep(120000);  // 2 minutos
    return 0;
}

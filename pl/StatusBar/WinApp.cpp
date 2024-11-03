#include "Framework.h"
#include "MainWindow.h"


// Definicje zmiennych globalnych
HINSTANCE hAppInstance;                         // uchwyt instancji aplikacji
CMainWindow MainWindow;                         // obiekt okna glownego


//------------------------------------------------------------------------------
// Przygotowanie instancji aplikacji i wyswietlenie okna glownego
//
BOOL InitAppInstance(HINSTANCE hInstance, int nCmdShow)
{
    hAppInstance = hInstance;
    // Utworzenie glownego okna ...
    HWND hWnd = MainWindow.Create();
    if (!hWnd)
        return FALSE;
    // ... i wyswietlenie go na ekranie
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


//------------------------------------------------------------------------------
// Glowna funkcja aplikacji Windows
//
int APIENTRY wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Zaladowanie lancuchow tekstowych z zasobow
    LoadStringW(hInstance, IDS_APP_TITLE, MainWindow.szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MAINWINDOW, MainWindow.szWindowClass, MAX_LOADSTRING);
    // Zarejestrowanie glownego okna aplikacji
    // Rejestracja okresla styl i wczytuje zasoby, z ktorych korzysta okno
    MainWindow.RegisterWindowClass(hInstance);

    // Zainicjowanie instancji aplikacji
    if (!InitAppInstance(hInstance, nCmdShow))
        return FALSE;

    // Pobranie tablicy skrotow klawiaturowych
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAINWINDOW));

    MSG msg;
    // Wejscie w glowna petle obslugi komunikatow: ...
    // ...  pobieranie komunikatow z kolejki ...
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            // ... i przekazywanie ich do procedury okna glownego
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

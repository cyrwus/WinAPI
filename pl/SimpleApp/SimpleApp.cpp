#include "Framework.h"
#include "SimpleApp.h"


// Definicje zmiennych globalnych
HINSTANCE hAppInstance;                         // uchwyt instancji aplikacji

#define MAX_LOADSTRING 128

WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna glownego
WCHAR szTitle[MAX_LOADSTRING];                  // napis w pasku tytulowym


// Deklaracje funkcji zdefiniowanych dalej w tym module
ATOM RegisterWindowClass(HINSTANCE hInstance);
BOOL InitAppInstance(HINSTANCE, int);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


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
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPLEAPP, szWindowClass, MAX_LOADSTRING);
    // Zarejestrowanie glownego okna aplikacji
    // Rejestracja okresla styl i wczytuje zasoby, z ktorych korzysta okno
    RegisterWindowClass(hInstance);

    // Zainicjowanie instancji aplikacji
    if (!InitAppInstance(hInstance, nCmdShow))
        return FALSE;

    // Pobranie tablicy skrotow klawiaturowych
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEAPP));

    MSG msg;
    // Wejscie w glowna petle obslugi komunikatow, tj. ...
    // ...  pobieranie komunikatow z kolejki ...
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            // ... oddelegowanie komunikatow nieobsluzonych
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


//------------------------------------------------------------------------------
// Rejestracja klasy okna
//
ATOM RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { };
    wcex.cbSize = sizeof(WNDCLASSEX);

    // Zdefiniowanie stylu okna glownego, zaladowanie i ustawienie jego zasobow
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = hInstance;
    wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
    wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW +1);
    wcex.lpszMenuName  = MAKEINTRESOURCEW(IDC_SIMPLEAPP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    // Zarejestrowanie klasy w systemie Windows
    return RegisterClassExW(&wcex);
}


//------------------------------------------------------------------------------
// Przygotowanie instancji aplikacji i wyswietlenie okna glownego
//
BOOL InitAppInstance(HINSTANCE hInstance, int nCmdShow)
{
    hAppInstance = hInstance;
    // Utworzenie glownego okna aplikacji
    HWND hWnd = CreateWindowW(
        szWindowClass, 
        szTitle, 
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, 
        NULL, 
        hAppInstance, 
        nullptr
    );
    if (!hWnd)
        return FALSE;

    // Wyswietlenie okna w systemie
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


//------------------------------------------------------------------------------
// Procedura obslugi wiadomosci dla glownego okna aplikacji
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
        {
            // Obsluga polecen z menu aplikacji, w tym: ...
            int wmId = LOWORD(wParam);

            switch (wmId)
            {
                case IDM_ABOUT:
                    // Reakcja na wybor polecenia "Pomoc" >> "O programie",
                    // tj. aktualizacja stanu tego polecenia w menu
                    DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;

                case IDM_EXIT:
                    // Reakcja na wybor opcji menu "Plik" >> "Zakoncz",
                    // tj. zamkniecie programu
                    DestroyWindow(hWnd);
                    break;

                default:
                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }
        break;

        case WM_DESTROY:
            // Obsluga wiadomosci o zamknieciu okna
            PostQuitMessage(0);
            break;

        default:
            // Domyslna procedura obslugi wiadomosci
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}


//------------------------------------------------------------------------------
// Procedura obslugi wiadomosci dla okienka "O programie..."
//
INT_PTR CALLBACK About(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (uMsg)
    {
        case WM_INITDIALOG:
            // Obsluga komunikatu o utworzeniu okna dialogowego
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            // Obsluga polecen z okna dialogowego, tj. ...
            // ... jesli kliknieto 'OK' lub 'Anuluj' ...
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                // ... zamkniecie okna
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}

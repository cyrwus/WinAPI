#include "MainWindow.h"
#include "StatusBar.h"


// Definicje zmiennych globalnych
CStatusBar StatusBar;                           // obiekt paska statusowego


//------------------------------------------------------------------------------
// Rejestracja klasy okna
//
ATOM CMainWindow::RegisterWindowClass(HINSTANCE hInstance)
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
    wcex.hbrBackground = CreateSolidBrush(RGB(80, 80, 80));
    wcex.lpszMenuName  = MAKEINTRESOURCEW(IDC_MAINWINDOW);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    // Zarejestrowanie klasy w systemie Windows
    return RegisterClassExW(&wcex);
}


//------------------------------------------------------------------------------
// Utworzenie okna glownego
//
HWND CMainWindow::Create()
{
    // Utworzenie glownego okna aplikacji (z rozszerzona definicja stylow)
    hWindow = CreateWindowEx(
        WS_EX_LAYERED,
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
    if (hWindow != NULL) {
        // Ustawienie stopnia przezroczystosci okna
        SetLayeredWindowAttributes(hWindow, RGB(0, 0, 0), 240, LWA_ALPHA);
        // Pasek statusowy domyslnie widoczny
        StatusBar.bVisible = TRUE;
    }

    return hWindow;
}


//------------------------------------------------------------------------------
// Czynnosci po wyswietleniu okna
//
VOID CMainWindow::OnShow()
{
    // Jesli okienko paska statusowego jest poprawnie utworzone, ...
    if (StatusBar.hWindow != NULL) {
        // ... aktualizacja wyswietlanego stanu klawiszy przelacznikowych
        StatusBar.OnShow();
    }
}


//------------------------------------------------------------------------------
// Czynnosci po zmianie rozmiarow okna glownego
//
VOID CMainWindow::OnResize()
{
    // Jesli okienko paska statusowego jest poprawnie utworzone, ...
    if (StatusBar.hWindow != NULL) {
        // ... to wezwanie tej kontrolki do zmiany szerokosci ...
        SendMessage(StatusBar.hWindow, WM_SIZE, 0, 0);
        // ... i wywolanie mechanizmu regulacji sekcji
        StatusBar.OnResize();
    }
}


//------------------------------------------------------------------------------
// Czynnosci po wybraniu polecenia "Ustawienia" >> "Pasek statusowy"
//
VOID CMainWindow::OnToggleStatusBar()
{
    // Jesli okienko paska statusowego jest poprawnie utworzone, ...
    if (StatusBar.hWindow != NULL) {
        // ... to gdy pasek ma zostac pokazany, ...
        if (StatusBar.bVisible) {
            // ... wlaczenie widocznosci i aktualizacja wyswietlanego statusu
            ShowWindow(StatusBar.hWindow, SW_SHOW);
            StatusBar.OnShow();
        }
        else
            // ... w przeciwnym razie wylaczenie jego widocznosci
            ShowWindow(StatusBar.hWindow, SW_HIDE);
    }
}




//------------------------------------------------------------------------------
// Procedura obslugi komunikatow dla glownego okna aplikacji
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
            // Obsluga komunikatu o utworzeniu okna, w tym: ...
            // ... utworzenie w oknie glownym paska statusowego ...
            StatusBar.Create(hWnd);
            StatusBar.bVisible = TRUE;
            // ... i chwila oczekiwania na zakonczenie inicjalizacji
            SetTimer(hWnd, 1, USER_TIMER_MINIMUM, NULL);
            break;

        case WM_TIMER:
            // Wygaszenie timera
            KillTimer(hWnd, 1);
            // Jesli pasek statusowy jest widoczny, ...
            if (StatusBar.bVisible)
                // ... to wypisanie informacji o gotowosci
                StatusBar.SetText(IDS_STATUS_READY);

        case WM_SHOWWINDOW:
            // Obsluga komunikatu o wyswietleniu okna,
            // tj. oddelegowanie zwiazanych z tym zadan
            MainWindow.OnShow();
            break;

        case WM_SIZE:
            // Obsluga komunikatu o zmianie rozmiaru okna,
            // tj. oddelegowanie zwiazanych z tym zadan
            MainWindow.OnResize();
            break;

        case WM_KEYDOWN:
            // Obsluga wcisniecia klawiszy, w tym: ...
            switch (wParam)
            {
                case VK_NUMLOCK:
                    // Reakcja na wcisniecie klawisza 'NumLock', tj. ...
                    // ... jesli pasek statusowy jest widoczny, ...
                    if (StatusBar.bVisible)
                        // ... to aktualizacja stanu indykatora NUM
                        StatusBar.OnNumLock(GetKeyState(VK_NUMLOCK) & 0x0001);
                    break;

                case VK_CAPITAL:
                    // Reakcja na wcisniecie klawisza 'CapsLock', tj. ...
                    // ... jesli pasek statusowy jest widoczny, ...
                    if (StatusBar.bVisible)
                        // ... to aktualizacja stanu indykatora CAPS
                        StatusBar.OnCapsLock(GetKeyState(VK_CAPITAL) & 0x0001);
                    break;

                case VK_SCROLL:
                    // Reakcja na wcisniecie klawisza 'ScrollLock', tj. ...
                    // ... jesli pasek statusowy jest widoczny, ...
                    if (StatusBar.bVisible)
                        // ... to aktualizacja stanu indykatora SCROLL
                        StatusBar.OnScrollLock(GetKeyState(VK_SCROLL) & 0x0001);
                    break;

                case VK_ESCAPE:
                    // Reakcja na wcisniecie klawisza 'Escape',
                    // tj. zamkniecie programu
                    DestroyWindow(hWnd);
                    break;
            }
            break;

        case WM_COMMAND:
        {
            // Obsluga polecen z menu aplikacji, w tym: ...
            int wmId = LOWORD(wParam);

            switch (wmId)
            {
                case IDM_STATUSBAR:
                    // Reakcja na wybor polecenia "Ustawienia" >> "Pasek statusowy", tj. ...
                    // ... aktualizacja stanu tego polecenia w menu, ...
                    CheckMenuItem(GetMenu(hWnd), IDM_STATUSBAR,
                        StatusBar.bVisible ? MF_UNCHECKED : MF_CHECKED
                    );
                    // ... zarejestrowanie zmiany widocznosci paska ...
                    StatusBar.bVisible = !StatusBar.bVisible;
                    // ... i oddelegowanie zwiazanych z tym zadan
                    MainWindow.OnToggleStatusBar();
                    break;

                case IDM_EXIT:
                    // Reakcja na wybor opcji menu "Plik" >> "Zakoncz",
                    // tj. zamkniecie programu
                    DestroyWindow(hWnd);
                    break;

                default:
                    // Przekazanie innych polecen do procedury domyslnej
                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }
        break;

        case WM_DESTROY:
            // Obsluga komunikatu o zamknieciu okna
            PostQuitMessage(0);
            break;

        default:
            // Przekazanie nieobsluzonych komunikatow do procedury domyslnej
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

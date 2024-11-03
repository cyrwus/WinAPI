#include "MainWindow.h"
#include "StatusBar.h"
#include "Navigator.h"


// Definicje zmiennych globalnych
CStatusBar StatusBar;                           // obiekt paska statusowego
CNavigator Navigator;                           // obiekt nawigatora


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
        // Ustawienie stopnia przezroczystosci okna ...
        SetLayeredWindowAttributes(hWindow, RGB(0, 0, 0), 240, LWA_ALPHA);
        // ... oraz pasek statusowy domyslnie widoczny
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
// Czynnosci po wcisnieciu jednego z klawiszy nawigacyjnych
//
VOID CMainWindow::OnNaviKeyDown(WPARAM wParam)
{
    UINT uStringID = IDS_STATUS_READY;

    switch (wParam)
    {
        case VK_HOME:
            // Reakcja na wcisniety klawisz 'Home',
            // tj. powrot na start
            Navigator.GoHome();
            uStringID = IDS_STATUS_HOME;
            break;
     
        case VK_LEFT:
            if (GetKeyState(VK_CONTROL) < 0)
            {
                if (GetKeyState(VK_SHIFT) < 0) {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Ctrl + Shift + Left',
                    // tj. manewr 'Przechyl w lewo'
                    Navigator.OnTiltLeft();
                    uStringID = IDS_STATUS_TLT_LEFT;
                }
                else {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Ctrl + Left',
                    // tj. manewr 'Obrot w lewo'
                    Navigator.OnPointLeft();
                    uStringID = IDS_STATUS_ROT_LEFT;
                }
            }
            else {
                // Reakcja na wcisniety klawisz 'Left',
                // tj. manewr 'Ruch w lewo'
                Navigator.OnMoveLeft();
                uStringID = IDS_STATUS_MOV_LEFT;
            }
            break;

        case VK_UP:
            if (GetKeyState(VK_CONTROL) < 0)
            {
                if (GetKeyState(VK_SHIFT) > 0) {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Ctrl + Up',
                    // tj. manewr 'Obrot do gory'
                    Navigator.OnPointUp();
                    uStringID = IDS_STATUS_ROT_UP;
                }
            }
            else
                if (GetKeyState(VK_SHIFT) < 0) {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Shift + Up',
                    // tj. manewr 'Ruch do gory'
                    Navigator.OnLiftUp();
                    uStringID = IDS_STATUS_MOV_UP;
                }
                else {
                    // Reakcja na wcisniety klawisz 'Up',
                    // tj. manewr 'Ruch do przodu'
                    Navigator.OnMoveForward();
                    uStringID = IDS_STATUS_MOV_FORWARD;
                }
            break;

        case VK_RIGHT:
            if (GetKeyState(VK_CONTROL) < 0)
            {
                if (GetKeyState(VK_SHIFT) < 0) {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Ctrl + Shift + Right',
                    // tj. manewr 'Przechyl w prawo'
                    Navigator.OnTiltRight();
                    uStringID = IDS_STATUS_TLT_RIGHT;
                }
                else {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Ctrl + Right',
                    // tj. manewr 'Obrot w prawo'
                    Navigator.OnPointRight();
                    uStringID = IDS_STATUS_ROT_RIGHT;
                }
            }
            else {
                // Reakcja na wcisniety klawisz 'Right',
                // tj. manewr 'Ruch w prawo'
                Navigator.OnMoveRight();
                uStringID = IDS_STATUS_MOV_RIGHT;
            }
            break;

        case VK_DOWN:
            if (GetKeyState(VK_CONTROL) < 0)
            {
                if (GetKeyState(VK_SHIFT) > 0) {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Ctrl + Down',
                    // tj. manewr 'Obrot do dolu'
                    Navigator.OnPointDown();
                    uStringID = IDS_STATUS_ROT_DOWN;
                }
            }
            else
                if (GetKeyState(VK_SHIFT) < 0) {
                    // Reakcja na wcisnieta kombinacje klawiszy 'Shift + Down',
                    // tj. manewr 'Ruch do dolu'
                    Navigator.OnLowerDown();
                    uStringID = IDS_STATUS_MOV_DOWN;
                }
                else {
                    // Reakcja na wcisniety klawisz 'Down',
                    // tj. manewr 'Ruch do tylu'
                    Navigator.OnMoveBack();
                    uStringID = IDS_STATUS_MOV_BACK;
                }
            break;

        case VK_ADD:
            // Reakcja na wcisniety klawisz numeryczny '+',
            // tj. operacja 'Zoom in'
            Navigator.OnZoomIn();
            uStringID = IDS_STATUS_ZOOM_IN;
            break;

        case VK_SUBTRACT:
            // Reakcja na wcisniety klawisz numeryczny '-',
            // tj. operacja 'Zoom out'
            Navigator.OnZoomOut();
            uStringID = IDS_STATUS_ZOOM_OUT;
            break;
    }

    // Jesli okienko paska statusowego jest poprawnie utworzone i jest widoczne, ...
    if (StatusBar.hWindow != NULL && StatusBar.bVisible) {
        // ... to powiadomienie o wykonanym manewrze i aktualizacja koordynat, ...
        StatusBar.OnManeuver(uStringID);
        // ... z ustawieniem czasu prezentacji na pasku
        SetTimer(hWindow, 1, 800, NULL);
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

                case VK_HOME:
                case VK_LEFT:
                case VK_UP:
                case VK_RIGHT:
                case VK_DOWN:
                case VK_ADD:
                case VK_SUBTRACT:
                    // Reakcje na wcisniecie klawiszy nawigacyjnych,
                    // tj. oddelegowanie zwiazanych z tym zadan
                    MainWindow.OnNaviKeyDown(wParam);
                    break;

                case VK_SHIFT:
                    // Reakcja na wcisniecie klawisza 'Shift',
                    // tj. ustawienie indykatora SHFT
                    StatusBar.OnShiftKey(TRUE);
                    break;

                case VK_CONTROL:
                    // Reakcja na zwolnienie klawisza 'Ctrl',
                    // tj. ustawienie indykatora CTRL
                    StatusBar.OnCtrlKey(TRUE);
                    break;
            }
            break;

        case WM_KEYUP: {
            // Obsluga zwolnienia klawiszy, w tym: ...
            switch (wParam)
            {
                case VK_SHIFT:
                    // Reakcja na zwolnienie klawisza 'Shift',
                    // tj. wyczyszczenie indykatora SHFT
                    StatusBar.OnShiftKey(FALSE);
                    break;

                case VK_CONTROL:
                    // Reakcja na zwolnienie klawisza 'Ctrl',
                    // tj. wyczyszczenie indykatora CTRL
                    StatusBar.OnCtrlKey(FALSE);
                break;
            }
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

                case IDM_ABOUT:
                    // Reakcja na wybor opcji menu "Pomoc" >> "O programie...",
                    // tj. pokazanie okienka dialogowego
                    DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;

                case IDM_NAVIKEYS:
                    // Reakcja na wybor polecenia "Pomoc" >> "Klawisze nawigacyjne...",
                    // tj. pokazanie okienka dialogowego
                    DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_OVERVIEW), hWnd, Overview);
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




//------------------------------------------------------------------------------
// Procedura obslugi komunikatow dla okienka "O programie..."
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
            // ... jesli wybrano 'OK' lub 'Anuluj' ...
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                // ... zamkniecie okna
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}


//------------------------------------------------------------------------------
// Procedura obslugi komunikatow dla okienka "Klawisze nawigacyjne..."
//
INT_PTR CALLBACK Overview(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (uMsg)
    {
    case WM_INITDIALOG:
        // Obsluga komunikatu o utworzeniu okna dialogowego
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        // Obsluga polecen z okna dialogowego, tj. ...
        // ... jesli wybrano 'OK' lub 'Anuluj' ...
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            // ... zamkniecie okna
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

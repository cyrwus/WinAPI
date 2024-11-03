#include "StatusBar.h"
#include "Navigator.h"


//------------------------------------------------------------------------------
// Utworzenie paska statusowego (standardowej kontrolki systemu Windows)
// w przestrzeni roboczej okna nadrzednego
//
HWND CStatusBar::Create(HWND hWndParent)  
{
    // Utworzenie paska statusowego w podanym oknie nadrzednym
    hWindow = CreateWindowEx(
        0,
        STATUSCLASSNAME,
        nullptr,
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
        0, 0,
        0, 0,
        hWndParent,
        NULL,
        hAppInstance,
        nullptr
    );
    if (hWindow != NULL) {
        hParent = hWndParent;
    }

    return hWindow;
}


//------------------------------------------------------------------------------
// Czynnosci po uzyskaniu widocznosci
//
VOID CStatusBar::OnShow()
{
    // Aktualizacja indykatorow klawiszy przelacznikowych
    OnNumLock(GetKeyState(VK_NUMLOCK) & 0x0001);
    OnCapsLock(GetKeyState(VK_CAPITAL) & 0x0001);
    OnScrollLock(GetKeyState(VK_SCROLL) & 0x0001);
    // Aktualizacja koordynat w sekcji nawigacyjnej
    OnManeuver();
}


//------------------------------------------------------------------------------
// Czynnosci po zmianie szerokosci okna glownego, tj. automatyczna regulacja 
// szerokosci sekcji paska statusowego
//
VOID CStatusBar::OnResize()
{
    // Jesli pasek ma przynajmniej dwie sekcje, ...
    if (iSections > 1) {
        // ... ustalenie rozmiaru czesci roboczej okna nadrzednego ...
        RECT rcClient;
        GetClientRect(hParent, &rcClient);
        // ... i uruchomienie mechanizmu autodopasowania szerokosci sekcji
        AutoResizeSections(rcClient.right - rcClient.left);
    }
}


//------------------------------------------------------------------------------
// Czynnosci po wcisnieciu klawiszy modyfikujacych
//

VOID CStatusBar::OnShiftKey(BOOL bEnabled)
{
    // Ustawienie/zgaszenie indykatora Shift
    SetText(bEnabled ? _T("\tSHFT") : NULL, 1);
}

VOID CStatusBar::OnCtrlKey(BOOL bEnabled) {
    // Ustawienie/zgaszenie indykatora Ctrl
    SetText(bEnabled ? _T("\tCTRL") : NULL, 2);
}


//------------------------------------------------------------------------------
// Czynnosci po wcisnieciu klawiszy przelacznikowych
//

VOID CStatusBar::OnNumLock(BOOL bEnabled)
{
    // Ustawienie/zgaszenie indykatora NumLock
    SetText(bEnabled ? _T("\tNUM") : NULL, 3);
}

VOID CStatusBar::OnCapsLock(BOOL bEnabled)
{
    // Ustawienie/zgaszenie indykatora CapsLock
    SetText(bEnabled ? _T("\tCAPS") : NULL, 4);
}

VOID CStatusBar::OnScrollLock(BOOL bEnabled)
{
    // Ustawienie/zgaszenie indykatora ScrollLock
    SetText(bEnabled ? _T("\tSCRL") : NULL, 5);
}


//------------------------------------------------------------------------------
// Czynnosci po wcisnieciu klawiszy nawigacyjnych, tj. opis manewru
//
VOID CStatusBar::OnManeuver(UINT uStringID)
{
    WCHAR szText[MAX_LOADSTRING] = { };
    // Zaladowanie z zasobow podanego lancucha tekstowego opisujacego manewr, ...
    if (LoadStringW(hAppInstance, uStringID, szText, MAX_LOADSTRING))
        // ... i wypisanie go na pasku
        SetText(szText);

    // Przygotowanie lancucha tekstowego z biezacymi koordynatami ...
    swprintf(szText, 80, _T("  XYZ: %.1f, %.1f, %.1f;  Alfa: %.1f, Beta: %.1f, Gamma: %.1f"),
        Navigator.Location.x,
        Navigator.Location.y,
        Navigator.Location.z,
        toDeg(normalize(Navigator.Orientation.a)),
        toDeg(normalize(Navigator.Orientation.b)),
        toDeg(normalize(Navigator.Orientation.g))
    );
    // ... oraz wypisanie go na pasku
    SetText(szText, 6);
}


//------------------------------------------------------------------------------
// Wypisanie tekstu w sekcji paska statusowego
//
VOID CStatusBar::SetText(const WCHAR szText[], UINT uSection)
{
    // Wezwanie kontrolki do wypisania podanego tekstu we wskazanej sekcji
    SendMessage(hWindow, SB_SETTEXT, uSection, (LPARAM)szText);
}


VOID CStatusBar::SetText(const UINT uStringID, UINT uSection)
{
    WCHAR szText[MAX_LOADSTRING] = { };
    // Zaladowanie podanego lancucha tekstowego z zasobow ...
    if (LoadStringW(hAppInstance, uStringID, szText, MAX_LOADSTRING))
        // ... i wypisanie go na pasku
        SetText(szText, uSection);
}


//------------------------------------------------------------------------------
// Ustawienie szerokosci sekcji
//
VOID CStatusBar::AutoResizeSections(INT iWidth)
{
    // INFO: 
    // Sekcje moga byc stale co do szerokosci lub responsywne tj. automatycznie
    // dopasowujace sie do szerokosci okna. W tablicy iSectionWidths podaje sie 
    // konkretna szerokosc w pikselach lub -1 dla sekcji responsywnych.
    // Kazda sekcja stala pomniejsza dyspozycyjna szerokosc responsywna. Jezeli
    // zadano wiecej niz jedna sekcje responsywna, kazdej zostanie przydzielona
    // rowna czesc szerokosci dyspozycyjnej.
    // Przyjety sposob definiowania szerokosci sekcji paska jest wygodny, jednak
    // wymaga wykonania obliczen, poniewaz do kontrolki nalezy przekazac tablice
    // ze wspolrzednymi X prawych krancow sekcji (wzgledne wspolrzedne w oknie).
    // Ponizszy kod przelicza szerokosci iSectionWidths na tablice wspolrzednych
    // iSectionEnds, ktora przekazuje sie w koncu do kontrolki.

    // Ustalenie ilosci sekcji responsywnych oraz ich lacznej szerokosci ...
    int iResponsiveCount = 0;
    int iResponsiveWidth = iWidth;
    for (int i = 0; i < iSections; i++) {
        if (iSectionWidths[i] < 0)
            iResponsiveCount++;
        else
            iResponsiveWidth -= iSectionWidths[i];
    }
    if (iResponsiveWidth < 0)
        iResponsiveWidth = 0;
    else
        // ... a gdy stwierdzono przynajmniej jedna sekcje responsywna
        // wyliczenie dla niej/nich szerokosci 'automatycznej'
        if (iResponsiveCount > 0)
            iResponsiveWidth /= iResponsiveCount;

    // Alokacja tablicy i wyliczenie wartosci przekazywanych do kontrolki, tj. ...
    PINT iSectionEnds = new INT[iSections];
    // ... ustawienie wzglednej wspolrzednej X dla kranca sekcji pierwszej, ...
    iSectionEnds[0] = (iSectionWidths[0] < 0) ? iResponsiveWidth : iSectionWidths[0];
    // ... wyliczanie wartosci dla kolejnych sekcji - analogicznie jak w pierwszej, ...
    for (int i = 1; i < iSections - 1; i++)
        if (iSectionWidths[i] < 0)
            iSectionEnds[i] = iSectionEnds[i -1] + iResponsiveWidth;
        else iSectionEnds[i] = iSectionEnds[i -1] + iSectionWidths[i];
    // ... ustawienie wymagane dla ostatniej sekcji
    iSectionEnds[iSections - 1] = -1;

    // Wezwanie kontrolki do ustawienia rozmiarow sekcji
    SendMessage(hWindow, SB_SETPARTS, iSections, (LPARAM)iSectionEnds);

    // Zwolnienie tablicy liczb
    delete[] iSectionEnds;
}

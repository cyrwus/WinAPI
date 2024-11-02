#pragma once

#include "Framework.h"
#include "resource.h"


#define MAX_LOADSTRING 128


struct CStatusBar
{
public:
    HWND hParent;                               // uchwyt okna nadrzednego
    HWND hWindow;                               // uchwyt kontrolki

    BOOL bVisible;                              // widocznosc
    INT iSections = 5;                          // liczba sekcji
    INT iSectionWidths[5] = {-1,40,40,40,120};  // szerokosci sekcji

public:
    HWND Create(HWND hWndParent);

    VOID OnShow();
    VOID OnResize();

    VOID OnNumLock(BOOL bEnabled);
    VOID OnCapsLock(BOOL bEnabled);
    VOID OnScrollLock(BOOL bEnabled);

    VOID SetText(const WCHAR szText[], UINT iSection = 0);
    VOID SetText(const UINT uStringID, UINT iSection = 0);

private:
    VOID AutoResizeSections(INT iWidth);
};
extern CStatusBar StatusBar;
extern HINSTANCE hAppInstance;

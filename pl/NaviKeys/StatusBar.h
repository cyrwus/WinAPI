#pragma once

#include "Framework.h"
#include "resource.h"


#define MAX_LOADSTRING 128


class CStatusBar
{
public:
    HWND hParent;                                     // uchwyt okna nadrzednego
    HWND hWindow;                                     // uchwyt kontrolki

    BOOL bVisible;                                    // widocznosc
    INT iSections = 7;                                // liczba sekcji
    INT iSectionWidths[7] = {-1,40,40,40,40,40,400};  // szerokosci sekcji

public:
    HWND Create(HWND hWndParent);

    VOID OnShow();
    VOID OnResize();

    VOID OnShiftKey(BOOL bEnabled);
    VOID OnCtrlKey(BOOL bEnabled);
    VOID OnNumLock(BOOL bEnabled);
    VOID OnCapsLock(BOOL bEnabled);
    VOID OnScrollLock(BOOL bEnabled);
    VOID OnManeuver(UINT uStringID = IDS_STATUS_READY);

    VOID SetText(const WCHAR szText[], UINT iSection = 0);
    VOID SetText(const UINT uStringID, UINT iSection = 0);

private:
    VOID AutoResizeSections(INT iWidth);
};

extern HINSTANCE hAppInstance;

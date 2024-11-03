#pragma once

#include "Framework.h"
#include "resource.h"


#define MAX_LOADSTRING 128


class CMainWindow
{
public:
    HWND  hWindow;                         // uchwyt okna

    WCHAR szWindowClass[MAX_LOADSTRING];   // nazwa klasy okna
    WCHAR szTitle[MAX_LOADSTRING];         // napis w pasku tytulowym

public:
    ATOM RegisterWindowClass(HINSTANCE hInstance);
    HWND Create();

    VOID OnShow();
    VOID OnResize();

    VOID OnToggleStatusBar();
    VOID OnNaviKeyDown(WPARAM wParam);
};
extern CMainWindow MainWindow;
extern HINSTANCE hAppInstance;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK Overview(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK About(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

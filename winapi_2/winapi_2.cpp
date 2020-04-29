// winapi_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "winapi_2.h"

#include <string>
#include <list>
#include <tuple>
#include <utility>

#include "RectInfo.h"
#include "CommonUtil.h"

#include "ChangeDialog.h"
#include "AboutDialog.h"


#define MAX_LOADSTRING 100

#define idCheckBox 1000
#define idReset 1001
#define idClear 1002
#define idPanel 1003

HWND hwPanel;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

const int DEF_RECT_HEIGHT = 50;
const int DEF_RECT_WIGHT = 50;
const int DEF_RECT_COLOR = RGB(255, 0, 255);

#define DEF_PANEL_INDENT_LEFT 200
#define DEF_PANEL_INDENT_TOP 10
#define DEF_PANEL_INDENT_RIGHT 10
#define DEF_PANEL_INDENT_BOTTOM 10

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DiaPoc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2));

    MSG msg;
    

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 920, 720, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

RECT GetPlaneRect() {
    return GetWindowRectInParent(hwPanel);
}

bool isDrawCrossedRects(HWND hWnd) {
    return !IsDlgButtonChecked(hWnd, idCheckBox);
}

void trimRectToPanel(RECT& rect, const RECT& panel) {
    if (panel.bottom - 15 >= rect.top) {
        rect.bottom = min(rect.bottom, panel.bottom - 15);
    }
    else {
        rect.bottom = rect.top;
    }

    if (panel.right - 210 >= rect.left) {
        rect.right = min(rect.right, panel.right - 210);
    }
    else {
        rect.right = rect.left;
    }
}

void drawRect(HDC& hdc, const RECT& rect, UINT color) {
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}


void RenderSqrs(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwPanel, &ps);

    std::list<RectInfo>* rects_info;
    std::list<RectInfo> temp;

    if (isDrawCrossedRects(hWnd)) {
        rects_info = &rect_info_list();
    }
    else {
        temp = filtredRects();
        rects_info = &temp;
    }
    

    for (auto r_info : *rects_info) {
        if (!r_info.visible) {
            continue;
        }

        RECT rect = r_info.rect;
        RECT planeRect = GetPlaneRect();

        trimRectToPanel(planeRect, rect);
        drawRect(hdc, rect, r_info.col);
    }
    
    EndPaint(hwPanel, &ps);
}

bool isNotCursorInRect(const RECT& rect, int x, int y) {
    return x < rect.left || y < rect.top ||
        y > rect.bottom - DEF_RECT_HEIGHT - 5 || x > rect.right - DEF_RECT_WIGHT - 5;
}


void MainWindowOnMouseDown(
    HWND hWnd, bool isDoubleClick, int x, int y, UINT keyFlags) {
    RECT planeRect = GetWindowRectInParent(GetDlgItem(hWnd, idPanel));

    if (isNotCursorInRect(planeRect, x, y)) {
        return;
    }

    x -= planeRect.left;
    y -= planeRect.top;
    
    rect_info_list().push_front({ 
        {x,y,x+ DEF_RECT_WIGHT,y+ DEF_RECT_HEIGHT},
        DEF_RECT_COLOR
    });

    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    return FORWARD_WM_LBUTTONDOWN(hWnd, isDoubleClick, x, y, keyFlags, DefWindowProc);
}

void MainWindowOnRightMouseDown(
    HWND hWnd, bool isDoubleClick, int x, int y, UINT keyFlags) {

    RECT planeRect = GetWindowRectInParent(GetDlgItem(hWnd, idPanel));

    auto p_to_rect_info = findRectOnCord(
        x - planeRect.left,
        y - planeRect.top
    );

    if (p_to_rect_info) {
        ChangeDialogShow(hInst, hWnd, *p_to_rect_info);
        RedrawWindow(GetParent(hwPanel), NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    }
    return FORWARD_WM_RBUTTONDOWN(hWnd, isDoubleClick, x, y, keyFlags, DefWindowProc);
}


void MainWindowOnCommad(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify) {
    switch (id)
    {
    case idClear:
        rectClearRects();
        RedrawWindow(GetParent(hwPanel), NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        break;
    case idReset:
        rectResetVisibility();
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        break;
    case idCheckBox:
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        break;
    case IDM_ABOUT:
        AboutDialogShow(hInst, hWnd);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
    default:
        return FORWARD_WM_COMMAND(hWnd, id, hwndCtl, codeNotify, DefWindowProc);
    }
}

void MainWindowOnResize(HWND hWnd, UINT state, int new_x, int new_y) {
    MoveWindow(hwPanel,
        DEF_PANEL_INDENT_LEFT,
        DEF_PANEL_INDENT_TOP,
        new_x - (DEF_PANEL_INDENT_LEFT + DEF_PANEL_INDENT_RIGHT),
        new_y - (DEF_PANEL_INDENT_TOP + DEF_PANEL_INDENT_BOTTOM),
        false
    );
    return FORWARD_WM_SIZE(hWnd, state, new_x, new_y, DefWindowProc);
}

BOOL MainWindowOnCreate(HWND hWnd, LPCREATESTRUCT something) {
    CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Только не пересек. кв."),
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        10,
        10,
        160,
        20,
        hWnd,
        (HMENU)idCheckBox,
        hInst,
        NULL
    );

    CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Отчистить видимость"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        50,
        160,
        20,
        hWnd,
        (HMENU)idReset,
        hInst,
        NULL
    );

    CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Отчистить"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        90,
        160,
        20,
        hWnd,
        (HMENU)idClear,
        hInst,
        NULL
    );

    hwPanel = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
        _T("STATIC"),
        _T(""),
        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | SS_SUNKEN,
        200,
        10,
        690,
        640,
        hWnd,
        (HMENU)idPanel,
        hInst,
        (LPVOID)NULL
    );
    //return FORWARD_WM_CREATE(hWnd, something, DefWindowProc);
    return 1;
}

void MainWindowOnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);

    RenderSqrs(hWnd);

    return FORWARD_WM_PAINT(hWnd, DefWindowProc);
}

void MainWindowsOnDestroy(HWND hWnd) {
    PostQuitMessage(0);
    return FORWARD_WM_DESTROY(hWnd, DefWindowProc);
}

void MainWindowsOnActivate(HWND hWnd, UINT state, HWND hwndActDeact, BOOL fMinimized) {
    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    return FORWARD_WM_ACTIVATE(hWnd, state, hwndActDeact, fMinimized, DefWindowProc);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    HANDLE_MSG(hWnd, WM_CREATE, MainWindowOnCreate);
    HANDLE_MSG(hWnd, WM_LBUTTONDOWN, MainWindowOnMouseDown);
    HANDLE_MSG(hWnd, WM_RBUTTONDOWN, MainWindowOnRightMouseDown);
    HANDLE_MSG(hWnd, WM_SIZE, MainWindowOnResize);
    HANDLE_MSG(hWnd, WM_COMMAND, MainWindowOnCommad);
    HANDLE_MSG(hWnd, WM_PAINT, MainWindowOnPaint);
    HANDLE_MSG(hWnd, WM_DESTROY, MainWindowsOnDestroy);
    HANDLE_MSG(hWnd, WM_ACTIVATE, MainWindowsOnActivate);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



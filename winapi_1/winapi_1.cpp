// winapi_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "winapi_1.h"

#define MAX_LOADSTRING 100

#define ID_BTN1 1001
#define ID_BTN2 1002
#define ID_BTN3 1003

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

WCHAR Window1Name[] = L"Window 1";
WCHAR Window2Name[] = L"Window 2";
WCHAR Window3Name[] = L"Window 3";

ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM MyRegClassSubWindow(HINSTANCE hInstance, WCHAR className[], HCURSOR cursor);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    SubWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    MyRegClassSubWindow(hInst, Window1Name, LoadCursor(NULL, IDC_WAIT));
    MyRegClassSubWindow(hInst, Window2Name, LoadCursor(NULL, IDC_CROSS));
    MyRegClassSubWindow(hInst, Window3Name, LoadCursor(NULL, IDC_IBEAM));

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI1));

    MSG msg;

    // Цикл основного сообщения:
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



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM MyRegClassSubWindow(HINSTANCE hInstance, WCHAR className[], HCURSOR cursor) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = SubWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI1));
    wcex.hCursor = cursor;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = className;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 200, 160, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

BOOL MainWindowsOnCreate(HWND hWnd, LPCREATESTRUCT something) {
    CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Window 1"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        10,
        160,
        20,
        hWnd,
        (HMENU)ID_BTN1,
        hInst,
        NULL
    );

    CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Window 2"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        40,
        160,
        20,
        hWnd,
        (HMENU)ID_BTN2,
        hInst,
        NULL
    );

    CreateWindowEx(
        0,
        TEXT("BUTTON"),
        TEXT("Window 3"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        70,
        160,
        20,
        hWnd,
        (HMENU)ID_BTN3,
        hInst,
        NULL
    );

    return 1;
}

void CreateSubWindows(HWND hWnd, WCHAR className[], LPCWSTR name) {
    HWND new_hWnd = CreateWindowW(className, name, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 400, 400, nullptr, nullptr, hInst, nullptr);

    ShowWindow(new_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(new_hWnd);
}

void MainWindowsOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify) {
    switch (id)
    {
    case ID_BTN1: {
        CreateSubWindows(hWnd, Window1Name, L"Window 1");
    }
        break;
    case ID_BTN2: {
        CreateSubWindows(hWnd, Window2Name, L"Window 2");
    }break;
    case ID_BTN3:
        CreateSubWindows(hWnd, Window3Name, L"Window 3");
        break;
    default:
        break;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, MainWindowsOnCreate);
        HANDLE_MSG(hWnd, WM_COMMAND, MainWindowsOnCommand);
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK SubWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, message, wParam, lParam);
}


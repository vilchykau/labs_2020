#include "ChangeDialog.h"

RectInfo Info;

void __CallColorDialog(HWND hDlg);
void __DialogShowCoord(HWND hDlg);
void __ReadCoord(HWND hDlg);
void __RedrawBtn(HWND hDlg);

INT_PTR CALLBACK __ChangeDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void __CallColorDialog(HWND hDlg) {
    CHOOSECOLOR cc;		// структура стандартного диалогового окна
    static COLORREF acrCustClr[16];	// массив пользовательских цветов
    HBRUSH hbrush;		// дескриптор кисти
    static DWORD rgbCurrent;		// выбор начального цвета

    // Инициализация CHOOSECOLOR
    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = hDlg;
    cc.lpCustColors = (LPDWORD)acrCustClr;
    cc.rgbResult = Info.col;

    cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc) == TRUE)
    {
        Info.col = cc.rgbResult;
    }
}

void __DialogShowCoord(HWND hDlg) {
    SetDlgItemText(
        hDlg,
        IDC_EDIT_LEFT,
        std::to_wstring(Info.rect.left).c_str()
    );

    SetDlgItemText(
        hDlg,
        IDC_EDIT_TOP,
        std::to_wstring(Info.rect.top).c_str()
    );

    SetDlgItemText(
        hDlg,
        IDC_EDIT_RIGHT,
        std::to_wstring(Info.rect.right).c_str()
    );

    SetDlgItemText(
        hDlg,
        IDC_EDIT_BOTTOM,
        std::to_wstring(Info.rect.bottom).c_str()
    );
}


void __ReadCoord(HWND hDlg) {
    Info.rect.left =
        GetDlgItemInt(hDlg, IDC_EDIT_LEFT, nullptr, false);
    Info.rect.right =
        GetDlgItemInt(hDlg, IDC_EDIT_RIGHT, nullptr, false);
    Info.rect.top =
        GetDlgItemInt(hDlg, IDC_EDIT_TOP, nullptr, false);
    Info.rect.bottom =
        GetDlgItemInt(hDlg, IDC_EDIT_BOTTOM, nullptr, false);
}

void __RedrawBtn(HWND hDlg) {
    HWND btnHwnd = GetDlgItem(hDlg, IDC_BUTTON2);
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(btnHwnd, &ps);

    RECT rect = GetWndSize(btnHwnd);

    HBRUSH brush = CreateSolidBrush(Info.col);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);

    EndPaint(btnHwnd, &ps);
}

INT_PTR CALLBACK __ChangeDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hDlg, IDC_STATIC_LEFT, L"Коорд. лев. грани");
        SetDlgItemText(hDlg, IDC_TOP_STATIC, L"Коорд. врх. грани");
        SetDlgItemText(hDlg, IDC_RIGHT_STATIC, L"Коорд. прв. грани");
        SetDlgItemText(hDlg, IDC_BOTTOM_STATIC, L"Коорд. ниж. грани");
        __DialogShowCoord(hDlg);

        SendMessage(
            GetDlgItem(hDlg, IDC_CHECK1),
            BM_SETCHECK,
            Info.visible ? BST_CHECKED : BST_UNCHECKED,
            0
        );

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            __ReadCoord(hDlg);
            Info.visible = IsDlgButtonChecked(hDlg, IDC_CHECK1);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_BUTTON2) {
            __CallColorDialog(hDlg);
            RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE);
        }
        break;

    case WM_PAINT: {
        __RedrawBtn(hDlg);
    }break;

    }
    return (INT_PTR)FALSE;
}

void ChangeDialogShow(HINSTANCE hInst, HWND hWnd, RectInfo& info) {
    Info = info;
    int res = DialogBox(hInst, MAKEINTRESOURCE(IDD_CHANGE), hWnd, __ChangeDialogProc);
    if (res == IDOK) {
        info = Info;
    }
}
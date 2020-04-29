#include "OptionsDialog.h"

Data dialogData;

void EnableEditSize(HWND hWnd) {
    Edit_Enable(GetDlgItem(hWnd, IDC_EDIT_ROW), true);
    Edit_Enable(GetDlgItem(hWnd, IDC_EDIT_RAD), true);
}

void DisableEditSize(HWND hWnd) {
    Edit_Enable(GetDlgItem(hWnd, IDC_EDIT_ROW), false);
    Edit_Enable(GetDlgItem(hWnd, IDC_EDIT_RAD), false);
}

void OptDialogOnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify) {
    if (id == IDOK || id == IDC_BUTTON1)
    {
        dialogData.dlgSize.radius = GetDlgItemInt(hWnd, IDC_EDIT_RAD, NULL, false);
        dialogData.dlgSize.n = GetDlgItemInt(hWnd, IDC_EDIT_ROW, NULL, false);
        EndDialog(hWnd, id == IDOK);
    }
    else if (id == IDC_RADIO_FILE || id == IDC_RADIO_DIALOG) {
        if (id == IDC_RADIO_FILE) {
            Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_DIALOG), BST_UNCHECKED);
            DisableEditSize(hWnd);
            dialogData.sizeSource = SizeSource::FILE;
        }
        else {
            Button_SetCheck(GetDlgItem(hWnd, IDC_RADIO_FILE), BST_UNCHECKED);
            EnableEditSize(hWnd);
            dialogData.sizeSource = SizeSource::DIALOG;
        }
    }
}

INT_PTR CALLBACK OptDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        if (dialogData.sizeSource == SizeSource::DIALOG) {
            Button_SetCheck(GetDlgItem(hDlg, IDC_RADIO_DIALOG), BST_CHECKED);
        }
        else {
            DisableEditSize(hDlg);
            Button_SetCheck(GetDlgItem(hDlg, IDC_RADIO_FILE), BST_CHECKED);
        }

        SetDlgItemInt(hDlg, IDC_EDIT_RAD, dialogData.dlgSize.radius, false);
        SetDlgItemInt(hDlg, IDC_EDIT_ROW, dialogData.dlgSize.n, false);

        
        return (INT_PTR)TRUE;
        HANDLE_MSG(hDlg, WM_COMMAND, OptDialogOnCommand);
    case WM_DESTROY:
        EndDialog(hDlg, 0);
        break;
    }
    return (INT_PTR)FALSE;
}

Data OptionsDialogShow(HINSTANCE hInst,HWND hWnd, const Data& data)
{
    dialogData = data;
    auto res = DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, OptDialogProc);
    return res ? dialogData : data;
}

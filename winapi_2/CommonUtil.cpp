#include "CommonUtil.h"

RECT GetWndSize(HWND hWnd) {
    RECT planeRect;
    GetWindowRect(hWnd, &planeRect);
    planeRect.right -= planeRect.left;
    planeRect.left = 0;
    planeRect.bottom -= planeRect.top;
    planeRect.top = 0;
    return planeRect;
}

RECT GetWindowRectInParent(HWND hWnd)
{
    RECT planeRect;
    GetWindowRect(hWnd, &planeRect);
    MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT)&planeRect, 2);
    return planeRect;
}

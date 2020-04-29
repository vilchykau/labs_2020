#pragma once
#include <Windows.h>
#include <tuple>
#include <list>

struct RectInfo {
    RECT rect;
    UINT col;
    bool visible = true;

    bool isInRect(int x, int y) const;
    bool operator==(const RectInfo& rInfo) const;
};

bool operator==(const RECT& left, const RECT& right);

std::list<RectInfo>& rect_info_list();
void rectClearRects();
RectInfo* findRectOnCord(int x, int y);
std::list<RectInfo> filtredRects();
void rectResetVisibility();
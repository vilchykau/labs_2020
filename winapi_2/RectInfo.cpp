#include "RectInfo.h"
#include <tuple>

bool RectInfo::isInRect(int x, int y) const {
    return x >= rect.left && y >= rect.top &&
        x <= rect.right && y <= rect.bottom;
}

bool RectInfo::operator==(const RectInfo& rInfo) const {
    return std::tie(rect, col) == std::tie(rInfo.rect, rInfo.col);
}

bool operator==(const RECT& left, const RECT& right) {
    return std::tie(left.left, left.right, left.top, left.bottom) ==
        std::tie(right.left, right.right, right.top, right.bottom);
}

std::list<RectInfo> __rect_info_list;

std::list<RectInfo>& rect_info_list() {
    return __rect_info_list;
}

void rectClearRects()
{
    rect_info_list().clear();
}

RectInfo* findRectOnCord(int x, int y) {
    for (auto& rect : rect_info_list()) {
        if (rect.isInRect(x, y)) {
            return &rect;
        }
    }
    return nullptr;
}

std::list<RectInfo> filtredRects() {
    std::list<RectInfo*> black_list;
    auto start = rect_info_list().begin();
    auto end = rect_info_list().end();

    while (start != end)
    {
        auto it = rect_info_list().begin();

        for (; it != end; ++it) {
            if (it == start) {
                continue;
            }

            if (start->rect.left > it->rect.right ||
                start->rect.right < it->rect.left ||
                start->rect.top > it->rect.bottom ||
                start->rect.bottom < it->rect.top
                ) {
                continue;
            }
            else {
                black_list.push_back(&(*start));
                break;
            }
        }

        ++start;
    }

    if (black_list.size() == 0) {
        return rect_info_list();
    }

    std::list<RectInfo> result;

    start = rect_info_list().begin();
    end = rect_info_list().end();

    auto start_black = black_list.begin();
    auto end_black = black_list.end();

    while (start != end) {
        if (start_black != end_black && &(*start) == *start_black) {
            ++start_black;
        }
        else {
            result.push_back(*start);
        }
        ++start;
    }

    return result;
}

void rectResetVisibility(){
    for (auto& item : rect_info_list()) {
        item.visible = true;
    }
}


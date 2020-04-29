#pragma once

struct Size {
    int n;
    int radius;
};

enum class SizeSource
{
    FILE,
    DIALOG
};

struct Data {
    Size dlgSize;
    Size fileSize;
    int color;

    SizeSource sizeSource;

    const Size& figSize() const {
        switch (sizeSource)
        {
        case SizeSource::FILE:
            return fileSize;
        case SizeSource::DIALOG:
            return dlgSize;
        }
    }
};
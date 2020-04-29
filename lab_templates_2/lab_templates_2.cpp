#include <iostream>
//--------------
#include "Math.h"
#include "Complex.h"
//--------

constexpr complex_pair findRoots(double a, double b, double c) {
    const complex_pair D = _root(complex{ b * b, 0 } - 4 * a * c);
    return { (-b + D.first) / (2 * a), (-b + D.second) / (2 * a) };
}

int main()
{
    constexpr complex_pair ss = findRoots(1, 1, 16);
    constexpr int min_abs_root = _min(_abs(ss.first), _abs(ss.second));

    std::cout
        << ss.first << std::endl
        << ss.second << std::endl;

    int a[min_abs_root];

    std::cout << sizeof(a)/sizeof(int);

    return 0;
} 
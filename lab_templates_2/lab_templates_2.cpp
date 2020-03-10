#include <iostream>
#include <cmath>

//--------------
#include "CSqrt.h"
#include "CAbs.h"
#include "CMin.h"
//--------



template<int a, int b, int c>
struct SqRoots
{
    enum {
        x1 = (-b - cRoot<b * b - 4 * a * c>()) / (2 * a),
        x2 = (-b + cRoot<b * b - 4 * a * c>()) / (2 * a),
    };
};


int main()
{

    __asm {
        mov rax, 1
    };
    constexpr int root = cRoot<63>();
    std::cout << root << std::endl;
    using qus = SqRoots<1, -5, 6>;

    constexpr auto a = CMin(CAbs(qus::x1), CAbs(qus::x2));
   // int arr[a];

    std::cout << a;
    return 0;
}
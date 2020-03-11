#include <iostream>
#include <cmath>
#include <complex>
//--------------
#include "CSqrt.h"
#include "CAbs.h"
#include "CMin.h"
#include "Complex.h"
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
    constexpr int root = cRoot<81>();
    std::cout << root << "   " << std::endl;
    return 0;
}
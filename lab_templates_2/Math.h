#pragma once

#include <tuple>

#include "Complex.h"

constexpr double DEFAUTL_ROOT = 1e9;

constexpr double _abs(double value) {
    return value >= 0 ? value : -value;
}

constexpr double _root(double n, double st = DEFAUTL_ROOT) {
    const double min_step = n / st;
    double start = 0;
    double end = n;
    while (end - start > min_step) {
        const double mid = start + (end - start) / 2;
        const double q_mid = mid * mid;
        if (q_mid < n) {
            start = mid + min_step;
        }
        else {
            end = mid;
        }
    }
    return start;
}

constexpr double _abs(const complex& com, double st = DEFAUTL_ROOT) {
    return _root(com.rl * com.rl + com.im * com.im, st);
}

constexpr complex_pair _root(const complex& n, double st = DEFAUTL_ROOT) {
    const double t = (_root(n.rl * n.rl + 4 * n.im, st) - n.rl) / 2;
    const double d = _root(t, st);
    const double d1 = d;
    const double d2 = -d;

    const double c = _root(n.rl + d * d, st);

    const double c1 = c;
    const double c2 = -c;
    return { complex{c1, d1} , complex{c2, d2} };
}

template<typename T>
constexpr T _min(const T& a, const T& b) {
    return a < b ? a : b;
}
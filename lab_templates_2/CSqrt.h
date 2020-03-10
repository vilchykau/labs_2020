#pragma once

#define Sqr(EXPR) ((EXPR)*(EXPR))

template<int n, int start = 0, int end = n>
constexpr int cRoot() {
    if constexpr (start < end) {

        constexpr int mid_n = (start + end + 1) / 2;
        constexpr int mid = Sqr(mid_n);

        if constexpr (n < mid) {
            return cRoot<n, start, mid_n - 1>();
        }
        else {
            return cRoot<n, mid_n, end>();
        }
    }
    return end;
}


/*
#define CRoot(NUMBER) Sqrt<false, NUMBER>::value

#define MID(a, b) ((a + b) / 2)

template <bool, int number, int start = 0, int end = number>
struct Sqrt;

template <int number, int start, int end>
struct Sqrt<false, number, start, end> {
    
    using not_equals_t = std::conditional_t<(Sqr((start + end) / 2) < number), \
        Sqrt<false, number, (start + end)/2, end>, \
        Sqrt<false, number, start, (start + end)/2>>;

    using equals_t = Sqrt<true, number, start, end>;

    enum {
        value = std::conditional<start < end-1, not_equals_t, equals_t>::type::value,
    };
};

template <int number, int start, int end>
struct Sqrt<true, number, start, end> {
    enum {
        value = end,
    };
};

*/

/*

template <int number, int start, int end>
struct Sqrt<false, number, start, end> {

    using not_equals_t = std::conditional_t<(number > Sqr((start + end) / 2)), \
        Sqrt<false, number, ((start + end) / 2 + 1), end>, \
        Sqrt<false, number, start, (start + end) / 2>>;

    using equals_t = Sqrt<true, number, start, end>;

    enum {
        value = std::conditional<start == end, equals_t, not_equals_t>::type::value,
    };
};
*/
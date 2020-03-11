#pragma once

#include "CSqrt.h"
#include "CAbs.h"
#include <type_traits>

template<int a, int b = 0>
struct Complex {
	enum {
		rl = a,
		im = b,
		abs = cRoot<Sqr(a) + Sqr(b)>()
	};
};

template<typename Complex1, typename Complex2>
struct ComplexSum
{
	using value = Complex<Complex1::rl + Complex2::rl, Complex1::im + Complex2::im>;
};

template<typename Complex1, typename Complex2>
struct ComplexSub
{
	using value = Complex<Complex1::rl - Complex2::rl, Complex1::im - Complex2::im>;
};

template<int value>
struct ComplexRoot {
	using value_1 = std::conditional_t<(value >= 0), Complex<cRoot<value>()>, Complex<0, cRoot<Abs<value>::value>()>>;
	using value_2 = std::conditional_t<(value >= 0), Complex<-cRoot<value>()>, Complex<0, -cRoot<Abs<value>::value>()>>;
};


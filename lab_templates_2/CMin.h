#pragma once

#include <type_traits>

template<int _value>
struct Cont {
	enum 
	{
		value = _value,
	};
};

template<int a, int b>
struct Min
{
	enum {
		value = std::conditional_t<a < b, Cont<a>, Cont<b>>::value,
	};
};

#define CMin(a, b) Min<a, b>::value
#pragma once

#include <type_traits>

template <int value_>
struct AbsCont {
	enum {
		value = value_
	};
};

template <int value_>
struct Abs {
	enum {
		value = std::conditional_t<value_ >= 0, AbsCont<value_>, AbsCont<-value_>>::value
	};
};

#define CAbs(NUM) Abs<NUM>::value
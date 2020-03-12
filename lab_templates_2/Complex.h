#pragma once

#include <tuple>
#include <iostream>

struct complex;

using complex_pair = std::pair<complex, complex>;

struct complex {
	const double rl;
	const double im;

	constexpr complex operator+(const complex& other) const {
		return { rl + other.rl, im + other.im };
	}

	constexpr complex operator-(const complex& other) const {
		return { rl - other.rl, im - other.im };
	}

	constexpr complex operator+(double other) const {
		return { rl + other, im};
	}
	constexpr complex operator-(double other) const {
		return { rl + other, im };
	}

	constexpr complex operator/(double d) const {
		return { rl / d, im / d };
	}
};

constexpr complex operator+(double other, const complex& c) {
	return { c.rl + other, c.im };
}

constexpr complex operator-(double other, const complex& c) {
	return {other - c.rl, c.im };
}

std::ostream& operator<<(std::ostream& os, const complex& com) {
	std::cout << "c(" << com.rl << ',' << com.im << ")";
	return os;
}


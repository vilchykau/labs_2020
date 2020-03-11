#include <iostream>
#include <algorithm>
#include <string>

template<typename T = int>
struct Info{
	Info(T v,int l) :length(l), value(v){}
	Info(T v) :length(1), value(v) {}
	Info():length(0), value(0){}

	int length;
	T value;
};

auto FMaxLenPlatform(int& m) {
	m = 0;
	return Info<int>{};
}

template<typename T, typename ...Args>
auto FMaxLenPlatform(int& m, const T& t, Args... args) {
	if constexpr (std::is_arithmetic_v<T> == true) {
		auto next = FMaxLenPlatform(m, args...);
		if (next.value == t) {
			next.length++;
			m = std::max<int>(m, next.length);
			return Info<T>{t, next.length};
		}
		else {
			return Info<T>{t};
		}
	}
	else {
		FMaxLenPlatform(m, args...);
		return Info<int>{};
	}
}

template<typename T, typename ...Args>
int FMaxLenPlatform_M(const T& t, Args... args) {
	int m;
	FMaxLenPlatform(m, t, args...);
	return m;
}

int main() {
	auto max = FMaxLenPlatform_M(1, 1, 1, 1, std::string("FF"), 5, 5, 5, 6);
	std::cout << max;
	return 0;	
}
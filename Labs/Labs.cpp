#include <iostream>
#include <algorithm>
#include <string>

template<bool is_number, typename T>
struct PreValue;

template<typename T>
struct PreValue<true, T> {
	PreValue(const T& value, int len):value(value), len(len){}
	T value;
	int len;
};

template<typename T>
struct PreValue<false, T> {
	PreValue(const T& value, int len) :value(value), len(-1) {}
	int value = 0;
	int len = -1;
};

template<typename T>
decltype(auto) MakePreValue(const T& value, int len = 1) {
	return PreValue<std::is_arithmetic<T>::value, T>{value, len};
}

template<typename T>
decltype(auto) FMaxLenPlatform(const T& t) {
	return MakePreValue(t);
}

template<typename T, typename ...Args>
decltype(auto) FMaxLenPlatform(const T& t, Args... args) {
	auto next_len = FMaxLenPlatform(args...);
	auto now_container = FMaxLenPlatform(t);
	if (next_len.len != -1 && now_container.len != -1) {
		if (next_len.value == now_container.value) {
			return MakePreValue(t, next_len.len + 1);
		}
	}
	return MakePreValue(t);
}


int main() {
	std::cout << FMaxLenPlatform(1, 1, 4, std::string("FF"), 5, 6).len;
	
	return 0;	
}
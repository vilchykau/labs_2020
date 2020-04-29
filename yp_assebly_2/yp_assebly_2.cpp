
#include <iostream>
#include <ctype.h>

extern "C" int sum_arr(int* a, uint32_t n);
extern "C" int __fastcall sum_fast_call(int n, int* a);

int main()
{
    constexpr int a_size = 50;
    int* f = new int[a_size];
    for (int i = 0; i < a_size; ++i) {
        f[i] = i;
    }
    
   std::cout << sum_arr(f, a_size)  << " " << sum_fast_call(a_size, f);

    return 0;
}


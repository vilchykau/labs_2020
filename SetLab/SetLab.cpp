#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>

#include "set.hpp"
#include "TestRunner.h"

STEST(EqualTest) {
    Set<int> s1 = { 1, 2, 7, 9 };
    Set<int> s2 = { 1, 9, 7, 2 };
    ASSERT_EQ(s1, s2);
}

STEST(EraseTest) {
    {
        Set<int> s1 = { 1, 9 };
        Set<int> s2 = { 1, 9, 7, 2 };
        s2.erase(s2.find(2), s2.find(9));
        ASSERT_EQ(s1, s2);
    };
    {
        Set<int> s1 = { 1, 2 };
        Set<int> s2 = { 1, 2, 3};
        s2.erase(3);

        ASSERT_EQ(s1, s2);
    };
}

STEST(InsetTest) {
    {
        Set<int> s1 = { 1,6, 7 , 10 };
        Set<int> s2 = { 1, 7 };
        s2.insert(s2.begin(), 6);
        s2.insert(s2.begin(), 10);
        ASSERT_EQ(s1, s2);
    }
    {
        Set<int> s1 = { 1,6, 7 , 10 };
        Set<int> s2 = {};
        s2.insert(s2.begin(), 6);
        s2.insert(s2.begin(), 10);
        s2.insert(s2.begin(), 1);
        auto it = s2.insert(s2.begin(), 7);
        ASSERT_EQ(s1, s2);
 
        ASSERT_EQ(*it, *s2.find(7));
    }
	{   
        Set<int> s1 = { 1,6, 7 , 10 };
	    Set<int> s2 = { 1, 7 };
        auto set_inserter = std::inserter(s2, s2.begin());
        *set_inserter = 6;
        *set_inserter = 10;
	    ASSERT_EQ(s1, s2); 
    }
    {
        Set<int> s1 = { 1,6, 7 , 10 };
        Set<int> s2;
        auto set_inserter = std::inserter(s2, s2.begin());
        *set_inserter = 6;
        *set_inserter = 10;
        *set_inserter = 1;
        *set_inserter = 7;
        ASSERT_EQ(s1, s2);
    }
}

STEST(IteratorTest) {
    {
        Set<int> s = { 1, 3, 4, 5, 6, 7 };
        int a[] = { 1, 3, 4, 5, 6, 7 };
        size_t i = 0;
        auto beg = s.begin();
        auto end = s.end();
        while (beg != end) {
            ASSERT_EQ(*beg, a[i]);
            ++i;
            ++beg;
        }
        ASSERT_EQ((int)i, (int)(sizeof(a) / sizeof(int)));
    }
}

STEST(EmplaceTest) {
    {
        Set<int> s = { 1, 5, 10 };
        s.emplace(2, 3, 6, 11);
        Set<int> s2 = Set<int>{ 1, 2, 3, 5, 6, 10, 11 };
        ASSERT_EQ(s, s2);
    }
}


void Test() {
    TEST_FUNC(EqualTest);
    TEST_FUNC(EraseTest);
    TEST_FUNC(InsetTest);
    TEST_FUNC(IteratorTest);
    TEST_FUNC(EmplaceTest);
}


int main()
{
    Test();
    Set<int> s = { 4, 5, 6 };
    Set<int> s2 = { 3, 4, 5 };
    Set<int> s3;
    
    std::vector<int> v;

    std::cout << "{" << s << "}" << std::endl;
    std::cout << "{" << s2 << "}" << std::endl;

    std::set_intersection(s.begin(), s.end(),
        s2.begin(), s2.end(),
        std::back_inserter(v));

    for (const auto& i : s3)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int a;
    std::cin >> a;
    if (s3.find(a) != s3.end())
    {
        std::cout << "There's " << a << " the in s3.";
    }
    else
    {
        std::cout << "There is not " << a << " the in s3.";
    }

    return 0;
}

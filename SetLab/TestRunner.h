#pragma once

#include "set.hpp"
#include "set_iterator.h"

#include <string>
#include <iostream>
#include <sstream>

#define TEST_FUNC(FUN_NAME) TestFunc(FUN_NAME, #FUN_NAME)
#define ASSERT_EQ(A, B) AssertEqual(A, B, __LINE__, __FILE__)
#define STEST(Name) void Name()

template<typename Func>
void TestFunc(Func func, const std::string name) {
    try {
        func();
        std::cerr << "Test \"" << name << "\" has been completed!" << std::endl;
    }
    catch (std::exception & ex) {
        std::cerr << "Test \"" << name << "\" has been stoped: " << std::endl;
        std::cerr << ex.what() << std::endl;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
    for (const auto& value : set) {
        os << value << " ";
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, set_iterator<T> it) {
    os << *it;
    return os;
}


template<typename T, typename U>
void AssertEqual(T& t, U& u, int line, const std::string& file_name, const std::string msg = "") {
    if(t == u){

    }
    else {
        std::stringstream ss;
        ss << "Fail test on line: "
            << line 
            << ", file: " << file_name << ", " 
            << t 
            << " != " 
            << u 
            <<",  with msg: " << msg;
        throw std::invalid_argument(ss.str());
    }
}

template<typename T, typename U>
void AssertEqual(const T& t, const U& u, int line, const std::string& file_name, const std::string msg = "") {
    if (t == u) {

    }
    else {
        std::stringstream ss;
        ss << "Fail test on line: "
            << line
            << ", file: " << file_name << ", "
            << t
            << " != "
            << u
            << ",  with msg: " << msg;
        throw std::invalid_argument(ss.str());
    }
}

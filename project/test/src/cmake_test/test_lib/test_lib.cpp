#include "test_lib.h"
#include <cstdio>
#include <memory>
#include <iostream>

// 将模板变量定义移到这里
template <typename T>
constexpr T pi = T(3.1415926535897932385);

int32_t test()
{
    printf("hello test\n");
    return 0;
}

// Function to demonstrate C++14 features
void demonstrateCpp14Features()
{
    // Using auto for function return type deduction
    auto getLambda = []() {
        return [](int x) { return x * x; };
    };

    // Using the lambda
    auto square = getLambda();
    std::cout << "Square of 5: " << square(5) << std::endl;

    // Using std::make_unique (C++14 feature)
    auto ptr = std::make_unique<int>(42);
    std::cout << "Value of unique_ptr: " << *ptr << std::endl;

    // Using variable template (C++14 feature)
    std::cout << "Pi with float precision: " << pi<float> << std::endl;
    std::cout << "Pi with double precision: " << pi<double> << std::endl;

    // Using digit separators (C++14 feature)
    long long bigNumber = 1'000'000'000'000;
    std::cout << "A billion: " << bigNumber << std::endl;
}



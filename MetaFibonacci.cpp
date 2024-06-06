#include <iostream>

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

template <int N>
struct Fibonacci
{
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<1>
{
    static const int value = 1;
};

template <>
struct Fibonacci<0>
{
    static const int value = 0;
};

int main()
{
    int runtime_result = fibonacci(10);
    std::cout << runtime_result << std::endl;

    int compiletime_result = Fibonacci<10>::value;
    std::cout << compiletime_result << std::endl;
    return 0;
}
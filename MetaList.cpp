#include <iostream>

template <int... Vals>
struct IntList;

template <int H, int... T>
struct IntList<H, T...>
{
    static const int Head = H;
    using Tail = IntList<T...>;
};

template <>
struct IntList<>
{
};

template <typename IL>
struct Length
{
    static const int value = 1 + Length<typename IL::Tail>::value;
};

template <>
struct Length<IntList<>>
{
    static const int value = 0;
};

template <int H, typename IL>
struct IntCons;

template <int H, int... Vals>
struct IntCons<H, IntList<Vals...>>
{
    using type = IntList<H, Vals...>;
};

template <int H, typename IL>
struct IntConsBack;

template <int H, int... Vals>
struct IntConsBack<H, IntList<Vals...>>
{
    using type = IntList<Vals..., H>;
};

template <int N, typename IL = IntList<>>
struct Generate
{
    using type = typename IntConsBack<N - 1, typename Generate<N - 1, IL>::type>::type;
};

template <>
struct Generate<0>
{
    using type = IntList<>;
};

int main()
{
    using primes = IntList<2, 3, 5, 7, 11, 13>;

    constexpr int head = primes::Head;
    std::cout << head << std::endl;

    using odd_primes = primes::Tail;
    std::cout << odd_primes::Head << std::endl;

    constexpr size_t len = Length<primes>::value;
    std::cout << len << std::endl;

    using L1 = IntList<2, 3, 4>;
    std::cout << "Head: " << L1::Head << std::endl;

    using L2 = IntCons<1, L1>::type;
    std::cout << "Head: " << L2::Head << std::endl;

    using L3 = Generate<5>::type;
    std::cout << "Generated: " << L3::Head << " " << L3::Tail::Head << " " << L3::Tail::Tail::Head << " " << L3::Tail::Tail::Tail::Head << " "
              << L3::Tail::Tail::Tail::Tail::Head << std::endl;

    return 0;
}
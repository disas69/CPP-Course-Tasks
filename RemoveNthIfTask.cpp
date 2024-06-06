#include <iostream>
#include <algorithm>
#include <vector>

template <class Iterator, class Pred>
Iterator remove_if(Iterator p, Iterator q, Pred pred)
{
    Iterator s = find_if(p, q, pred);
    if (s == q) return q;

    Iterator out = s;
    ++s;
    return remove_copy_if(s, q, out, pred);
}

struct ElementN
{
    explicit ElementN(size_t n) : n(n), i(0) {}

    template <class T>
    bool operator()(T const& t)
    {
        return (i++ == n);
    }

    size_t n;
    size_t i;
};

int main()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    v.erase(std::remove_if(v.begin(), v.end(), ElementN(3)), v.end());

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
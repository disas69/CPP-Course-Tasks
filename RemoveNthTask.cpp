#include <iostream>
#include <algorithm>
#include <vector>

template <class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    if (std::distance(p, q) <= n)
    {
        return q;
    }

    FwdIt it = q;
    for (size_t i = 0; p != q; ++p, ++i)
    {
        if (i >= n)
        {
            FwdIt temp = p;
            p = std::rotate(p, ++temp, q);
            it = p;
        }
    }

    return it;
}

int main()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int>::iterator rIt = remove_nth(v.begin(), v.end(), 5);

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    v.erase(rIt, v.end());

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
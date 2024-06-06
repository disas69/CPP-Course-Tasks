#include <vector>
#include <list>

template <class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const&) = default;
    VectorList(VectorList&&) = default;

    VectorList& operator=(VectorList&&) = default;
    VectorList& operator=(VectorList const&) = default;
    
    template <class It>
    void append(It p, It q);  // defined outside

    bool empty() const { return size() == 0; }

    size_t size() const
    {
        size_t size = 0;
        for (const auto& vect : data_)
        {
            size += vect.size();
        }
        return size;
    }

    struct const_iterator : std::iterator<std::bidirectional_iterator_tag, const T>
    {
        typename ListT::const_iterator ListIt;
        typename VectT::const_iterator VectIt;

        const ListT* data_;

        const_iterator() = default;
        ~const_iterator() = default;
        const_iterator(const ListT* data) : data_(data), ListIt(data->cbegin()), VectIt(ListIt->cbegin()) {}
        const_iterator(const const_iterator& other) = default;
        const_iterator& operator=(const const_iterator& other) = default;

        const T& operator*() const { return *VectIt; }

        const_iterator& operator++()
        {
            if (data_ == nullptr)
            {
                return *this;
            }

            if (VectIt == --ListIt->cend())
            {
                ++ListIt;

                if (ListIt != data_->cend())
                {
                    VectIt = ListIt->cbegin();
                }
                else
                {
                    ++VectIt;
                    --ListIt;
                }
            }
            else
            {
                ++VectIt;
            }
            return *this;
        }

        const_iterator& operator--()
        {
            if (data_ == nullptr)
            {
                return *this;
            }

            if (VectIt == ListIt->cbegin())
            {
                if (ListIt != data_->cbegin())
                {
                    --ListIt;
                    VectIt = --ListIt->cend();
                }
            }
            else
            {
                --VectIt;
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const { return ListIt == other.ListIt && VectIt == other.VectIt; }

        bool operator!=(const const_iterator& other) const { return !(*this == other); }

        const T* operator->() const { return &(*VectIt); }

        const_iterator& end()
        {
            ListIt = --data_->cend();
            VectIt = ListIt->cend();
            return *this;
        }
    };

    const_iterator begin() const
    {
        if (empty())
        {
            return const_iterator();
        }

        return const_iterator(&data_);
    }

    const_iterator end() const
    {
        if (empty())
        {
            return const_iterator();
        }

        return const_iterator(&data_).end();
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_reverse_iterator rbegin() const
    {
        if (empty())
        {
            return const_reverse_iterator();
        }

        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const
    {
        if (empty())
        {
            return const_reverse_iterator();
        }

        return const_reverse_iterator(begin());
    }

private:
    ListT data_;
};
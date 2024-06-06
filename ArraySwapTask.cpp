template <class T>
struct Array
{
    explicit Array(size_t size = 0);
    Array(Array const& a);
    Array& operator=(Array const& a);
    ~Array();

    size_t size() const;
    T& operator[](size_t i);
    T const& operator[](size_t i) const;

    void Swap(Array& a)
    {
        size_t tempSize = size_;
        size_ = a.size_;
        a.size_ = tempSize;

        T* tempData = data_;
        data_ = a.data_;
        a.data_ = tempData;
    }

    Array(Array&& a) noexcept
    {
        Swap(a);
    }

    Array& operator=(Array&& a) noexcept
    {
        Swap(a);
        return *this;
    }

private:
    size_t size_;
    T* data_;
};
#include <memory>

template<typename T, typename Allocator = std::allocator<T> >
class ezoe_vector
{
public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const pointer;
    using reference       = value_type&;
    using const_reference = const value_type&;

    using allocator_type  = Allocator;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    // 先頭の要素へのポインター
    pointer first;
    // 最後の要素の1つ前方のポインター
    pointer last;
    // 確保したストレージの終端
    pointer reserved_last;
    // アロケーターの値
    allocator_type alloc;

public:
    iterator begin() noexcept { return first; }
    iterator end() noexcept { return last; }
    iterator begin() const noexcept { return first; }
    iterator end() const noexcept { return last; }

    reverse_iterator rbegin() noexcept { return reverse_iterator { last }; }
    reverse_iterator rend() noexcept { return reverse_iterator { first }; }

    size_type size() const noexcept { return end() - begin(); }
    bool      empty() const noexcept { return begin() == end(); }
    size_type capacity() const noexcept { return reserved_last - first; }

    reference       operator[](size_type i) { return first[i]; }
    const_reference operator[](size_type i) const { return first[i]; }

    reference at(size_type i) {
        if (i >= size())
            throw std::out_of_range("index is out of range.");
        return first[i];
    }
    const_reference at(size_type i) const {
        if (i >= size())
            throw std::out_of_range("index is out of range.");
        return first[i];
    }

    pointer       data() noexcept { return first; }
    const_pointer data() const noexcept { return first; }

    reference       front() { return first; }
    const_reference front() const { return first; }
    reference       back() { return last - 1; }
    const_reference back() const { return last - 1; }

    ezoe_vector() {}
};

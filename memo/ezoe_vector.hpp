#include <memory>
#include <iostream>

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
    ezoe_vector(const allocator_type& alloc) noexcept : alloc(alloc) {}

    // ezoe_vector(size_type size, const allocator_type& alloc =
    // allocator_type())
    //     : ezoe_vector(alloc) {}
    // ezoe_vector(size_type size, const_reference value,
    //     const allocator_type& alloc = allocator_type())
    //     : ezoe_vector(alloc) {}

    ezoe_vector(size_type size, const allocator_type& alloc)
        : ezoe_vector(alloc) {
        std::cout << "aa" << std::endl;
        resize(size);
    }
    ezoe_vector(
        size_type size, const_reference value, const allocator_type& alloc)
        : ezoe_vector(alloc) {
        std::cout << "bb" << std::endl;
        resize(size, value);
    }

private:
    using traits = std::allocator_traits<allocator_type>;

    pointer allocate(size_type n) { return traits::allocate(alloc, n); }
    void    deallocate() { traits::deallocate(alloc, first, capacity()); }
    void    destroy(pointer ptr) { traits::destroy(alloc, ptr); }
    void    destroy_until(reverse_iterator rend) {
        for (auto riter = rbegin(); riter != rend; ++riter, --last) {
            destroy(&*riter);
        }
    }

public:
    void construct(pointer ptr) { traits::construct(alloc, ptr); }
    void construct(pointer ptr, const_reference value) {
        traits::construct(alloc, ptr, value);
    }
    void construct(pointer ptr, value_type&& value) {
        traits::construct(alloc, ptr, std::move(value));
    }
    void clear() noexcept { destroy_until(rend()); }
    ~ezoe_vector() {
        clear();
        deallocate();
    }
    void reserve(size_type sz) {
        if (sz <= capacity())
            return;
        auto ptr          = allocate(sz);
        auto old_first    = first;
        auto old_last     = last;
        auto old_capacity = capacity();
        first             = ptr;
        last              = first;
        reserved_last     = first + sz;

        // std::scope_exit e([&] { // TODO [&] って何？
        //     traits::deallocate(alloc, old_first, old_capacity);
        // });
        for (auto old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last) {
            construct(last, std::move(*old_iter));
        }
        for (auto riter = reverse_iterator(old_last),
                  rend  = reverse_iterator(old_first);
             riter != rend; ++riter)
        {
            destroy(&*riter);
        }
    }
    void resize(size_type sz) {
        if (sz < size()) {
            auto diff = size() - sz;
            destroy_until(rbegin() + diff);
            last = first + sz;
        } else if (sz > size()) {
            reserve(sz);
            for (; last != reserved_last; ++last) {
                construct(last);
            }
        }
    }
};

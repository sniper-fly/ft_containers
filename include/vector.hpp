#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
    template<class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        typedef T                                        value_type;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        //// 一旦仮おき
        typedef int  hoge;
        typedef hoge iterator;
        typedef hoge const_iterator;
        typedef hoge reverse_iterator;
        typedef hoge const_reverse_iterator;
        typedef hoge difference_type;
        ////

        typedef size_t size_type;

    private:
        vector(); // for canonical form

    public:
        explicit vector(const allocator_type& alloc = allocator_type());
        explicit vector(size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type());
        template<class InputIterator>
        vector(InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type());
        vector(const vector& x);

        ~vector();

        vector& operator=(const vector& x);

        iterator               begin();
        const_iterator         begin() const;
        iterator               end();
        const_iterator         end() const;
        reverse_iterator       rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator       rend();
        const_reverse_iterator rend() const;

        size_type size() const;
        size_type max_size() const;
        void      resize(size_type n, value_type val = value_type());
        size_type capacity() const;
        bool      empty() const;
        void      reserve(size_type n);

        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;
        reference       at(size_type n);
        const_reference at(size_type n) const;
        reference       front();
        const_reference front() const;
        reference       back();
        const_reference back() const;

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last);
        void assign(size_type n, const T& val);
    };
} // namespace ft
#endif

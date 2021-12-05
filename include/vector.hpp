#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "macro.hpp"
#include <memory>
#include <iterator>
#include "vector_iterator.hpp"
#include <stdexcept>
#include <sstream>

// TODO
namespace forbidden = std;

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

        typedef vector_iterator<pointer>              iterator;
        typedef vector_iterator<const_pointer>        const_iterator;
        typedef forbidden::reverse_iterator<iterator> reverse_iterator;
        typedef forbidden::reverse_iterator<const_pointer>
                                                     const_reverse_iterator;
        typedef forbidden::iterator_traits<iterator> difference_type;
        typedef size_t                               size_type;

    private:
        pointer        _first; // 先頭の要素へのポインター
        pointer        _last;  // 最後の要素の1つ前方のポインター
        pointer        _reserved_last; // 確保したストレージの終端
        allocator_type _alloc;         // アロケーターの値

    public:
        /* default */
        explicit vector(const allocator_type& alloc = allocator_type())
            : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {}
        /* fill */
        explicit vector(size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type())
            : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {
            _first         = _alloc.allocate(n);
            _last          = _first + n;
            _reserved_last = _last;
            rep(n) { _alloc.construct(_first + i, val); }
        } /* range */
        // template<class InputIterator>
        // vector(InputIterator first, InputIterator last,
        //     const allocator_type& alloc = allocator_type());
        /* copy */
        vector(const vector& x)
            : _first(NULL), _last(NULL), _reserved_last(NULL),
              _alloc(x._alloc) {
            *this = x;
        }

        ~vector() {
            clear();
            _alloc.deallocate(_first, capacity());
        }

        vector& operator=(const vector& x) {
            this->~vector();
            _first         = _alloc.allocate(x.size());
            _last          = _first + x.size();
            _reserved_last = _first + x.capacity();
            rep(x.size()) { _alloc.construct(_first + i, x[i]); }
            return *this;
        }

        // XXX iterators
        iterator               begin() { return iterator(_first); }
        const_iterator         begin() const { return const_iterator(_first); }
        iterator               end() { return iterator(_last); }
        const_iterator         end() const { return const_iterator(_last); }
        reverse_iterator       rbegin() {}
        const_reverse_iterator rbegin() const {}
        reverse_iterator       rend() {}
        const_reverse_iterator rend() const {}

        // XXX capacity
        size_type size() const { return end() - begin(); };
        size_type max_size() const;
        void      resize(size_type n, value_type val = value_type());
        size_type capacity() const { return _reserved_last - _first; }
        bool      empty() const { return begin() == end(); }
        void      reserve(size_type n) {
            // max_sizeより大きかったら
            //'std::length_error' what(): vector::reserve
            //上記のエラーを吐く
            if (n <= capacity()) {
                return;
            }
            pointer         new_first = _alloc.allocate(n);
            const size_type len       = size();
            rep(len) {
                _alloc.construct(new_first + i, _first[i]);
                _alloc.destroy(_first + i);
            }
            _alloc.deallocate(_first, capacity());
            _first         = new_first;
            _last          = _first + len;
            _reserved_last = _first + n;
        }

        // XXX element access
        reference       operator[](size_type n) { return _first[n]; }
        const_reference operator[](size_type n) const { return _first[n]; }
        reference       at(size_type n) {
            check_range(n);
            return _first[n];
        }
        const_reference at(size_type n) const {
            check_range(n);
            return _first[n];
        }
        reference       front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference       back() { return *(end() - 1); }
        const_reference back() const { return *(end() - 1); }

        // XXX modifiers
        template<class InputIterator>
        void assign(InputIterator first, InputIterator last);
        void assign(size_type n, const T& val) {
            clear();
            if (n > capacity()) {
                reserve(n);
            }
            // val で n個分埋める
            _last = _first + n;
            rep(n) { _alloc.construct(_first + i, val); }
        }
        void push_back(const value_type& val) {
            if (size() == capacity()) {
                reserve(capacity() ? capacity() * 2 : 10);
            }
            _alloc.construct(_last, val);
            ++_last;
        }
        void pop_back() {
            _alloc.destroy(&_first[size() - 1]);
            --_last;
        }
        iterator insert(iterator position, const value_type& val);
        void     insert(iterator position, size_type n, const value_type& val);
        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void     swap(vector& x) {
            pointer tmp_first         = _first;
            pointer tmp_last          = _last;
            pointer tmp_reserved_last = _reserved_last;

            _first         = x._first;
            _last          = x._last;
            _reserved_last = x._reserved_last;

            x._first         = tmp_first;
            x._last          = tmp_last;
            x._reserved_last = tmp_reserved_last;
        }
        void clear() {
            size_type len = size();
            rep(len) { pop_back(); }
        }

        // XXX allocator
        allocator_type get_allocator() const;

    private:
        void check_range(size_type n) {
            if (size() <= n) {
                std::string err_msg =
                    "vector::check_range: n (which is " + num2str(n) +
                    ") >= this->size() (which is " + num2str(size()) + ")";
                throw std::out_of_range(err_msg);
            }
        }
        template<typename num>
        std::string num2str(num number) {
            std::ostringstream ss;
            ss << number;
            return ss.str();
        }
        /////////// debug func /////////////////////
        ////////////////////////////////////////////
    };

    // vector: Non-member functions
    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        rep(lhs.size()) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return NOT(lhs == rhs);
    }
    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {}
    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {}
    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {}
    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {}
    template<class T, class Alloc>
    void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {}
} // namespace ft
#endif

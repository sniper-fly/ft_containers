#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "macro.hpp"
#include <memory>
#include <iterator>
#include "vector_iterator.hpp"
#include <stdexcept>
#include <sstream>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

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

        typedef vector_iterator<pointer>             iterator;
        typedef vector_iterator<const_pointer>       const_iterator;
        typedef ft::reverse_iterator<iterator>       reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type
                       difference_type;
        typedef size_t size_type;

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
        }
        /* range */
        template<class InputIterator>
        vector(typename ft::enable_if<! ft::is_integral<InputIterator>::value,
                   InputIterator>::type first,
            InputIterator last, const allocator_type& alloc = allocator_type())
            : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {
            reserve(std::distance(first, last));
            insert(begin(), first, last);
        }
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
        iterator       begin() { return iterator(_first); }
        const_iterator begin() const { return const_iterator(_first); }
        iterator       end() { return iterator(_last); }
        const_iterator end() const { return const_iterator(_last); }

        reverse_iterator rbegin() { return reverse_iterator(iterator(_last)); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(const_iterator(_last));
        }
        reverse_iterator rend() { return reverse_iterator(iterator(_first)); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(const_iterator(_first));
        }

        // XXX capacity
        size_type size() const { return end() - begin(); };
        size_type max_size() const { return _alloc.max_size(); }
        void      resize(size_type n, value_type val = value_type()) {
            if (n < size()) {
                const size_type remove_amount = size() - n;
                rep(remove_amount) { pop_back(); }
                return;
            }
            const size_type fill_amount = n - size();
            if (capacity() < n) {
                reserve(n);
            }
            rep(fill_amount) { push_back(val); }
        }
        size_type capacity() const { return _reserved_last - _first; }
        bool      empty() const { return begin() == end(); }
        void      reserve(size_type n) {
            if (n > max_size()) {
                throw std::length_error("vector::reserve");
            }
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
        void assign(
            typename ft::enable_if<! ft::is_integral<InputIterator>::value,
                InputIterator>::type first,
            InputIterator            last) {
            clear();
            insert(begin(), first, last);
        }

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
            reserve(recalc_cap_if_over(size() + 1));
            _alloc.construct(_last, val);
            ++_last;
        }
        void pop_back() {
            _alloc.destroy(&_first[size() - 1]);
            --_last;
        }
        iterator insert(iterator position, const value_type& val) {
            const difference_type offset = position - begin();
            insert(position, 1, val);
            return begin() + offset;
        }
        void insert(iterator position, size_type n, const value_type& val) {
            // positionはreserveの後だと使えない可能性がある
            const size_type offset      = position - begin();
            const size_type shift_times = end() - position;
            reserve(recalc_cap_if_over(size() + n));
            shift_to_right(shift_times, n);
            rep(n) {
                if (i < size()) {
                    _first[offset + i] = val;
                } else {
                    _alloc.construct(&(_first[offset + i]), val);
                }
            }
            _last += n;
        }
        template<class InputIterator>
        void insert(iterator         position,
            typename ft::enable_if<! ft::is_integral<InputIterator>::value,
                InputIterator>::type first,
            InputIterator            last) {
            if (first > last) {
                throw std::length_error("vector:insert");
            }
            if (first == last) {
                return;
            }
            const difference_type offset        = position - begin();
            const difference_type shift_times   = end() - position;
            const difference_type distance      = std::distance(first, last);
            const size_type       num_to_insert = distance + 1;
            reserve(recalc_cap_if_over(size() + num_to_insert));
            shift_to_right(shift_times, num_to_insert);
            rep(num_to_insert) {
                if (offset + i < size()) {
                    _first[offset + i] = *first;
                } else {
                    _alloc.construct(&(_first[offset + i]), *first);
                }
                // ここも空の配列が来たときなどは初期化を想定しないと駄目
                ++first;
            }
            _last += distance;
        }
        iterator erase(iterator position) {
            return erase(position, position + 1);
        }
        iterator erase(iterator first, iterator last) {
            if (first > last) {
                throw std::length_error("vector:erase");
            }
            if (first == last) {
                return first;
            }
            const difference_type distance    = last - first;
            iterator              delete_head = first;
            while (delete_head != last) {
                _alloc.destroy(&(*delete_head));
                ++delete_head;
            }
            iterator concat_head = first;
            while (concat_head + distance != end()) {
                *concat_head = *(concat_head + distance);
                ++concat_head;
            }
            _alloc.destroy(&(*concat_head));
            _last -= distance;
            return first;
        }
        void swap(vector& x) {
            swap_ptr(this->_first, x._first);
            swap_ptr(this->_last, x._last);
            swap_ptr(this->_reserved_last, x._reserved_last);
        }
        void clear() {
            size_type len = size();
            rep(len) { pop_back(); }
        }

        // XXX allocator
        allocator_type get_allocator() const { return _alloc; }

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
        size_type recalc_cap_if_over(size_type new_size) {
            if (new_size <= capacity()) {
                return capacity();
            }
            if (new_size <= 1) {
                return 10;
            }
            return std::min(new_size * 2, max_size());
        }
        void shift_to_right(size_type times, size_type num_to_insert) {
            const size_type new_tail = size() + num_to_insert - 1;
            const size_type old_tail = size() - 1;
            rep(times) {
                if (new_tail - i < size()) {
                    _first[new_tail - i] = _first[old_tail - i];
                } else {
                    _alloc.construct(
                        &(_first[new_tail - i]), _first[old_tail - i]);
                }
            }
        }
        void swap_ptr(pointer& a, pointer& b) {
            pointer tmp_a = a;
            a             = b;
            b             = tmp_a;
        }
    };

    // vector: Non-member functions
    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return ! (lhs == rhs);
    }
    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return ft::lexicographical_compare(
            lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return operator>=(rhs, lhs);
    }
    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return operator<(rhs, lhs);
    }
    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return ! (operator<(lhs, rhs));
    }
    template<class T, class Alloc>
    void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
        x.swap(y);
    }
} // namespace ft
#endif

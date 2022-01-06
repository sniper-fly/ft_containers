#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cstddef>

namespace ft
{
    template<class Iterator>
    class iterator_traits
    {
    public:
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    class iterator_traits<T*>
    {
    public:
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<class T>
    class iterator_traits<const T*>
    {
    public:
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<class Iterator>
    class reverse_iterator
        : public std::iterator<
              typename ft::iterator_traits<Iterator>::iterator_category,
              typename ft::iterator_traits<Iterator>::value_type,
              typename ft::iterator_traits<Iterator>::difference_type,
              typename ft::iterator_traits<Iterator>::pointer,
              typename ft::iterator_traits<Iterator>::reference>
    {
    public:
        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category
            iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type
                                                                difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;

    private:
        iterator_type current_elem;

    public:
        reverse_iterator() : current_elem() {}
        explicit reverse_iterator(iterator_type it) : current_elem(it) {}
        template<class Iter>
        reverse_iterator(const reverse_iterator<Iter>& rev_it) {
            current_elem = rev_it.base();
        }
        iterator_type base() const { return current_elem; }
        reference     operator*() const {
            iterator_type refering_value = current_elem;
            --refering_value;
            return *refering_value;
        }
        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(current_elem - n);
        }
        reverse_iterator& operator++() {
            --current_elem;
            return *this;
        }
        reverse_iterator operator++(int) {
            reverse_iterator temp = *this;
            ++(*this);
            return temp;
        }
        reverse_iterator& operator+=(difference_type n) {
            current_elem -= n;
            return *this;
        }
        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current_elem + n);
        }
        reverse_iterator& operator--() {
            ++current_elem;
            return *this;
        }
        reverse_iterator operator--(int) {
            reverse_iterator temp = *this;
            --(*this);
            return temp;
        }
        reverse_iterator operator-=(difference_type n) {
            current_elem += n;
            return *this;
        }
        pointer   operator->() const { return &(operator*()); }
        reference operator[](difference_type n) const {
            return *(current_elem - n - 1);
        }
    };
    template<class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>&             rhs) {
        return lhs.base() == rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>&             rhs) {
        return lhs.base() != rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>&            rhs) {
        return lhs.base() < rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>&             rhs) {
        return lhs.base() <= rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>&            rhs) {
        return lhs.base() > rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>&             rhs) {
        return lhs.base() >= rhs.base();
    }
} // namespace ft

#endif

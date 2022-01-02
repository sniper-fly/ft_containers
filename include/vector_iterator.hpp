#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>

namespace forbidden = std;

namespace ft
{
    template<class T>
    class vector_iterator
        : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        // 一旦std::iterator_traitsで仮おき、あとで自作する
        typedef T iterator_type;
        typedef typename forbidden::iterator_traits<T>::iterator_category
            iterator_category;

        typedef typename forbidden::iterator_traits<T>::value_type value_type;
        typedef typename forbidden::iterator_traits<T>::difference_type
                                                                difference_type;
        typedef typename forbidden::iterator_traits<T>::pointer pointer;
        typedef typename forbidden::iterator_traits<T>::reference reference;
        //

        vector_iterator() : current_elem(NULL) {}
        explicit vector_iterator(iterator_type it) : current_elem(it) {}
        template<class Iter>
        vector_iterator(const vector_iterator<Iter>& it) {
            *this = it;
        }
        template<class Iter>
        vector_iterator& operator=(const vector_iterator<Iter>& other) {
            current_elem = other.base();
            return *this;
        }

        iterator_type    base() const { return current_elem; }
        reference        operator*() const { return *current_elem; }
        pointer          operator->() const { return current_elem; }
        vector_iterator& operator++() {
            current_elem++;
            return *this;
        }
        vector_iterator operator++(int) {
            vector_iterator tmp = *this;
            current_elem++;
            return tmp;
        }
        vector_iterator& operator--() {
            current_elem--;
            return *this;
        }
        vector_iterator operator--(int) {
            vector_iterator tmp = *this;
            current_elem--;
            return tmp;
        }
        vector_iterator operator+(difference_type n) const {
            return vector_iterator(current_elem + n);
        }
        vector_iterator operator-(difference_type n) const {
            return vector_iterator(current_elem - n);
        }
        vector_iterator& operator+=(difference_type n) {
            current_elem += n;
            return *this;
        }
        vector_iterator& operator-=(difference_type n) {
            current_elem -= n;
            return *this;
        }
        reference operator[](difference_type n) const {
            return *(current_elem + n);
        }

    private:
        iterator_type current_elem;
    };

    template<class Iterator1, class Iterator2>
    bool operator==(const vector_iterator<Iterator1>& lhs,
        const vector_iterator<Iterator2>&             rhs) {
        return lhs.base() == rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator!=(const vector_iterator<Iterator1>& lhs,
        const vector_iterator<Iterator2>&             rhs) {
        return lhs.base() != rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator<(const vector_iterator<Iterator1>& lhs,
        const vector_iterator<Iterator2>&            rhs) {
        return lhs.base() < rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator<=(const vector_iterator<Iterator1>& lhs,
        const vector_iterator<Iterator2>&             rhs) {
        return lhs.base() <= rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator>(const vector_iterator<Iterator1>& lhs,
        const vector_iterator<Iterator2>&            rhs) {
        return lhs.base() > rhs.base();
    }
    template<class Iterator1, class Iterator2>
    bool operator>=(const vector_iterator<Iterator1>& lhs,
        const vector_iterator<Iterator2>&             rhs) {
        return lhs.base() >= rhs.base();
    }
    template<class Iterator>
    vector_iterator<Iterator> operator+(
        typename vector_iterator<Iterator>::difference_type n,
        const vector_iterator<Iterator>&                    it) {
        return vector_iterator<Iterator>(it.base() + n);
    }
    template<class Iterator>
    typename vector_iterator<Iterator>::difference_type operator-(
        const vector_iterator<Iterator>& lhs,
        const vector_iterator<Iterator>& rhs) {
        return lhs.base() - rhs.base();
    }
} // namespace ft

#endif

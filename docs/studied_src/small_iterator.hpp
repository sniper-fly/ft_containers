#ifndef SMALL_ITERATOR_HPP
#define SMALL_ITERATOR_HPP
#include <string>
#include <vector>

class const_line_iterator
    : public std::iterator<std::forward_iterator_tag, std::string>
{
    typedef std::vector<char>::const_iterator char_iterator;
    char_iterator m_begin; //  行先頭へのイテレータ
    char_iterator m_next;  //  行末の次の文字
    char_iterator m_end;   //  行全体の末尾の次

public:
    const_line_iterator(char_iterator itr, char_iterator end)
        : m_begin(itr), m_end(end) {
        set_next();
    }

public:
    /*const*/ std::string operator*() const {
        return std::string(m_begin, m_next);
    }
    const_line_iterator& operator++() {
        if (m_begin != m_end) {
            m_begin = m_next;
            set_next();
        }
        return *this;
    }
    bool operator==(const const_line_iterator& x) const {
        return m_begin == x.m_begin;
    }
    bool operator!=(const const_line_iterator& x) const {
        return m_begin != x.m_begin;
    }

protected:
    void set_next() {
        char ch = '\0'; //  ひとつ前の文字
        for (m_next = m_begin;;) {
            if (m_next == m_end || ch == '\n')
                return;
            if (ch == '\r') {
                if (*m_next == '\n')
                    ++m_next;
                return;
            }
            ch = *m_next;
            ++m_next;
        }
    }
};

#endif

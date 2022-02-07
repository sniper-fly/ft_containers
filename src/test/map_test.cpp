#include "map.hpp"
#include "macro.hpp"
#include "gtest/gtest.h"

namespace
{
    class my_class
    {
    public:
        my_class() {}
        my_class(int hoge, double fuga, std::string foo)
            : hoge(hoge), fuga(fuga), foo(foo) {}
        ~my_class() {
            if (should_output_destructor_msg) {
                std::cout << foo;
            }
        }

        static bool should_output_destructor_msg;

        int         hoge;
        double      fuga;
        std::string foo;

        my_class& operator=(const my_class& x) {
            hoge = x.hoge;
            fuga = x.fuga;
            foo  = x.foo;
            return *this;
        }
    };
    bool my_class::should_output_destructor_msg = false;

    bool operator==(const my_class& lhs, const my_class& rhs) {
        return lhs.hoge == rhs.hoge && lhs.fuga == rhs.fuga &&
               lhs.foo == rhs.foo;
    }
    // bool operator!=(const my_class& lhs, const my_class& rhs) {
    //     return NOT(lhs == rhs);
    // }
    bool operator<(const my_class& lhs, const my_class& rhs) {
        return lhs.hoge < rhs.hoge || lhs.fuga < rhs.fuga || lhs.foo < rhs.foo;
    }

    void insert_sequence(ft::map<my_class>& ex, int start, int last) {
        for (int i = start; i <= last; ++i) {
            ex.insert(my_class(i, i, "ex"));
        }
    }

    TEST(Constructor_Destructor_operator_eq, empty_range_copy) {
        ft::map<my_class> empty;
        int               hoge[] = { 21, 12, 13, 42, 53, 1 };
        ft::map<int>      range(&hoge[0], &hoge[sizeof(hoge) - 1]);
        ft::map<int>      copy(range);
        ft::map<my_class> assigner;
        assigner.insert(my_class(1, 1, "a"));
        empty = assigner;
        EXPECT_TRUE(empty == assigner);
    }
    {
        ft::map<my_class> example;
    }

    TEST(Iterators, begin_end_and_r) {
        ft::map<my_class> example;
        insert_sequence(example, 1, 12);
        // to make sure the value is correct
        EXPECT_TRUE(*example.begin() == my_class(1, 1, "ex"));
        EXPECT_TRUE(*example.end() == my_class(12, 12, "ex"));
        EXPECT_TRUE(*example.rend() == my_class(1, 1, "ex"));
        EXPECT_TRUE(*example.rbegin() == my_class(12, 12, "ex"));

        // is it iterable?
        ft::map<my_class>::iterator it = example.begin();
        int                         i  = 1;
        while (it != example.end()) {
            EXPECT_TRUE(*it == my_class(i, i, "ex"));
            ++i;
        }
        ft::map<my_class>::reverse_iterator rit = example.rbegin();
        i                                       = 12;
        while (rit != example.rend()) {
            EXPECT_TRUE(*rit == my_class(i, i, "ex"));
            --i;
        }
    }

    TEST(capacity, empty_size_max_size) {
        ft::map<my_class> example;
        EXPECT_TRUE(example.empty());
        EXPECT_TRUE(example.size() == 0);
        insert_sequence(example, 1, 20);
        EXPECT_TRUE(example.size() == 20);
        // TODO how to make sure the max_size() value is correct
    }

    TEST(element_access, operator) {
        ft::map<my_class> example;
        insert_sequence(example, 0, 20);
        rep(21) { EXPECT_TRUE(example[i] == my_class(i, i, "ex")); }
    }

    TEST(modifiers, insert) {}
    TEST(modifiers, erase) {}
    TEST(modifiers, swap) {}
    TEST(modifiers, clear) {}

    TEST(observers, key_comp) {}
    TEST(observers, value_comp) {}

    TEST(operations, find) {}
    TEST(operations, count) {}
    TEST(operations, lower_bound) {}
    TEST(operations, upper_bound) {}
    TEST(operations, equal_range) {}
    TEST(operations, get_allocator) {}
} // namespace

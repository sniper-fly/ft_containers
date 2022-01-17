#include "gtest/gtest.h"
#include "stack.hpp"
#include "macro.hpp"

namespace
{
    void push_sequel_num(ft::stack<int>& st, int start, int last) {
        for (int i = start; i <= last; ++i) {
            st.push(i);
        }
    }

    TEST(stack, constructor) {
        ft::stack<int> st1;
        push_sequel_num(st1, 10, 12);
        ft::stack<int> st2(st1);
        EXPECT_TRUE(st1 == st2);
    }

    TEST(stack, empty) {
        ft::stack<int> st;
        EXPECT_TRUE(st.empty());
        ft::stack<int> st1;
        st1.push(1);
        EXPECT_TRUE(! st1.empty());
    }

    TEST(stack, size) {
        ft::stack<int> st;
        push_sequel_num(st, 1, 151);
        EXPECT_TRUE(st.size() == 151);
        ft::stack<int> st1;
        EXPECT_TRUE(st1.size() == 0);
    }

    TEST(stack, top) {
        ft::stack<int> st;
        push_sequel_num(st, 1, 10);
        EXPECT_TRUE(st.top() == 10);
        ////////// const
        const ft::stack<int> st1(st);
        EXPECT_TRUE(st.top() == 10);
    }

    TEST(stack, push_pop) {
        ft::stack<int> st;
        push_sequel_num(st, 1, 10);
        for (int i = 10; i >= 1; --i) {
            EXPECT_TRUE(st.top() == i);
            st.pop();
        }
    }

    TEST(stack, relational_operators) {
        //// == <= >=
        ft::stack<int> st1;
        push_sequel_num(st1, 1, 10);
        ft::stack<int> st2;
        push_sequel_num(st2, 1, 10);
        EXPECT_TRUE(st1 == st2);
        EXPECT_TRUE(st1 >= st2);
        EXPECT_TRUE(st1 <= st2);
        //// < <= > >= !=
        ft::stack<int> st3;
        push_sequel_num(st3, 1, 9);
        st3.push(11);
        EXPECT_TRUE(st1 < st3);
        EXPECT_TRUE(st1 <= st3);
        EXPECT_TRUE(st3 > st1);
        EXPECT_TRUE(st3 >= st1);
        EXPECT_TRUE(st3 != st1);
        ft::stack<int> st4;
        push_sequel_num(st4, 1, 11);
        EXPECT_TRUE(st1 < st4);
        EXPECT_TRUE(st1 <= st4);
        EXPECT_TRUE(st4 > st1);
        EXPECT_TRUE(st4 >= st1);
        EXPECT_TRUE(st4 != st1);
    }
} // namespace

#include "gtest/gtest.h"
#include "vector.hpp"
#include <iostream>
#include <string>
#include "macro.hpp"


namespace
{
    class my_class
    {
    public:
        my_class() {}
        my_class(int hoge, double fuga, float piyo, std::string foo)
            : hoge(hoge), fuga(fuga), piyo(piyo), foo(foo) {}
        ~my_class() {
            if (should_output_destructor_msg) {
                std::cout << foo;
            }
        }

        static bool should_output_destructor_msg;

        int         hoge;
        double      fuga;
        float       piyo;
        std::string foo;

        my_class& operator=(const my_class& x) {
            hoge = x.hoge;
            fuga = x.fuga;
            piyo = x.piyo;
            foo  = x.foo;
            return *this;
        }
    };
    bool my_class::should_output_destructor_msg = false;

    bool operator==(const my_class& lhs, const my_class& rhs) {
        return lhs.hoge == rhs.hoge && lhs.fuga == rhs.fuga &&
               lhs.piyo == rhs.piyo && lhs.foo == rhs.foo;
    }
    bool operator!=(const my_class& lhs, const my_class& rhs) {
        return NOT(lhs == rhs);
    }


    ft::vector<int>      hoge;
    ft::vector<int>      fuga(3, 42);
    ft::vector<my_class> piyo(7, my_class(1, 2, 3, "foo"));
    ft::vector<my_class> foo;

    TEST(Constructor, _) {
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(42 == fuga[i]);
        }
    }

    TEST(destructor, _) {
        std::cout << "----- destructor output test ------" << std::endl;
        my_class::should_output_destructor_msg = true;
        testing::internal::CaptureStdout();
        {
            my_class             element(1, 1, 1, "0");
            ft::vector<my_class> dest(4, element);
            element.foo = "1";
            dest[1]     = element;
            element.foo = "2";
            dest[2]     = element;
            element.foo = "3";
            dest[3]     = element;
            element.foo = "";
        }
        EXPECT_STREQ("3210", testing::internal::GetCapturedStdout().c_str());
        my_class::should_output_destructor_msg = false;
        std::cout << "-----------------------------------" << std::endl;
    }

    // TEST(Destructor, ) { }
    // TEST(operator=, ) {  }
    // TEST(iterators, ) {  }

    TEST(capacity, size_capacity_empty) {
        EXPECT_TRUE(fuga.size() == 3);
        EXPECT_TRUE(piyo.size() == 7);
        EXPECT_TRUE(foo.size() == 0);
        EXPECT_TRUE(piyo.capacity() == 7);
        EXPECT_TRUE(foo.empty());
        EXPECT_TRUE(NOT piyo.empty());
    }

    TEST(capacity, reserve) {
        ft::vector<my_class> bar(5, my_class(1, 2, 3, "a"));
        ft::vector<my_class> baz(5, my_class(1, 2, 3, "a"));
        my_class             expect(1, 2, 3, "a");
        bar.reserve(10);
        EXPECT_TRUE(bar.capacity() == 10);
        rep(5) { EXPECT_TRUE(bar[i] == expect); }
        baz.reserve(2);
        EXPECT_TRUE(baz.capacity() == 5);
        rep(5) { EXPECT_TRUE(baz[i] == expect); }
    }

    TEST(element_access, at_front_back) {
        ft::vector<int> hoge(3, 5);
        // EXPECT_DEATH(hoge.at(4), ".*");
        try {
            hoge.at(4);
        } catch (std::exception& e) {
            EXPECT_TRUE(e.what());
        }
        EXPECT_TRUE(hoge[2] == 5);
        EXPECT_TRUE(hoge.at(2) == 5);
        EXPECT_TRUE(hoge.front() == 5);
        EXPECT_TRUE(hoge.back() == 5);
    }

    TEST(modifiers, assign) {
        ft::vector<my_class> modi(3, my_class(1, 2, 3, "a"));
        modi[1] = my_class(4, 5, 6, "b");
        modi[2] = my_class(7, 8, 9, "c");
        modi.assign(2, my_class(100, 101, 102, "z"));
        ft::vector<my_class> expect1(2, my_class(100, 101, 102, "z"));
        EXPECT_TRUE(modi == expect1);

        modi.assign(5, my_class(200, 201, 202, "hoge"));
        ft::vector<my_class> expect2(5, my_class(200, 201, 202, "hoge"));
        EXPECT_TRUE(modi == expect2);
    }

    TEST(modifiers, clear) {
        ft::vector<my_class> cle(3, my_class(1, 2, 3, "a"));
        cle.clear();
        EXPECT_TRUE(cle.empty());
    }

    TEST(modifiers, push_back) {
        ft::vector<my_class> pus;
        pus.push_back(my_class(1, 2, 3, "a"));
        ft::vector<my_class> expect(2, my_class(1, 2, 3, "a"));
        EXPECT_TRUE(pus[0] == expect[0]);
        my_class add_one(10, 11, 12, "ab");
        expect[1] = add_one;
        pus.push_back(add_one);
        EXPECT_TRUE(pus[1] == expect[1]);
    }

    TEST(modifiers, swap) {
        ft::vector<int> a;
        ft::vector<int> b;
        a.push_back(0);
        a.push_back(1);
        a.push_back(2);
        ft::vector<int> a_copy(a);
        b.push_back(3);
        b.push_back(4);
        b.push_back(5);
        ft::vector<int> b_copy(b);
        a.swap(b);
        EXPECT_TRUE(b == a_copy);
        EXPECT_TRUE(b == b_copy);
    }
    // TEST(allocator, ) {  }

    TEST(vector, std_out) {
        testing::internal::CaptureStdout();
        std::cout << "hello" << std::endl;
        EXPECT_STREQ("hello\n", testing::internal::GetCapturedStdout().c_str());
    }
} // namespace

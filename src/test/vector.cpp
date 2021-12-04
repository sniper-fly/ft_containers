#include "gtest/gtest.h"
#include "vector.hpp"
#include <iostream>
#include <string>
#include "macro.hpp"

class my_class
{
public:
    my_class() {}
    my_class(int hoge, double fuga, float piyo, std::string foo)
        : hoge(hoge), fuga(fuga), piyo(piyo), foo(foo) {}

    int    hoge;
    double fuga;
    float  piyo;

    std::string foo;
    bool        operator==(my_class& x) {
        return hoge == x.hoge && fuga == x.fuga && piyo == x.piyo &&
               foo == x.foo;
    }
};

namespace
{
    ft::vector<int>      hoge;
    ft::vector<int>      fuga(3, 42);
    ft::vector<my_class> piyo(7, my_class(1, 2, 3, "foo"));
    ft::vector<my_class> foo;

    TEST(Vector, Constructor) {
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(42 == fuga[i]);
        }
    }

    // TEST(Vector, Destructor) { }
    // TEST(Vector, operator=) {  }
    // TEST(Vector, iterators) {  }
    TEST(Vector, capacity) {
        EXPECT_TRUE(fuga.size() == 3);
        EXPECT_TRUE(piyo.size() == 7);
        EXPECT_TRUE(foo.size() == 0);
        EXPECT_TRUE(piyo.capacity() == 7);
        EXPECT_TRUE(foo.empty());
        EXPECT_TRUE(! piyo.empty());
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

    TEST(Vector, element_access) {
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

    TEST(vector, std_out) {
        testing::internal::CaptureStdout();
        std::cout << "hello" << std::endl;
        EXPECT_STREQ("hello\n", testing::internal::GetCapturedStdout().c_str());
    }
    // TEST(Vector, modifiers) {  }
    // TEST(Vector, allocator) {  }
} // namespace

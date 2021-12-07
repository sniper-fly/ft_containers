#include "gtest/gtest.h"
#include "vector.hpp"
#include <iostream>
#include <string>

class my_class
{
public:
    my_class() {}
    my_class(int hoge, double fuga, float piyo, std::string foo)
        : hoge(hoge), fuga(fuga), piyo(piyo), foo(foo) {}

    int         hoge;
    double      fuga;
    float       piyo;
    std::string foo;
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
    // 10;
    // 20;

    // TEST(Vector, Destructor) { }
    // TEST(Vector, operator=) {  }
    // TEST(Vector, iterators) {  }
    TEST(Vector, capacity) {
        EXPECT_TRUE(fuga.size() == 3);
        EXPECT_TRUE(piyo.size() == 7);
        EXPECT_TRUE(foo.size() == 0);
    }

    TEST(Vector, element_access) {
        ft::vector<int> hoge(3, 5);
        EXPECT_DEATH(hoge.at(4), ".*");
        try {
            hoge.at(4);
        } catch (std::exception& e) {
            EXPECT_TRUE(e.what());
        }
        EXPECT_EQ(hoge[2], 5);
        EXPECT_EQ(hoge.at(2), 5);
        EXPECT_EQ(hoge.front(), 5);
        EXPECT_EQ(hoge.back(), 5);
    }

    // TEST(Vector, modifiers) {  }
    // TEST(Vector, allocator) {  }
} // namespace

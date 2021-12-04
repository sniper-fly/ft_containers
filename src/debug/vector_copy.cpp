#include "gtest/gtest.h"
#include "vector.hpp"
#include <iostream>
#include <string>
#include <cassert>

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

void test_vector() {
    ft::vector<int>      hoge;
    ft::vector<int>      fuga(3, 42);
    ft::vector<my_class> piyo(7, my_class(1, 2, 3, "foo"));
    ft::vector<my_class> foo;

    {
        for (int i = 0; i < 3; ++i) {
            assert(42 == fuga[i]);
        }
    }

    // TEST(Vector, Destructor) { }
    // TEST(Vector, operator=) {  }
    // TEST(Vector, iterators) {  }
    {
        assert(fuga.size() == 3);
        assert(piyo.size() == 7);
        assert(foo.size() == 0);
        assert(piyo.capacity() == 7);
        assert(foo.empty());
        assert(! piyo.empty());
    }
    {
        ft::vector<my_class> bar(5, my_class(1, 2, 3, "a"));
        ft::vector<my_class> baz(5, my_class(1, 2, 3, "a"));
        my_class             expect(1, 2, 3, "a");
        bar.reserve(10);
        assert(bar.capacity() == 10);
        rep(5) { assert(bar[i] == expect); }
        baz.reserve(2);
        assert(baz.capacity() == 5);
        rep(5) { assert(baz[i] == expect); }
    }

    {
        ft::vector<int> hoge(3, 5);
        // EXPECT_DEATH(hoge.at(4), ".*");
        try {
            hoge.at(4);
        } catch (std::exception& e) {
            assert(e.what());
        }
        assert(hoge[2] == 5);
        assert(hoge.at(2) == 5);
        assert(hoge.front() == 5);
        assert(hoge.back() == 5);
    }

    // TEST(Vector, modifiers) {  }
    // TEST(Vector, allocator) {  }
} // namespace

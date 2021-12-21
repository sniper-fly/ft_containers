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

    TEST(Constructor, default_fill_copy) {
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(42 == fuga[i]);
        }
        ft::vector<int> original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);
        original.push_back(4);
        ft::vector<int> copied(original);
        EXPECT_TRUE(original == copied);
        EXPECT_TRUE(original.capacity() == copied.capacity());

        const ft::vector<int> const_copied(original);
        EXPECT_TRUE(original == copied);
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

    TEST(operator_eq, _) {
        ft::vector<my_class> opeq;
        opeq.push_back(my_class(1, 2, 3, "a"));
        opeq.push_back(my_class(4, 5, 6, "b"));
        opeq.push_back(my_class(7, 8, 9, "c"));
        ft::vector<my_class> copied;
        copied = opeq;
        EXPECT_TRUE(opeq == copied);
        EXPECT_TRUE(opeq.capacity() == copied.capacity());
    }
    // TEST(iterators, ) {  }

    TEST(capacity, size_capacity_empty) {
        EXPECT_TRUE(fuga.size() == 3);
        EXPECT_TRUE(piyo.size() == 7);
        EXPECT_TRUE(foo.size() == 0);
        EXPECT_TRUE(piyo.capacity() == 7);
        EXPECT_TRUE(foo.empty());
        EXPECT_TRUE(NOT piyo.empty());
    }

    TEST(capacity, max_size) {
        ft::vector<int>  mine;
        std::vector<int> expect;
        EXPECT_TRUE(mine.max_size() == expect.max_size());
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
        bool has_error = false;
        try {
            baz.reserve(baz.max_size() + 1);
        } catch (std::exception& e) {
            std::cout << "------------------" << std::endl;
            std::cout << e.what() << std::endl;
            std::cout << "------------------" << std::endl;
            has_error = true;
        }
        EXPECT_TRUE(has_error);
    }

    TEST(capacity, resize) {
        ft::vector<my_class> res;
        res.push_back(my_class(1, 2, 3, "a"));
        res.push_back(my_class(4, 5, 6, "b"));
        res.push_back(my_class(7, 8, 9, "c"));
        res.push_back(my_class(10, 11, 12, "d"));
        res.resize(1); // 要素を減らす
        ft::vector<my_class> expect(1, my_class(1, 2, 3, "a"));
        EXPECT_TRUE(res == expect);
        res.resize(3, my_class(100, 101, 102, "aa")); // 要素を3個目まで埋める
        rep(2) { expect.push_back(my_class(100, 101, 102, "aa")); }
        EXPECT_TRUE(res == expect);
        res.resize(
            7, my_class(100, 101, 102, "aa")); // capacityより容量を増やす
        rep(4) { expect.push_back(my_class(100, 101, 102, "aa")); }
        EXPECT_TRUE(res == expect);
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
        EXPECT_TRUE(b == a_copy);
    }

    TEST(modifiers, insert) {
        {
            ft::vector<my_class> ins;
            ins.push_back(my_class(0, 2, 3, "a"));
            ins.push_back(my_class(10, 5, 6, "b"));
            ins.push_back(my_class(20, 8, 9, "c"));
            ins.push_back(my_class(30, 1, 2, "d"));
            ins.push_back(my_class(40, 4, 5, "e"));
            ft::vector<my_class>::iterator it;
            it = ins.insert(ins.begin() + 2, my_class(11, 11, 11, "bb"));
            ft::vector<my_class> expect;
            expect.push_back(my_class(0, 2, 3, "a"));
            expect.push_back(my_class(10, 5, 6, "b"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(20, 8, 9, "c"));
            expect.push_back(my_class(30, 1, 2, "d"));
            expect.push_back(my_class(40, 4, 5, "e"));
            EXPECT_TRUE(ins == expect);
        }
        {
            ft::vector<my_class> ins;
            ins.push_back(my_class(0, 2, 3, "a"));
            ins.push_back(my_class(10, 5, 6, "b"));
            ins.push_back(my_class(20, 8, 9, "c"));
            ins.push_back(my_class(30, 1, 2, "d"));
            ins.push_back(my_class(40, 4, 5, "e"));
            ft::vector<my_class>::iterator it;
            ins.insert(ins.begin() + 2, 5, my_class(11, 11, 11, "bb"));
            ft::vector<my_class> expect;
            expect.push_back(my_class(0, 2, 3, "a"));
            expect.push_back(my_class(10, 5, 6, "b"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(20, 8, 9, "c"));
            expect.push_back(my_class(30, 1, 2, "d"));
            expect.push_back(my_class(40, 4, 5, "e"));
            EXPECT_TRUE(ins == expect);
        }
        {
            ft::vector<my_class> ins;
            ins.push_back(my_class(0, 2, 3, "a"));
            ins.push_back(my_class(10, 5, 6, "b"));
            ins.push_back(my_class(20, 8, 9, "c"));
            ins.push_back(my_class(30, 1, 2, "d"));
            ins.push_back(my_class(40, 4, 5, "e"));
            ft::vector<my_class>::iterator it;
            ins.insert(ins.end() - 1, 5, my_class(11, 11, 11, "bb"));
            ft::vector<my_class> expect;
            expect.push_back(my_class(0, 2, 3, "a"));
            expect.push_back(my_class(10, 5, 6, "b"));
            expect.push_back(my_class(20, 8, 9, "c"));
            expect.push_back(my_class(30, 1, 2, "d"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(11, 11, 11, "bb"));
            expect.push_back(my_class(40, 4, 5, "e"));
            EXPECT_TRUE(ins == expect);
        }
    }

    TEST(modifiers, erase) {
        {
            ft::vector<my_class> era;
            era.push_back(my_class(1, 2, 3, "a"));
            era.push_back(my_class(4, 5, 6, "b"));
            era.push_back(my_class(7, 8, 9, "c"));
            era.push_back(my_class(10, 11, 12, "d"));
            era.push_back(my_class(13, 14, 15, "e"));
            era.erase(era.begin() + 2);
            ft::vector<my_class> expect;
            expect.push_back(my_class(1, 2, 3, "a"));
            expect.push_back(my_class(4, 5, 6, "b"));
            expect.push_back(my_class(10, 11, 12, "d"));
            expect.push_back(my_class(13, 14, 15, "e"));
            EXPECT_TRUE(era == expect);
        }
        {
            ft::vector<my_class> era;
            era.push_back(my_class(1, 2, 3, "a"));
            era.push_back(my_class(4, 5, 6, "b"));
            era.push_back(my_class(7, 8, 9, "c"));
            era.push_back(my_class(10, 11, 12, "d"));
            era.push_back(my_class(13, 14, 15, "e"));
            era.push_back(my_class(16, 17, 18, "f"));
            era.push_back(my_class(19, 20, 21, "g"));
            era.erase(era.begin() + 2, era.begin() + 5);
            ft::vector<my_class> expect;
            expect.push_back(my_class(1, 2, 3, "a"));
            expect.push_back(my_class(4, 5, 6, "b"));
            expect.push_back(my_class(16, 17, 18, "f"));
            expect.push_back(my_class(19, 20, 21, "g"));
            EXPECT_TRUE(era == expect);
        }
    }
    // TEST(allocator, ) {  }

} // namespace

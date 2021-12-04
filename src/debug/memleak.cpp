#include "vector.hpp"
#include <iostream>

namespace debug
{
    void test_memleak() {
        ft::vector<int> hoge(3, 42);
        std::cout << hoge[2] << std::endl;
    }
} // namespace debug

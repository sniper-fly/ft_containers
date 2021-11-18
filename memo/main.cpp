#include "ezoe_vector.hpp"
#include <memory>
#include <string>
#include <iostream>

int main() {
    // std::allocator<int> alloc;
    // ezoe_vector<int>    v(alloc);

    {
        ezoe_vector<int> v(10);
        v[2] = 99;
        std::cout << "a" << std::endl;
        v.resize(5);
    }
}

#include "ezoe_vector.hpp"
#include <memory>
#include <string>
#include <iostream>

int main() {
    {
        std::allocator<std::string> a;
        std::string*                p = a.allocate(1);
        std::string*                s = new (p) std::string("hello");
        std::cout << *s << std::endl;
        s->~basic_string();
        a.deallocate(p, 1);
    }
}

#include <memory>
#include <string>
#include <iostream>

int main() {
    {
        std::allocator<std::string> a;
        using traits   = std::allocator_traits<decltype(a)>;
        std::string* p = traits::allocate(a, 1);
        traits::construct(a, p, "hello");
        std::cout << *p << std::endl;
        traits::destroy(a, p);
        traits::deallocate(a, p, 1);
    }
}

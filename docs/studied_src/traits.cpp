#include <memory>
#include <string>
#include <iostream>

class Hoge
{
private:
    int         _a;
    std::string _b;

public:
    Hoge(int a, std::string b) {
        _a = a;
        _b = b;
    }
    ~Hoge() { std::cout << "destructor called" << std::endl; }
    void put() { std::cout << "a:" << _a << ", b:" << _b << std::endl; }
};

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
    std::cout << "--------------------" << std::endl;
    {
        std::allocator<Hoge> a;
        using traits = std::allocator_traits<decltype(a)>;
        Hoge* p      = traits::allocate(a, 1);
        traits::construct(a, p, 123, "abc");
        p->put();
        traits::destroy(a, p);
        traits::deallocate(a, p, 1);
    }
    std::cout << "--------------------" << std::endl;
    {
        std::allocator<Hoge> a;
        Hoge*                p = a.allocate(3);
        a.construct(p, 456, "def");
        p->put();
        a.destroy(p);
        a.deallocate(p, 1);

        std::allocator<int> b;
        int*                p_ = b.allocate(3);
        printf("%p", &p_[1]);
        std::cout << std::endl;
        printf("%p", &p_[2]);
    }
}

#include <iostream>

template<class T>
class hoge
{
public:
    typedef T value_type;

    hoge(const value_type aa);
};

template<class T>
hoge<T>::hoge(const value_type aa) {
    std::cout << aa << std::endl;
}

int main() { hoge<int> a(12); }

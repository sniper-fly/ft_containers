#include <iostream>
#include <vector>
#include <array>

template <typename T>
auto print(T v) -> decltype(std::begin(v), void())  // (1)
{
    std::cout << "container" << std::endl;
}

template <typename T>
auto print(T []) -> void                            // (2)
{
    std::cout << "array" << std::endl;
}

template <typename T>
auto print(T v) -> decltype(v + 0, void())          // (3)
{
    std::cout << "value" << std::endl;
}

#if 0
// (3)を次のように書くとコンパイルエラー
template <typename T>
auto print(T t) -> void
{
    std::cout << "value" << std::endl;
}
#endif

template<>
auto print<float>(float v) -> void                  // (4)
{
    std::cout << "value(specialized for float)" << std::endl;
}

void print(...)                                     // (5)
{
    std::cout << "other type" << std::endl;
}

int main()
{
    std::vector<float>  a = { 0, 1, 2 };
    double b[3] = { 0, 1, 2 };
    std::array<int, 3> c = { 0, 1, 2 };
    int d = 0;
    struct { int x; int y; } e = { 0, 1 };

    std::cout << "a: ";        print(a);        // (a-1)
    std::cout << "a.data(): "; print(a.data()); // (a-2)
    std::cout << "a.at(0): ";  print(a.at(0));  // (a-3)
    std::cout << "b: ";        print(b);        // (b)
    std::cout << "c: "   ;     print(c);        // (c-1)
    std::cout << "c.data(): "; print(c.data()); // (c-2)
    std::cout << "d: ";        print(d);        // (d)
    std::cout << "e: ";        print(e);        // (e)

    return 0;
}
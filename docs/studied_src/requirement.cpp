#include <iostream>
#include <string>
#include <vector>

class my_class
{
public:
    int         hoge;
    double      fuga;
    float       piyo;
    std::string foo;

    my_class() {}
    my_class(int hoge, double fuga, float piyo, std::string foo)
        : hoge(hoge), fuga(fuga), piyo(piyo), foo(foo) {}
    // ~my_class() { std::cout << foo; }

    // my_class& operator=(const my_class& x) {
    //     hoge = x.hoge;
    //     fuga = x.fuga;
    //     piyo = x.piyo;
    //     foo  = x.foo;
    //     return *this;
    // }
};

int main() {
    std::vector<my_class> mine;
    mine.push_back(my_class(1, 2, 3, "a"));
    mine.push_back(my_class(1, 2, 3, "b"));
    mine.push_back(my_class(1, 2, 3, "c"));
    mine.push_back(my_class(1, 2, 3, "d"));
    std::vector<my_class>::iterator it = mine.begin();
    it++;
    mine.erase(it);
    mine.resize(5);
}

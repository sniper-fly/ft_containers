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
        : hoge(hoge), fuga(fuga), piyo(piyo), foo(foo) {
        std::cout << "constructor" << std::endl;
    }
    ~my_class() {
        std::cout << "destructor"
                  << "|" << foo << std::endl;
    }

private:
    my_class& operator=(const my_class& x);

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
    std::cout << "=======================" << std::endl;
    mine.erase(it);
    std::cout << "=======================" << std::endl;
    // mine.resize(5);
}

// inserting into a vector
#include <iostream>
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

    my_class& operator=(const my_class& x) {
        std::cout << "operator=" << std::endl;
        hoge = x.hoge;
        fuga = x.fuga;
        piyo = x.piyo;
        foo  = x.foo;
        return *this;
    }
};

int main() {
    {
        std::vector<int>           myvector(3, 100);
        std::vector<int>::iterator it;

        it = myvector.begin() + 1;
        it = myvector.insert(it, 200);
        std::cout << it - myvector.begin() << std::endl;

        myvector.insert(it, 2, 300);

        // "it" no longer valid, get a new one:
        // it = myvector.begin();

        // std::vector<int> anothervector(2, 400);
        // myvector.insert(it + 2, anothervector.begin(), anothervector.end());

        // int myarray[] = { 501, 502, 503 };
        // myvector.insert(myvector.begin(), myarray, myarray + 3);

        std::cout << "myvector contains:";
        for (it = myvector.begin(); it < myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    std::cout << "==================" << std::endl;

    {
        std::vector<my_class> origin = {
            my_class(0, 0, 0, "a"), //
            my_class(1, 1, 1, "b"), //
            my_class(2, 2, 2, "c"), //
            my_class(3, 3, 3, "d"), //
            my_class(4, 4, 4, "e"), //
            my_class(5, 5, 5, "f")  //
        };
        typename std::vector<my_class>::iterator it;

        my_class inserter(11, 11, 11, "bb");
        origin.reserve(30);
        std::cout << "====insert======" << std::endl;
        origin.insert(origin.end() - 1, 3, inserter);
        std::cout << "================" << std::endl;
        std::cout << "original contains:";
        for (it = origin.begin(); it < origin.end(); it++)
            std::cout << ' ' << it->hoge;
        std::cout << '\n';
        return 0;
    }
}

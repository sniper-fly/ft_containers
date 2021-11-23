#include "./small_iterator.hpp"
#include <iostream>
#include <algorithm>

//      各行の内容を行番号付きで表示
void printLine(const std::vector<char>& v) {
    int                 lineNum = 0;
    const_line_iterator itr(v.begin(), v.end());
    const_line_iterator iend(v.end(), v.end());
    for (; itr != iend; ++itr)
        std::cout << ++lineNum << ": " << (*itr).c_str() << "\n";
}

//      最大行長を返す
int getMaxSize(const std::vector<char>& v) {
    size_t              maxSize = 0;
    const_line_iterator itr(v.begin(), v.end());
    const_line_iterator iend(v.end(), v.end());
    for (; itr != iend; ++itr)
        maxSize = std::max(maxSize, (*itr).size());
    return maxSize;
}

//      std::find() を用いて指定文字列の行を検索
int main() {
    std::vector<char> v;
    v.push_back('1');
    v.push_back('2');
    v.push_back('3');
    v.push_back('5');
    v.push_back('4');
    v.push_back('5');
    const_line_iterator first(v.begin(), v.end());
    const_line_iterator last(v.end(), v.end());
    const_line_iterator itr = std::find(first, last, std::string("12345"));
    std::cout << *first << std::endl;
    std::cout << *last << std::endl;
    std::cout << *itr << std::endl;
}

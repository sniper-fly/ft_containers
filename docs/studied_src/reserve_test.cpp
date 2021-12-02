#include <vector>

int main() {
    std::vector<int> hoge(5, 41);
    hoge.reserve(hoge.max_size() + 5);
}

#include <iostream>
#include <memory>

#include <vector>
#include <algorithm>

int main() {
    const std::vector<int> v = { 1, 2, 3 };

    std::allocator<int> alloc;

    // メモリ確保。
    // この段階では、[p, p + size)の領域は未初期化
    const std::size_t size = 3;
    int*              p    = alloc.allocate(size);

    // 未初期化領域pを初期化しつつ範囲vから要素をコピー
    std::uninitialized_copy(v.begin(), v.end(), p);

    // pの領域が初期化され、かつvからpに要素がコピーされているか確認
    std::for_each(p, p + size, [](int x) { std::cout << x << std::endl; });

    // 要素を破棄
    for (std::size_t i = 0; i < size; ++i) {
        alloc.destroy(p + i);
    }

    // メモリ解放
    alloc.deallocate(p, size);
}

#include <iostream>

auto hoge(int a) -> int { return a * 2; }

int main() { std::cout << hoge(10) << std::endl; }

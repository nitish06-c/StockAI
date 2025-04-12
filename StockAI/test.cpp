//
//  test.cpp
//  StockAI
//
#include <cassert>
#include <string>
#include <iostream>

std::string test1() {
    return "StockAI ready!";
}

int main() {
    assert(test1() == "StockAI ready!");
    std::cout << "✅ Tests passed!" << std::endl;
    return 0;
}

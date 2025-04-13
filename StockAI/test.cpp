//
//  test.cpp
//  StockAI
//
#include "StockAI/utils.hpp"
#include <cassert>
#include <string>
#include <iostream>

std::string test1() {
    return "StockAI ready!";
}

void testJsonFormat() {
    std::string mockJson = R"({"c": 138.012, "pc": 130.20})";
    std::string summary = formatDataFromJson(mockJson, "AAPL");

    assert(summary.find("AAPL") != std::string::npos);
    assert(summary.find("up") != std::string::npos);
    assert(summary.find("1.06") != std::string::npos);

    std::cout << "✅ formatDataFromJson test passed!" << std::endl;
}

int main() {
    assert(test1() == "StockAI ready!");
    std::cout << "✅ Tests passed!" << std::endl;
    testJsonFormat();
    return 0;
    
}

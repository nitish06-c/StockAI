//
//  main.cpp
//  StockAI
//
//  Created by Nitish Madabusi on 2025-04-11.
//

#include <iostream>
#include <string>

std::string getEnvChar(const std:: string &key) {
    const char* val = std::getenv(key.c_str());
    return val == nullptr ? "" : std::string(val);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

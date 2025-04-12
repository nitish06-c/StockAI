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
    return val == nullptr ? "" : std::string(val); //return empty string if key isn't found
}

std::string getData(const std::string& ticker, const std::string& stockApiKey) {
    //TODO
    return "";
}

std::string gptCall(const std::string &analysis, const std::string openaiKey) {
    //TODO
    return "";
}


int main(int argc, const char * argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./StockAI <TICKER>\n";
        return 1;
    }
    
    std::string ticker = argv[1];
    std::string stockApiKey = getEnvChar("STOCK_API_KEY");
    std::string openApiKey = getEnvChar("OPENAI_API_KEY");
    
    if (stockApiKey.empty() || openApiKey.empty()) {
        std::cerr << "Error: No STOCK_API_KEY or OPENAI_API_KEY in environment";
        return 1;
    }
    
    std:: string stockData = getData(ticker, stockApiKey);
    std:: string gptData = gptCall(ticker, openApiKey);
    
    std:: cout << "\nStock Summary: " << stockData << "\n";
    std:: cout << gptData << "\n";
    
    return 0;
    
}

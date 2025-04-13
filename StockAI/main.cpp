//  main.cpp
//  StockAI

#include "utils.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <iomanip>


#include "json.hpp"
using json = nlohmann::json;

int main() {
    std::string stockApiKey = getEnvChar("STOCK_API_KEY");
    std::string openApiKey = getEnvChar("OPENAI_API_KEY");
    
    if (stockApiKey.empty() || openApiKey.empty()) {
        std::cerr << "Error: No STOCK_API_KEY or OPENAI_API_KEY in environment\n";
        return 1;
    }
    
    std::cout << "Welcome to StockAI! Get information on stocks here\n";
    std::cout << "Type 'exit' anytime to quit or 'back' to choose a different stock\n";

    while (true) {
        std::string ticker;
        std::cout << "Input stock symbol: ";
        std::getline(std::cin, ticker);
        
        if (ticker == "exit") {
            std::cout << "Exiting\n";
            break;
        }
        std::string stockdata = getData(ticker, stockApiKey);
        std::string data = formatDataFromJson(stockdata, ticker);
        
        while (true) {
            std::string q;
            std::cout << "Ask GPT about the stock " << ticker << " or type 'back' to pick a different stock: ";
            std::getline(std::cin, q);
            
            if (q == "back") {
                break;
            }
            if (q == "exit") {
                std::cout << "Exiting\n";
                exit(0);
            }
            std::string gptprompt = data + "\n" + q;
            std::string gptres = gptCall(gptprompt, openApiKey);

            std::cout << "\nStock Summary: " << data << "\n\n";
            std::cout << "ChatGPT analysis: " << gptres << "\n";
            
        }
        
    }
    return 0;
}

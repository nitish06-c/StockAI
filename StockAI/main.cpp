//  main.cpp
//  StockAI


#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <iomanip>


#include "json.hpp"
using json = nlohmann::json;

std::string getEnvChar(const std:: string &key) {
    const char* val = std::getenv(key.c_str());
    return val == nullptr ? "" : std::string(val); //return empty string if key isn't found
}

std::string getData(const std::string& ticker, const std::string& stockApiKey) {
    std::string url = "https://finnhub.io/api/v1/quote?symbol=" + ticker + "&token=" + stockApiKey;
    std::string command = "curl -s \"" + url + "\"";
    
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "Could not get any stock data";
    }
    char buffer[128];
    std::stringstream res;
    
    while (fgets(buffer, sizeof buffer, pipe) != nullptr) {
        res << buffer;
    }
    
    pclose(pipe);
    return res.str();
}

std::string formatDataFromJson(const std::string& rawJson, const std::string& ticker) {
    try {
        json data = json::parse(rawJson);

        double cur = data["c"];
        double prevClose = data["pc"];

        double change = cur - prevClose;
        double percent = (change / prevClose) * 100.0;

        std::ostringstream oss;
        oss << ticker << " is valued at $" << cur << ", "
            << (change >= 0 ? "up" : "down") << " "
            << std::fixed << std::setprecision(2)
            << std::abs(percent) << "% from the previous close.";

        return oss.str();
    } catch (const std::exception& e) {
        return std::string("Error parsing data: ") + e.what();
    }
}

std::string gptCall(const std::string &analysis, const std::string& openaiKey) {
    std::string text = "Explain the trends: " + analysis;
    
    json payload;
        payload["model"] = "gpt-3.5-turbo";
        payload["messages"] = {
            { {"role", "user"}, {"content", text} }
        };
        payload["temperature"] = 0.7;
    
    std::string payloadString = payload.dump();

    std::string command = "curl -s https://api.openai.com/v1/chat/completions "
    "-H \"Authorization: Bearer " + openaiKey + "\" "
    "-H \"Content-Type: application/json\" "
    "-d '" + payloadString + "'";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "Could not get any stock data";
    }
    char buffer[512];
    std::stringstream res;
    
    while (fgets(buffer, sizeof buffer, pipe) != nullptr) {
        res << buffer;
    }
    
    pclose(pipe);
    
    try {
        json parse = json::parse(res.str());
        if (!parse.contains("choices") || parse["choices"].empty() ||
            !parse["choices"][0].contains("message") ||
            !parse["choices"][0]["message"].contains("content") ||
            parse["choices"][0]["message"]["content"].is_null()) {
            return "GPT response malformed or missing content.";
        }
        return parse["choices"][0]["message"]["content"];
        
    } catch (const std::exception& e){
        return std::string("Error parsing json") + e.what();
    }
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
        std::cerr << "Error: No STOCK_API_KEY or OPENAI_API_KEY in environment\n";
        return 1;
    }
    
    std::string stockdata = getData(ticker, stockApiKey);
    std::string data = formatDataFromJson(stockdata, ticker);
    std::string gptres = gptCall(data, openApiKey);

    std::cout << "\nStock Summary: " << data << "\n\n";
    std::cout << "ChatGPT analysis:\n" << gptres << "\n";

    return 0;
    
}

#pragma once
#include <string>

std::string getEnvChar(const std::string &key);
std::string getData(const std::string& ticker, const std::string& stockApiKey);
std::string formatDataFromJson(const std::string& rawJson, const std::string& ticker);
std::string gptCall(const std::string &analysis, const std::string& openaiKey);

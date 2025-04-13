// StockAI/utils.hpp
#pragma once

#include <string>

std::string getEnvChar(const std::string& key);
std::string formatDataFromJson(const std::string& rawJson, const std::string& ticker);

#StockAI

StockAI is a command-line C++ app that fetches real-time stock data and uses OpenAI to provide human-friendly analysis of stock trends. It’s Dockerized, CI-tested, and fully modular.

---

## Features

- Get current price, percentage change, and other stock metrics via the [Finnhub API](https://finnhub.io/)
- Ask ChatGPT (via OpenAI API) questions about the stock's performance
- Dockerized for easy use across environments
- CI/CD with GitHub Actions and unit tests for reliability

---

## 🚀 Getting Started

### Prerequisites

- C++ compiler (e.g. `g++`)
- A [Finnhub API key](https://finnhub.io/)
- An [OpenAI API key](https://platform.openai.com/account/api-keys)

### Local Build & Run

```bash
# Compile
g++ -std=c++17 -IStockAI -IStockAI/include StockAI/main.cpp StockAI/utils.cpp -o stockai.out

# Set API keys
export STOCK_API_KEY=your_finnhub_key
export OPENAI_API_KEY=your_openai_key

# Run the app
./stockai.out

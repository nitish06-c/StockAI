FROM gcc:13

WORKDIR /app

COPY StockAI/ ./StockAI

RUN apt-get update && apt-get install -y curl

RUN g++ -std=c++17 -I./StockAI/include -o stockai.out ./StockAI/main.cpp

CMD ["./stockai.out"]
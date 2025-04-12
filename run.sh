echo " Building Docker image..."
docker build -t stockai .

echo "Running StockAI with .env environment variables..."
docker run --env-file .env -it stockai

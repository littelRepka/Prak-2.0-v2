FROM drogonframework/drogon:latest AS builder

WORKDIR /app


COPY . .

# Собираем 
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make


FROM ubuntu:22.04


WORKDIR /app

RUN apt-get update && \
    apt-get -y install libc-ares-dev libjsoncpp-dev libpq-dev libmariadb3 sqlite3 libhiredis0.14 libgtest-dev
    
COPY --from=builder /app/build/calculator /app/calculator
COPY --from=builder /app/config.json /app/config.json
COPY --from=builder /app/build/main_test  /app/main_test


EXPOSE 8080


CMD ["./calculator"]
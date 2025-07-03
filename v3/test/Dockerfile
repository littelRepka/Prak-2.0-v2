# Stage 1: Build Drogon и приложение
FROM alpine:3.20 AS builder

# Установка зависимостей для сборки
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    openssl-dev \
    libuuid \
    zlib-dev \
    boost-dev \
    clang \
    linux-headers \
    libexecinfo-dev

# Клонируем Drogon
WORKDIR /drogon
RUN git clone --depth=1 https://github.com/drogon-framework/drogon.git  . && \
    git submodule update --init

# Сборка Drogon
WORKDIR /drogon/build
RUN cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DDROGON_BUILD_TESTS=OFF \
    -DDROGON_WITH_POSTGRESQL=OFF \
    -DDROGON_WITH_MYSQL=OFF \
    -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make -j$(nproc) && \
    make install

# Копируем пользовательский код
WORKDIR /app
COPY app.cpp .

# Компилируем приложение
RUN g++ app.cpp -o myapp \
    -I/usr/local/include \
    -L/usr/local/lib \
    -ldrogon -ltrantor \
    -lpthread -lssl -lcrypto -luuid -lz -ldl

# Stage 2: Минимальный runtime контейнер
FROM alpine:3.20

# Установка необходимых библиотек для запуска
RUN apk add --no-cache \
    libstdc++ \
    openssl \
    libuuid \
    zlib

# Копируем скомпилированное приложение из builder stage
COPY --from=builder /app/myapp /usr/local/bin/myapp

# Открываем порт
EXPOSE 8080

# Запуск приложения
CMD ["myapp"]
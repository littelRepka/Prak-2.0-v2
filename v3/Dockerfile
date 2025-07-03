
FROM alpine:3.20 as builder


RUN apk add --no-cache \
    c-ares\
    openssl \
    zlib \
    #gcompat \
   # jsoncpp \
    libuuid \
    #flatpak \
    libpq \
    mariadb-connector-c \
    sqlite-libs  \
    build-base \
    cmake \
    git \
    openssl-dev \
    zlib-dev \
    linux-headers \
    boost-dev \
    gcc \
    llvm \
    jsoncpp \
   # e2fsprogs-dev \
    && mkdir /workspace

WORKDIR /workspace

RUN git clone https://github.com/an-tao/drogon  && \
    cd drogon && \
    git submodule update --init


WORKDIR /workspace/drogon
RUN mkdir -p build && \
    cd build && \
    cmake          -DCMAKE_PREFIX_PATH=/usr/lib \
         .. && \
    make && \
    make install

WORKDIR /workspace
COPY . .

# Собираем 
WORKDIR /workspace
RUN ls &&\
ls /usr/local/lib/cmake/jsoncpp/ &&\
mkdir -p build && \
    cd build && \
    cmake     .. &&\
    make

# 
FROM alpine:3.20

#  зависимости
RUN apk update && \
    apk add --no-cache \
        c-ares\
        openssl \
        zlib \
        #gcompat \
        jsoncpp \
        libuuid \
        #flatpak \
        libpq \
        mariadb-connector-c \
        sqlite-libs  


COPY --from=builder /workspace/build/calculator /usr/local/bin/
COPY --from=builder /workspace/build/config.json /usr/local/bin/
COPY --from=builder /workspace/build/libhiredis.so.0.14 /usr/lib/libhiredis.so.0.14

EXPOSE 8080

# Запуск приложения
CMD ["calculator"]
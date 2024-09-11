FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y g++ cmake mariadb-client openssl libssl-dev nlohmann-json3-dev libmariadb3 libmariadb-dev

COPY . .

RUN cd include/mariadb && mkdir build && cd build && cmake .. -DINSTALL_INCLUDEDIR=/usr/include/mariadb -DINSTALL_LIBDIR=/usr/lib && make . && make install .

RUN cd BackEnd/src/API/Server && openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -sha256 -days 365 -nodes -subj "/C=BR/ST=./L=./O=Dafoe/OU=./CN=Dafoe"

RUN cd include/jwt-cpp && cmake . && cmake --build . && cmake --install .

RUN mkdir build && cd build && cmake .. && make

EXPOSE 12354

RUN sleep 20

CMD ["./build/teste.out"]

#include "JWToken.hpp"

int main() {
   // Cria um objeto da classe com a chave secreta

   std::string issuer = "Dafoe";
   std::string key = "Dafoe111";
   JWToken jwt = JWToken(key,issuer);
   std::string token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhZG1pbiI6dHJ1ZSwiZXhwIjoxNzI1NzQ0ODk4LCJpYXQiOjE3MjU3NDQ1OTgsImlzcyI6IkRhZm9lIiwic3ViIjoiMTIzNDUifQ.6lnCtjwyQNCxYBaekqXv6Nw3b4kt_-KZpnZbb88aB3g";

//   std::chrono::seconds expiresIn = std::chrono::seconds(300);

//   std::string token = jwt.createToken(12345, "admin", expiresIn);

//   std::cout << "Token JWT gerado: " << token << std::endl;

   if(jwt.validateToken(token))
        std::cout << "Token válido\n";
    else 
        std::cout << "Token inválido\n";
   return 0;
}

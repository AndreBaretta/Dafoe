#include "JWToken.hpp"
#include "Session.hpp"

int main() {
   // Cria um objeto da classe com a chave secreta

   std::string issuer = "Dafoe";
   std::string key = "Dafoe111";
   std::chrono::seconds expiresIn = std::chrono::seconds(300);
   JWToken jwt = JWToken(key,issuer, expiresIn);
   std::string token1;
   std::string token2;
   // std::string token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhZG1pbiI6dHJ1ZSwiZXhwIjoxNzI1NzQ0ODk4LCJpYXQiOjE3MjU3NDQ1OTgsImlzcyI6IkRhZm9lIiwic3ViIjoiMTIzNDUifQ.6lnCtjwyQNCxYBaekqXv6Nw3b4kt_-KZpnZbb88aB3g";

   token1 = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhZG1pbiI6dHJ1ZSwiZXhwIjoxNzI1ODIwODYzLCJpYXQiOjE3MjU4MjA1NjMsImlzcyI6IkRhZm9lIiwic3ViIjoiMTIzNDUifQ.cXcHoyerhgwgIowOMRYFSKmDP4c7sHSqES24Vmesj6Q";

   token2 = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhZG1pbiI6ZmFsc2UsImV4cCI6MTcyNTgyMDg2MywiaWF0IjoxNzI1ODIwNTYzLCJpc3MiOiJEYWZvZSIsInN1YiI6IjEyMzQ0In0.0n4JmDWZRPZAq_h0_Dg3hyMiFT9espGmVfovP5JTiCs";

   /*
   token1 = jwt.createToken(12345, true);

   std::cout << "Token JWT gerado: " << token1 << '\n';

   token2 = jwt.createToken(12344, false);

   std::cout << "Token JWT gerado: " << token2 << '\n';
   */

   if(jwt.validateToken(token1)){
      Session session1 = jwt.getSession(token1);
      std::cout << "Token1 válido:\n";
      std::cout << "id: " << session1.getId() << "\nAdmin: " << session1.getAdmin() << '\n';

   } else{
      std::cout << "Token1 inválido\n";
   }

   if(jwt.validateToken(token2)){
      Session session2 = jwt.getSession(token2);
      std::cout << "Token2 válido:\n";
      std::cout << "id: " << session2.getId() << "\nAdmin: " << session2.getAdmin() << '\n';
      
   } else{
      std::cout << "Token2 inválido\n";
   }

   return 0;
}

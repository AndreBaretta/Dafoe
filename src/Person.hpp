#ifndef PERSON_2210
#define PERSON_2210

#include "Client.hpp"
#include <string>

class Pessoa : public Cliente{
   public:
      Pessoa(){}
      ~Pessoa(){}
      
      // Setters
      bool setCpf(std::string);

      // Getters
      std::string getCpf();

   private:
      std::string cpf{};
};

#endif

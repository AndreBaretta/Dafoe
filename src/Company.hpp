#ifndef COMPANY_2210
#define COMPANY_2210

#include "Client.hpp"
#include <string>

class Empresa : public Cliente{
   public:
      Empresa(){}
      ~Empresa(){}

      // Setters
      bool setCnpj(std::string);

      // Getters
      std::string getCnpj();

   private:
      std::string cnpj{};
};

#endif

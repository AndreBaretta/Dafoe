#ifndef COMPANY_2210
#define COMPANY_2210

#include "../Client/Client.hpp"
#include <string>
#include <string_view>

class Company: public Client{
   public:
      Company(){}
      ~Company(){}

      // Setters
      bool setCnpj(std::string);

      // Getters
      std::string_view getCnpj();

   private:
      std::string cnpj{};
};

#endif

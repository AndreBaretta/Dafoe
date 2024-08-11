#ifndef COMPANY_2210
#define COMPANY_2210

#include "../Client/Client.hpp"
#include <array>
#include <string>

class Company: public Client{
   public:
      explicit Company(std::string name, std::array<char, 14> cnpj);
      ~Company();

      // Setters

      // Getters
      std::array<char, 14>& getCnpj();

   private:
      std::array<char, 14> m_cnpj{};
};

#endif

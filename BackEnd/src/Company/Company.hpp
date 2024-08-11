#ifndef COMPANY_2210
#define COMPANY_2210

#include "../Client/Client.hpp"
#include <array>
#include <string>

class Company: public Client{
   public:
      explicit Company(int id, std::string name, std::string address, std::array<char, 14> cpnj);
      ~Company();

      // Setters

      // Getters
      std::array<char, 14>& getCnpj();

   private:
      std::array<char, 14> m_cnpj{};
};

#endif

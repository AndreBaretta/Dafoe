#ifndef PERSON_2210
#define PERSON_2210

#include "../Client/Client.hpp"
#include <array>

class Person : public Client{
   public:
      explicit Person(int id, std::string name, std::string address, std::array<char, 11> cpf);
      ~Person();
      
      // Setters

      // Getters
      std::array<char, 11>& getCpf();

   private:
      std::array<char, 11> m_cpf{};
};

#endif

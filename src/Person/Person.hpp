#ifndef PERSON_2210
#define PERSON_2210

#include "../Client/Client.hpp"
#include <string>
#include <string_view>

class Person : public Client{
   public:
      Person(){}
      ~Person(){}
      
      // Setters
      bool setCpf(std::string);

      // Getters
      std::string_view getCpf();

   private:
      std::string cpf{};
};

#endif

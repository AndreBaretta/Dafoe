#ifndef CLIENT_2208
#define CLIENT_2208

#include <string>
class Cliente{
   public:
      Cliente();
      ~Cliente();

      // Setters
      bool setId(int);
      bool setName(std::string);
      bool setAddress(std::string);
      bool setBill(double);
      
      // Getters
      int getId();
      std::string getName();
      std::string getAddress();
      double getBill();

   private:
      int id{};
      std::string name{};
      std::string address{};
      double bill{};
};

#endif

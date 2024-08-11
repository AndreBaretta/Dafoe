#ifndef CLIENT_2208
#define CLIENT_2208

#include <string>
#include <string_view>
class Client{
   public:
      Client();
      ~Client();

      // Setters
      bool setId(int);
      bool setName(std::string);
      bool setAddress(std::string);
      bool setBill(double);
      
      // Getters
      int getId();
      std::string_view getName();
      std::string_view getAddress();
      double getBill();

   private:
      int id{};
      std::string name{};
      std::string address{};
      double bill{};
};

#endif

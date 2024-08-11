#ifndef CLIENT_2208
#define CLIENT_2208
#include <string>
#include <string_view>
class Client{
   public:
      explicit Client(int, std::string, std::string);
      ~Client();

      // Setters
      bool setName(std::string);
      bool setAddress(std::string);
      bool setBill(double);
      
      // Getters
      int getId();
      std::string_view getName();
      std::string_view getAddress();
      double getBill();

   private:
      int m_id{};
      std::string m_name{};
      std::string m_address{};
      double m_bill{};
};

#endif

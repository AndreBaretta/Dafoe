#ifndef CLIENT_2208
#define CLIENT_2208
#include <array>
#include <string>
#include <string_view>
class Client{
   public:
      Client(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);      
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
      std::string m_phoneNumber{};
};

#endif

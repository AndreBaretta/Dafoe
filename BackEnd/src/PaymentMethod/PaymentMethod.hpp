#ifndef PAYMENTMETHOD_0232
#define PAYMENTMETHOD_0232
#include <string>

class PaymentMethod{
public:
   PaymentMethod(const int id, const std::string& name);

   // Setters
   bool setId(const int id);
   bool setName(const std::string& name);

   // Getters
   int getId();
   std::string getName();

private:
   int m_id{};
   std::string m_name;
};  

#endif

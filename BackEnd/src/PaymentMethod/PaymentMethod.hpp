#ifndef PAYMENTMETHOD_0232
#define PAYMENTMETHOD_0232
#include <string>

class PaymentMethod{
public:
   PaymentMethod(int id, const std::string& name);

private:
   int m_id{};
   std::string m_name{};
};  

#endif

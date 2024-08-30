#ifndef PAYMENTMETHODDAO_0236
#define PAYMENTMETHODDAO_0236
#include "PaymentMethod.hpp"
#include <vector>
#include "../DafoeGod/DafoeGod.hpp"

class PaymentMethodDAO{
public:
   PaymentMethodDAO(DafoeGod& dafoe);
   bool createPaymentMethod(const std::string& name);
   bool deletePaymentMethod(const int id);
   bool updatePaymentMethod(const int id, const std::string& name);
   std::vector<PaymentMethod> listPayment();
   PaymentMethod retrievePaymentMethod(const int id);

private:
   DafoeGod& m_theos;
};

#endif

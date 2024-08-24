#ifndef PAYMENTMETHODDAO_0236
#define PAYMENTMETHODDAO_0236
#include "PaymentMethod.hpp"
#include <vector>
#include "../DafoeGod/DafoeGod.hpp"

class PaymentMethodDAO{
public:

   PaymentMethodDAO(DafoeGod& dafoe);
   bool createPaymentMethodDAO(const std::string& name);
   bool deletePaymentMethodDAO(const int id);
   bool updatePaymentMethodDAO(const int id, const std::string& name);
   std::vector<PaymentMethod> listPayment();
private:
   DafoeGod& m_theos;
   static inline int s_id{0};

};

#endif

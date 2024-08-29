#ifndef PAYMENTMETHODMNG_2235
#define PAYMENTMETHODMNG_2235
#include "PaymentMethodDAO.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include <string>

class PaymentMethodMNG{
   public:
      PaymentMethodMNG(PaymentMethodDAO& paymentMethodDAO, JsonBuilder& jsonBuilder);
      bool createPaymentMethod(const std::string& name);
      bool updatePaymentMethod(const int id, const std::string& name);
      bool deletePaymentMethod(const int id);
      std::string retrieveAllPaymentMethod();
      std::string retrievePaymentMethod(int id);

   private:
      PaymentMethodDAO& m_paymentMethodDAO;
      JsonBuilder& m_jsonBuilder;
};

#endif


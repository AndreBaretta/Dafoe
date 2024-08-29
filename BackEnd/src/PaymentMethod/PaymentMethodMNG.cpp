#include "PaymentMethodMNG.hpp"

PaymentMethodMNG::PaymentMethodMNG(PaymentMethodDAO& paymentMethodDAO, JsonBuilder& jsonBuilder)
: m_paymentMethodDAO{paymentMethodDAO}
, m_jsonBuilder{jsonBuilder}
{}

bool PaymentMethodMNG::createPaymentMethod(const std::string& name){
   bool response = this->m_paymentMethodDAO.createPaymentMethod(name);
   return response;
}

bool PaymentMethodMNG::updatePaymentMethod(const int id, const std::string& name){
   bool response = this->m_paymentMethodDAO.updatePaymentMethod(id, name);
   return response;
}

bool PaymentMethodMNG::deletePaymentMethod(const int id){
   bool response = this->m_paymentMethodDAO.deletePaymentMethod(id);
   return response;
}

std::string PaymentMethodMNG::retrievePaymentMethod(const int id){
   json response = this->m_paymentMethodDAO.retrievePaymentMethod(id).dump();
   return response;
}

std::string 



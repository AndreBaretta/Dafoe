#include "PaymentMethod.hpp"

PaymentMethod::PaymentMethod(int id, const std::string& name)
: m_id(id)
, m_name(name) 
{}

// Setters
bool PaymentMethod::setId(int id) {
   m_id = id;
   return true;
}

bool PaymentMethod::setName(const std::string& name) {
   m_name = name;
   return true;
}

// Getters
int PaymentMethod::getId() const {
   return m_id;
}

const std::string& PaymentMethod::getName() const {
   return m_name;
}


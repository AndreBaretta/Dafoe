#include "PaymentMethod.hpp"

PaymentMethod::PaymentMethod(const int id, const std::string& name)
: m_id{id}
, m_name{name}
{}

bool PaymentMethod::setId(const int id){
   this->m_id = id;
   return true;
}

bool PaymentMethod::setName(const std::string& name){
   this->m_name = name;
   return true;
}

int PaymentMethod::getId(){ return this->m_id; }
std::string PaymentMethod::getName(){ return this->m_name; }


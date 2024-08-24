#include "PaymentMethod.hpp"

PaymentMethod::PaymentMethod(int id, const std::string& name)
: m_name{name}
, m_id{id}
{}

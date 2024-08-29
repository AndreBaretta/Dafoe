#include "Employee.hpp"

Employee::Employee(const int id, const std::string& name, const std::string& cargo)
: m_id{id}
, m_name{name}
, m_cargo{cargo}
{}

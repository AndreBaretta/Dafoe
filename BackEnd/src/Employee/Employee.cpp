#include "Employee.hpp"

Employee::Employee(int id, const std::string& name, const std::string& cargo)
: m_id(id)
, m_name(name)
, m_cargo(cargo) 
{}

// Setters
bool Employee::setId(const int id) {
   m_id = id;
   return true;
}

bool Employee::setName(const std::string& name) {
   m_name = name;
   return true;
}

bool Employee::setCargo(const std::string& cargo) {
   m_cargo = cargo;
   return true;
}

// Getters
int Employee::getId() const {
   return m_id;
}

std::string_view Employee::getName() const {
   return m_name;
}

std::string_view Employee::getCargo() const {
   return m_cargo;
}


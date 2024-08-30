#include "Manufacturer.hpp"

Manufacturer::Manufacturer(int id, const std::string& name)
: m_id(id)
, m_name(name) 
{}

// Setters
bool Manufacturer::setId(int id) {
   m_id = id;
   return true;
}

bool Manufacturer::setName(const std::string& name) {
   m_name = name;
   return true;
}

// Getters
int Manufacturer::getId() const {
   return m_id;
}

const std::string& Manufacturer::getName() const {
   return m_name;
}


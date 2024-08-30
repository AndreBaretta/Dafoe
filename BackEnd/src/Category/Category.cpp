#include "Category.hpp"

Category::Category(int id, const std::string& name)
: m_id(id)
, m_name(name) 
{}

// Setters
bool Category::setId(int id) {
   m_id = id;
   return true;
}

bool Category::setName(const std::string& name) {
   m_name = name;
   return true;
}

// Getters
int Category::getId() const {
   return m_id;
}

std::string Category::getName() const {
   return m_name;
}


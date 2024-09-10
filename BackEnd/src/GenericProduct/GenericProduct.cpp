#include "GenericProduct.hpp"

GenericProduct::GenericProduct(int id, const std::string& name, int category)
: m_id(id)
, m_name(name)
, m_category(category)
{}

bool GenericProduct::setName(const std::string& name) {
   m_name = name;
   return true;
}


bool GenericProduct::setCategory(int category) {
   m_category = category;
   return true;
}

// Getters
int GenericProduct::getId() const {
   return m_id;
}

std::string GenericProduct::getName() const {
   return m_name;
}


int GenericProduct::getCategory() const {
   return m_category;
}


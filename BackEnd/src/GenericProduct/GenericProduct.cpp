#include "GenericProduct.hpp"

GenericProduct::GenericProduct(int id, const std::string& name, int quantity, int category, const std::string& reference)
: m_id(id)
, m_name(name)
, m_quantity(quantity)
, m_category(category)
, m_reference(reference) 
{}

bool GenericProduct::setName(const std::string& name) {
   m_name = name;
   return true;
}

bool GenericProduct::setQuantity(int quantity) {
   m_quantity = quantity;
   return true;
}

bool GenericProduct::setCategory(int category) {
   m_category = category;
   return true;
}

bool GenericProduct::setReference(const std::string& reference) {
   m_reference = reference;
   return true;
}

// Getters
int GenericProduct::getId() const {
   return m_id;
}

std::string_view GenericProduct::getName() const {
   return m_name;
}

int GenericProduct::getQuantity() const {
   return m_quantity;
}

int GenericProduct::getCategory() const {
   return m_category;
}

std::string_view GenericProduct::getReference() const {
   return m_reference;
}


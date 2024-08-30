#include "GenericProduct.hpp"
#include <new>
#include <string_view>

GenericProduct::GenericProduct(const int id, const std::string& name, const int quantity, const int category, const std::string& reference)
: m_id{id}
, m_name{name}
, m_quantity{quantity}
, m_category{category}
, m_reference{reference}
{}

bool GenericProduct::setName(const std::string& name){
   m_name = name;
   return true;
}

bool GenericProduct::setQuantity(const int quantity){
   m_quantity = quantity;
   return true;
}

bool GenericProduct::setCategory(const int category){
   m_category = category;
   return true;
}

bool GenericProduct::setReference(const std::string& reference){
   m_reference = reference;
   return true;
}


int GenericProduct::getId(){
   return m_id;
}

std::string_view GenericProduct::getName(){
   return m_name;
}

int GenericProduct::getQuantity(){
   return m_quantity;
}

int GenericProduct::getCategory(){
   return m_category;
}

std::string_view GenericProduct::getReference(){
   return m_reference;
}

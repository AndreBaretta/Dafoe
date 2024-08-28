#include "Category.hpp"

Category::Category(int id, std::string name)
: m_name(name)
, m_id(id)
{}

int Category::getId(){return this->m_id;}
std::string Category::getName(){return this->m_name;}

bool Category::setId(const int id){
   this->m_id = id;
   return true;
}

bool Category::setName(const std::string& name){
   this->m_name = name;
   return true;
}


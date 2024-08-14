#include <array>
#include <string>
#include <string_view>
#include "Product.hpp"

Product::Product(int id, std::string name)
: m_id{id}
, m_name{name}
{}

Product::Product(int id, std::string name, int quantity)
: m_id{id}
, m_name{name}
, m_quantity{quantity}
{}


Product::Product(int id, std::string name, int quantity, std::array<char, 13> barCode)
: m_id{id}
, m_name{name}
, m_quantity{quantity}
{}

bool Product::setId(int id){
    this->m_id = id;
    return true;
}

bool Product::setName(std::string name){
    this->m_name = name;
    return true;
}


int Product::getId(){return this->m_id;}
std::string_view Product::getName(){return this->m_name;}
int Product::getQuantity(){return this->m_quantity;}

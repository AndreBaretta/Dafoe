#include <array>
#include <string>
#include <string_view>
#include "Product.hpp"

Product::Product(int id, std::string name, double price)
: m_id{id}
, m_name{name}
, m_price{price}
{}

Product::Product(int id, std::string name, double price, int quantity)
: m_id{id}
, m_name{name}
, m_price{price}
, m_quantity{quantity}
{}


Product::Product(int id, std::string name, double price, int quantity, std::array<char, 13> barCode)
: m_id{id}
, m_name{name}
, m_price{price}
, m_quantity{quantity}
, m_barCode(barCode)
{}

bool Product::setId(int id){
    this->m_id = id;
    return true;
}

bool Product::setName(std::string name){
    this->m_name = name;
    return true;
}

bool Product::setPrice(double price){
    this->m_price = price;
    return true;
}

bool Product::setBarCode(std::array<char, 13> barCode){
    this->m_barCode = barCode;
    return true;
}

int Product::getId(){return this->m_id;}
std::string_view Product::getName(){return this->m_name;}
int Product::getQuantity(){return this->m_quantity;}
double Product::getPrice(){return this->m_price;}
std::array<char, 13>& Product::getBarCode(){return this->m_barCode;}

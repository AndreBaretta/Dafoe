#include "Product.hpp"

Product::Product(const int id, const std::string& name)
: m_id{id}
, m_name{name}
{}

Product::Product(const int id, const std::string& name, const int quantity)
: m_id{id}
, m_name{name}
, m_quantity{quantity}
{}


Product::Product(const int id, const std::string& name, const int quantity, const int category)
: m_id{id}
, m_name{name}
, m_quantity{quantity}
{}

bool Product::setId(int id){
    this->m_id = id;
    return true;
}

bool Product::setQuantity(int qnty){
    this->m_quantity = qnty;
    return true;
}

bool Product::setBarCode(std::string barcode){
    this->m_barcode = barcode;
    return true;
}

bool Product::setName(std::string name){
    this->m_name = name;
    return true;
}

bool Product::setCategory(int category){
    this->m_category = category;
    return true;
}

std::string Product::getCategory(){return this->m_category;}
std::string Product::getBarCode(){return this->m_barcode;}
int Product::getId(){return this->m_id;}
std::string Product::getName(){return this->m_name;}
int Product::getQuantity(){return this->m_quantity;}

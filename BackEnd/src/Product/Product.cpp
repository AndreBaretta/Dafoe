#include "Product.hpp"

Product::Product(){}

Product::Product(const int id, const std::string& name, const int genericProduct, const int manufacturer, const std::string& barcode, const double price, const double cost, const std::string& reference, const int quantity)
: m_id{id}
, m_name{name}
, m_genericProduct{genericProduct}
, m_manufacturer{manufacturer}
, m_barcode{barcode}
, m_price{price}
, m_cost{cost}
, m_reference{reference}
, m_quantity{quantity}
{}


bool Product::setId(int id){
   m_id = id;
   return true;
}

bool Product::setName(std::string name){
   m_name = name;
   return true;
}

bool Product::setManufacturer(int manufacturer){
   m_manufacturer = manufacturer;
   return true;
}

bool Product::setGenericProduct(int genericProduct){
   m_genericProduct = genericProduct;
   return true;
}

bool Product::setBarcode(std::string barcode){
   m_barcode = barcode;
   return true;
}

bool Product::setPrice(double price){
   m_price = price;
   return true;
}

bool Product::setCost(double cost){
   m_cost = cost;
   return true;
}

bool Product::setReference(std::string reference){
   m_reference = reference;
   return true;
}

bool Product::setQuantity(int quantity){
   m_quantity = quantity;
   return true;
}

int Product::getId(){return m_id;}
std::string Product::getName(){return m_name;}
int Product::getManufacturer(){return m_manufacturer;}
int Product::getGenericProduct(){return m_genericProduct;}
std::string Product::getBarcode(){return m_barcode;}
double Product::getPrice(){return m_price;}
double Product::getCost(){return m_cost;}
std::string Product::getReference(){return m_reference;}
int Product::getQuantity(){return m_quantity;}




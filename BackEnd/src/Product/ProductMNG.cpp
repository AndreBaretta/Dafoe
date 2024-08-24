#include "ProductMNG.hpp"
#include <iostream>

ProductMNG::ProductMNG(ProductDAO& productDAO,JsonBuilder& jsonBuilder)
: m_productDAO{productDAO}
, m_jsonBuilder{jsonBuilder}
{}

ProductMNG::~ProductMNG(){}

// Create
bool ProductMNG::createProduct(const std::string& name, const int manufacturerId, const int quantity,
                         const int category, const std::string& barCode, const std::string& reference,
                         const double cost, const double price){
   return this->m_productDAO.createProduct(name,manufacturerId,quantity,category,barCode,reference,cost,price);
}


// Read
json ProductMNG::queryProductByName(const std::string& name){
   std::vector<Product> product = this->m_productDAO.retrieveByName(name);
   json json = this->m_jsonBuilder.productVectorToJson(product);
   return json;
}

json ProductMNG::retrieveAll(){
   std::vector<Product> products = this->m_productDAO.retrieveByName("");
   json json = this->m_jsonBuilder.productVectorToJson(products);
   return json;
}

json ProductMNG::retrieveProductByID(const int id){
   Product product = this->m_productDAO.retrieveByID(id);
   json json = this->m_jsonBuilder.productToJson(product);
   return json;
}

json ProductMNG::retrieveProductByBarCode(const std::string& barCode){
   Product product = this->m_productDAO.retrieveByBarCode(barCode);
   json json = this->m_jsonBuilder.productToJson(product);
   return json;
}

json ProductMNG::retrieveProductByReference(const std::string& reference){
   std::vector<Product> products = this->m_productDAO.retrieveByReference(reference);
   json json = this->m_jsonBuilder.productVectorToJson(products);
   return json;
}

// Update
bool ProductMNG::updateProduct(const int id, const std::string& name, const int manufacturerId, const int quantity,
                   const int category, const std::string& barCode, const std::string& reference,
                   const double cost, const double price){
   return this->m_productDAO.updateProduct(id,name,manufacturerId,quantity,category,barCode,reference,cost,price);
}

bool ProductMNG::updateCategoryPriceByNumber(const int category, const double price){
   return this->updateCategoryPriceByNumber(category,price);
}

bool ProductMNG::updateCategoryPriceByPercentage(const int category, const double price){
   return this->updateCategoryPriceByPercentage(category,price);
}

bool ProductMNG::deleteProduct(const int id){
   return this->m_productDAO.deleteProduct(id);
}
























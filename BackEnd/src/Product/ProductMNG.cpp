#include "ProductMNG.hpp"

ProductMNG::ProductMNG(ProductDAO& ProductDAO)
: m_productDAO{ProductDAO}
{}

ProductMNG::~ProductMNG(){}

// Create
bool ProductMNG::createProduct(const std::string& name, const int manufacturerId, const int quantity,
                         const int category, const std::string& barCode, const std::string& reference,
                         const double cost, const double price){
   return this->m_productDAO.createProduct(name,manufacturerId,quantity,category,barCode,reference,cost,price);
}


// Read
std::vector<Product> ProductMNG::queryProductByName(const std::string& name){
   return this->m_productDAO.retrieveByName(name);
}

Product ProductMNG::retrieveProductByID(const int id){
   return this->m_productDAO.retrieveByID(id);
}

Product ProductMNG::retrieveProductByBarCode(const std::string& barCode){
   return this->m_productDAO.retrieveByBarCode(barCode);
}

Product ProductMNG::retrieveProductByReference(const std::string& reference){
   return this->m_productDAO.retrieveByReference(reference);
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
























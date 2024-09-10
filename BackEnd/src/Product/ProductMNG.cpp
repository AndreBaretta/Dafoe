#include "ProductMNG.hpp"

ProductMNG::ProductMNG(ProductDAO& productDAO,JsonBuilder& jsonBuilder)
: m_productDAO{productDAO}
, m_jsonBuilder{jsonBuilder}
{}

ProductMNG::~ProductMNG(){}

// Create
bool ProductMNG::createProduct(const std::string& name, const int genericProduct, const int manufacturer, 
                               const std::string& barcode, const double price, const double cost, 
                               const std::string& reference, const int quantity){
   return this->m_productDAO.createProduct(name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);
}


// Read
json ProductMNG::queryProductByName(const std::string& name){
   try{
      std::vector<Product> product = this->m_productDAO.retrieveByName(name);
      json json = this->m_jsonBuilder.productVectorToJson(product);
      return json;
   }catch(std::exception &e){
      throw;
   }
}

json ProductMNG::retrieveAll(){
   try{
      std::vector<Product> products = this->m_productDAO.retrieveByName("");
      json json = this->m_jsonBuilder.productVectorToJson(products);
      return json;
   } catch(std::exception &e){
      throw;
   }
}

json ProductMNG::retrieveProductByID(const int id){
   try{
      std::vector<Product> products = this->m_productDAO.retrieveByID(id);
      json json = this->m_jsonBuilder.productVectorToJson(products);
      return json;
   } catch(std::exception &e){
      throw;
   }
}

json ProductMNG::retrieveProductByBarCode(const std::string& barcode){
   try{
      std::vector<Product> product = this->m_productDAO.retrieveByBarcode(barcode);
      json json = this->m_jsonBuilder.productVectorToJson(product);
      return json;
   } catch(std::exception &e){
      throw;
   }
}

json ProductMNG::retrieveProductByReference(const std::string& reference){
   try{
      std::vector<Product> products = this->m_productDAO.retrieveByReference(reference);
      json json = this->m_jsonBuilder.productVectorToJson(products);
      return json;
   }catch(std::exception &e){
      throw;
   }
}

// Update
bool ProductMNG::updateProduct(const int id, const std::string& name, const int genericProduct, const int manufacturer,
                               const std::string& barcode, const double price, const double cost, const std::string& reference,
                               const int quantity){
   return this->m_productDAO.updateProduct(id,name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);
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
























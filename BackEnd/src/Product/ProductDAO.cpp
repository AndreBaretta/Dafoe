#include "ProductDAO.hpp"
#include <iostream>
//NEED TO ADD TRY CATCHES TO ALL SQL QUERIES


ProductDAO::ProductDAO(DafoeGod& zeus)
: m_theos{zeus}
{}

std::vector<Product> ProductDAO::retrieveByName(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where name like ?")};
   state->setString(1, '%' + name + '%');
   sql::ResultSet* result {state->executeQuery()};
   
   Product product{};
   std::vector<Product> products{};
   while(result->next()){
      int productId = result->getInt("id");
      std::string productName = result->getString("name").c_str();
      int productGenericProduct = result->getInt("genericProduct");
      int productManufacturer = result->getInt("manufacturer");
      std::string productBarcode = result->getString("barcode").c_str();
      double productPrice = result->getDouble("price");
      double productCost = result->getDouble("cost");
      std::string productReference = result->getString("reference").c_str();
      int productQuantity = result->getInt("quantity");
      product = Product(productId, productName, productGenericProduct,productManufacturer,productBarcode,productPrice,productCost,productReference,productQuantity);
      products.push_back(product);
   }

   return products;
}

Product ProductDAO::retrieveByID(const int id){
   std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where id = ?")};
   state->setInt(1,id);
   sql::ResultSet* result {state->executeQuery()};
   Product product{};
   if(!result->next())
      return product;
   int productId = result->getInt("id");
   std::string productName = result->getString("name").c_str();
   int productGenericProduct = result->getInt("genericProduct");
   int productManufacturer = result->getInt("manufacturer");
   std::string productBarcode = result->getString("barcode").c_str();
   double productPrice = result->getDouble("price");
   double productCost = result->getDouble("cost");
   std::string productReference = result->getString("reference").c_str();
   int productQuantity = result->getInt("quantity");
   product = Product(productId, productName, productGenericProduct,productManufacturer,productBarcode,productPrice,productCost,productReference,productQuantity);

   return product;
}

Product ProductDAO::retrieveByBarcode(const std::string& barcode){
   std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where barcode = ?")};
   state->setString(1,barcode);
   sql::ResultSet* result {state->executeQuery()};
   result->next();

   Product product{};
   int productId = result->getInt("id");
   std::string productName = result->getString("name").c_str();
   int productGenericProduct = result->getInt("genericProduct");
   int productManufacturer = result->getInt("manufacturer");
   std::string productBarcode = result->getString("barcode").c_str();
   double productPrice = result->getDouble("price");
   double productCost = result->getDouble("cost");
   std::string productReference = result->getString("reference").c_str();
   int productQuantity = result->getInt("quantity");
   product = Product(productId, productName, productGenericProduct,productManufacturer,productBarcode,productPrice,productCost,productReference,productQuantity);

   return product;
}

std::vector<Product> ProductDAO::retrieveByReference(const std::string& reference){
   std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select * from product where reference like ?")};
   state->setString(1,'%' + reference + '%');
   sql::ResultSet* result {state->executeQuery()};

   Product product{};
   std::vector<Product> products{};
   while(result->next()){
      int productId = result->getInt("id");
      std::string productName = result->getString("name").c_str();
      int productGenericProduct = result->getInt("genericProduct");
      int productManufacturer = result->getInt("manufacturer");
      std::string productBarcode = result->getString("barcode").c_str();
      double productPrice = result->getDouble("price");
      double productCost = result->getDouble("cost");
      std::string productReference = result->getString("reference").c_str();
      int productQuantity = result->getInt("quantity");
      product = Product(productId, productName, productGenericProduct,productManufacturer,productBarcode,productPrice,productCost,productReference,productQuantity);
      products.push_back(product);
   }

   return products;
}
std::vector<Product> ProductDAO::retrieveByManufacturer(const std::string& manufacturer){
   std::unique_ptr<sql::PreparedStatement> state{m_theos.conn->prepareStatement("select id from manufacturer where name like ?")};
   state->setString(1,'%' + manufacturer + '%');
   sql::ResultSet* result {state->executeQuery()};

   Product product{};
   std::vector<Product> products{};
   while(result->next()){
      int productId = result->getInt("id");
      std::string productName = result->getString("name").c_str();
      int productGenericProduct = result->getInt("genericProduct");
      int productManufacturer = result->getInt("manufacturer");
      std::string productBarcode = result->getString("barcode").c_str();
      double productPrice = result->getDouble("price");
      double productCost = result->getDouble("cost");
      std::string productReference = result->getString("reference").c_str();
      int productQuantity = result->getInt("quantity");
      product = Product(productId, productName, productGenericProduct,productManufacturer,productBarcode,productPrice,productCost,productReference,productQuantity);
      products.push_back(product);
   }

   return products;
}

bool ProductDAO::createProduct(const std::string& name, const int genericProduct, const int manufacturer,
                               const std::string& barcode, const double price, const double cost, 
                               const std::string& reference,const int quantity){

   std::unique_ptr<sql::PreparedStatement> statement{m_theos.conn->prepareStatement("insert into product (genericProduct, manufacturer, name, barcode, price, cost, reference, quantity) values (?, ?, ?, ?, ?, ?, ?, ?);")};
   statement->setInt(1, genericProduct);
   statement->setInt(2, manufacturer);
   statement->setString(3, name);
   statement->setString(4, barcode);
   statement->setDouble(5, price);
   statement->setDouble(6, cost);
   statement->setString(7, reference);
   statement->setInt(8, quantity);

   statement->executeQuery();

   return true;
}

bool ProductDAO::deleteProduct(const int id){
   std::unique_ptr<sql::PreparedStatement> state(m_theos.conn->prepareStatement("delete from product where id = ?"));
   state->setInt(1, id);
   state->executeQuery();

   return true;
}

bool ProductDAO::updateProduct(const int id, const std::string& name, const int genericProduct, 
                               const int manufacturer, const std::string& barcode, const double price,
                               const double cost, const std::string& reference, const int quantity){
   std::unique_ptr<sql::PreparedStatement> statement(m_theos.conn->prepareStatement("update product set name = ?, genericProduct = ?, manufacturer = ?, barcode = ?, price = ?, cost = ?, reference = ?, quantity = ? where id = ?"));
   statement->setString(1, name);
   statement->setInt(2, genericProduct);
   statement->setInt(3, manufacturer);
   statement->setString(4, barcode);
   statement->setDouble(5, price);
   statement->setDouble(6, cost);
   statement->setString(7, reference);
   statement->setInt(8, quantity);
   statement->setInt(9, id);

   statement->executeQuery();

   return true;
}

bool ProductDAO::updateCategoryPriceByNumber(const int category, const double price){
   std::unique_ptr<sql::PreparedStatement> statement(m_theos.conn->prepareStatement("update productManufacturer set price = price+? where category = ?"));
   statement->setDouble(1, price);
   statement->setInt(2, category);
   statement->executeQuery();

   return true;
}

bool ProductDAO::updateCategoryPriceByPercentage(const int category, const double percentage){
   std::unique_ptr<sql::PreparedStatement> statement(m_theos.conn->prepareStatement("update productManufacturer set price = price+(price/100)*? where category = ?"));
   statement->setDouble(1, percentage);
   statement->setInt(2, category);
   statement->executeQuery();

   return true;
}


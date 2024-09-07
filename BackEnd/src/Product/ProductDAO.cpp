#include "ProductDAO.hpp"
#include <iostream>
#include "../Type/Enum.hpp"

ProductDAO::ProductDAO(DafoeGod& zeus)
: m_theos{zeus}
{}

std::vector<Product> ProductDAO::retrieveByName(const std::string& name){
   try{
      m_theos.prepareStatement("select * from product where name like ?");
      m_theos.getStatement()->setString(1, '%' + name + '%');
      m_theos.query(RETRIEVE);

      Product product{};
      std::vector<Product> products{};
      while(m_theos.getResult()->next()){
         int productId = m_theos.getResult()->getInt("id");
         std::string productName = m_theos.getResult()->getString("name").c_str();
         int productGenericProduct = m_theos.getResult()->getInt("genericProduct");
         int productManufacturer = m_theos.getResult()->getInt("manufacturer");
         std::string productBarcode = m_theos.getResult()->getString("barcode").c_str();
         double productPrice = m_theos.getResult()->getDouble("price");
         double productCost = m_theos.getResult()->getDouble("cost");
         std::string productReference = m_theos.getResult()->getString("reference").c_str();
         int productQuantity = m_theos.getResult()->getInt("quantity");
         product = Product(productId, productName, productGenericProduct,productManufacturer,
                           productBarcode,productPrice,productCost,productReference,productQuantity);
         products.push_back(product);
      }

      return products;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Product> ProductDAO::retrieveByID(const int id){
   try{
      m_theos.prepareStatement("select * from product where id = ?");
      m_theos.getStatement()->setInt(1,id);
      m_theos.query(RETRIEVE);

      std::vector<Product> products{};
      Product product{};
      if(!m_theos.getResult()->next())
         return products;

      int productId = m_theos.getResult()->getInt("id");
      std::string productName = m_theos.getResult()->getString("name").c_str();
      int productGenericProduct = m_theos.getResult()->getInt("genericProduct");
      int productManufacturer = m_theos.getResult()->getInt("manufacturer");
      std::string productBarcode = m_theos.getResult()->getString("barcode").c_str();
      double productPrice = m_theos.getResult()->getDouble("price");
      double productCost = m_theos.getResult()->getDouble("cost");
      std::string productReference = m_theos.getResult()->getString("reference").c_str();
      int productQuantity = m_theos.getResult()->getInt("quantity");
      product = Product(productId, productName, productGenericProduct,
                        productManufacturer,productBarcode,productPrice,
                        productCost,productReference,productQuantity);
      products.push_back(product);

      return products;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Product> ProductDAO::retrieveByBarcode(const std::string& barcode){
   try{
      m_theos.prepareStatement("select * from product where barcode = ?");
      m_theos.getStatement()->setString(1,barcode);
      m_theos.query(RETRIEVE);

      std::vector<Product> products;
      if(!m_theos.getResult()->next())
         return products;

      Product product{};
      int productId = m_theos.getResult()->getInt("id");
      std::string productName = m_theos.getResult()->getString("name").c_str();
      int productGenericProduct = m_theos.getResult()->getInt("genericProduct");
      int productManufacturer = m_theos.getResult()->getInt("manufacturer");
      std::string productBarcode = m_theos.getResult()->getString("barcode").c_str();
      double productPrice = m_theos.getResult()->getDouble("price");
      double productCost = m_theos.getResult()->getDouble("cost");
      std::string productReference = m_theos.getResult()->getString("reference").c_str();
      int productQuantity = m_theos.getResult()->getInt("quantity");
      product = Product(productId, productName, productGenericProduct,
                        productManufacturer,productBarcode,productPrice,
                        productCost,productReference,productQuantity);
      products.push_back(product);

      return products;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

std::vector<Product> ProductDAO::retrieveByReference(const std::string& reference){
   try{
      m_theos.prepareStatement("select * from product where reference like ?");
      m_theos.getStatement()->setString(1,'%' + reference + '%');
      m_theos.query(RETRIEVE); 

      Product product{};
      std::vector<Product> products{};
      while(m_theos.getResult()->next()){
         int productId = m_theos.getResult()->getInt("id");
         std::string productName = m_theos.getResult()->getString("name").c_str();
         int productGenericProduct = m_theos.getResult()->getInt("genericProduct");
         int productManufacturer = m_theos.getResult()->getInt("manufacturer");
         std::string productBarcode = m_theos.getResult()->getString("barcode").c_str();
         double productPrice = m_theos.getResult()->getDouble("price");
         double productCost = m_theos.getResult()->getDouble("cost");
         std::string productReference = m_theos.getResult()->getString("reference").c_str();
         int productQuantity = m_theos.getResult()->getInt("quantity");
         product = Product(productId, productName, productGenericProduct,
                           productManufacturer,productBarcode,productPrice,
                           productCost,productReference,productQuantity);
         products.push_back(product);
      }

      return products;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}
std::vector<Product> ProductDAO::retrieveByManufacturer(const int manufacturer){
   try{
      m_theos.prepareStatement("select * from product where manufacturer = ?");
      m_theos.getStatement()->setInt(1,manufacturer);
      m_theos.query(RETRIEVE);

      Product product{};
      std::vector<Product> products{};
      while(m_theos.getResult()->next()){
         int productId = m_theos.getResult()->getInt("id");
         std::string productName = m_theos.getResult()->getString("name").c_str();
         int productGenericProduct = m_theos.getResult()->getInt("genericProduct");
         int productManufacturer = m_theos.getResult()->getInt("manufacturer");
         std::string productBarcode = m_theos.getResult()->getString("barcode").c_str();
         double productPrice = m_theos.getResult()->getDouble("price");
         double productCost = m_theos.getResult()->getDouble("cost");
         std::string productReference = m_theos.getResult()->getString("reference").c_str();
         int productQuantity = m_theos.getResult()->getInt("quantity");
         product = Product(productId, productName, productGenericProduct,
                           productManufacturer,productBarcode,productPrice,
                           productCost,productReference,productQuantity);
         products.push_back(product);
      }

      return products;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

std::vector<Product> ProductDAO::retrieveByPrice(const double cost){
   try{
      m_theos.prepareStatement("select * product where cost = ?");
      m_theos.getStatement()->setDouble(1, cost);
      m_theos.query(RETRIEVE);

      Product product{};
      std::vector<Product> products{};
      while(m_theos.getResult()->next()){
         int productId = m_theos.getResult()->getInt("id");
         std::string productName = m_theos.getResult()->getString("name").c_str();
         int productGenericProduct = m_theos.getResult()->getInt("genericProduct");
         int productManufacturer = m_theos.getResult()->getInt("manufacturer");
         std::string productBarcode = m_theos.getResult()->getString("barcode").c_str();
         double productPrice = m_theos.getResult()->getDouble("price");
         double productCost = m_theos.getResult()->getDouble("cost");
         std::string productReference = m_theos.getResult()->getString("reference").c_str();
         int productQuantity = m_theos.getResult()->getInt("quantity");
         product = Product(productId, productName, productGenericProduct,
                           productManufacturer,productBarcode,productPrice,
                           productCost,productReference,productQuantity);
         products.push_back(product);
      }

      return products;  

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }


}

bool ProductDAO::createProduct(const std::string& name, const int genericProduct, const int manufacturer,
                               const std::string& barcode, const double price, const double cost, 
                               const std::string& reference,const int quantity){
   try{
      m_theos.prepareStatement("insert into product (genericProduct, manufacturer, name, barcode, price, cost, reference, quantity) values (?, ?, ?, ?, ?, ?, ?, ?);");
      m_theos.getStatement()->setInt(1, genericProduct);
      m_theos.getStatement()->setInt(2, manufacturer);
      m_theos.getStatement()->setString(3, name);
      m_theos.getStatement()->setString(4, barcode);
      m_theos.getStatement()->setDouble(5, price);
      m_theos.getStatement()->setDouble(6, cost);
      m_theos.getStatement()->setString(7, reference);
      m_theos.getStatement()->setInt(8, quantity);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

bool ProductDAO::deleteProduct(const int id){
   try{
      m_theos.prepareStatement("delete from product where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.getStatement()->executeQuery();

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

bool ProductDAO::updateProduct(const int id, const std::string& name, const int genericProduct, 
                               const int manufacturer, const std::string& barcode, const double price,
                               const double cost, const std::string& reference, const int quantity){
   try{
      m_theos.prepareStatement("update product set name = ?, genericProduct = ?, manufacturer = ?, barcode = ?, price = ?, cost = ?, reference = ?, quantity = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, genericProduct);
      m_theos.getStatement()->setInt(3, manufacturer);
      m_theos.getStatement()->setString(4, barcode);
      m_theos.getStatement()->setDouble(5, price);
      m_theos.getStatement()->setDouble(6, cost);
      m_theos.getStatement()->setString(7, reference);
      m_theos.getStatement()->setInt(8, quantity);
      m_theos.getStatement()->setInt(9, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }


}

bool ProductDAO::updateCategoryPriceByNumber(const int category, const double price){
   try{
      m_theos.prepareStatement("update productManufacturer set price = price+? where category = ?");
      m_theos.getStatement()->setDouble(1, price);
      m_theos.getStatement()->setInt(2, category);
      m_theos.getStatement()->executeQuery();

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

bool ProductDAO::updateCategoryPriceByPercentage(const int category, const double percentage){
   try{
      m_theos.prepareStatement("update productManufacturer set price = price+(price/100)*? where category = ?");
      m_theos.getStatement()->setDouble(1, percentage);
      m_theos.getStatement()->setInt(2, category);
      m_theos.getStatement()->executeQuery();

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}


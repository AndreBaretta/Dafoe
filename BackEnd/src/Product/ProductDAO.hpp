#ifndef PRODUCTDAO_1836
#define PRODUCTDAO_1836
#include "../DafoeGod/DafoeGod.hpp"
#include "Product.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <vector>

class ProductDAO{
public:
   ProductDAO(DafoeGod& zeus);
   std::vector<Product> retrieveByName(const std::string& name);
   std::vector<Product> retrieveByID(const int id);
   std::vector<Product> retrieveByReference(const std::string& reference);
   std::vector<Product> retrieveByManufacturer(const std::string& manufacturer);
   std::vector<Product> retrieveByBarcode(const std::string& barcode);

   bool createProduct(const std::string& name, const int genericProduct, const int manufacturer,
                      const std::string& barcode, const double price, const double cost, 
                      const std::string& reference, const int quantity);

   bool deleteProduct(const int id);

   bool updateProduct(const int id, const std::string& name, const int genericProduct,
                      const int manufacturer, const std::string& barcode, const double price,
                      const double cost, const std::string& reference, const int quantity);

   bool updateCategoryPriceByNumber(const int category, const double price);
   bool updateCategoryPriceByPercentage(const int category, const double percentage);

private:
   DafoeGod& m_theos;
};

#endif

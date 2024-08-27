#ifndef PRODUCTDAO_1836
#define PRODUCTDAO_1836
#include "../DafoeGod/DafoeGod.hpp"
#include "Product.hpp"
#include <mariadb/conncpp/ResultSet.hpp>
#include <vector>

class ProductDAO{
public:

   ProductDAO(DafoeGod& zeus);
   std::vector<Product> retrieveByName(std::string name);
   Product retrieveByID(const int id);
   std::vector<Product> retrieveByReference(std::string reference);
   std::vector<Product> retrieveByManufacturer(std::string manufacturer);
   Product retrieveByBarCode(std::string barCode);

   bool createProduct(const std::string& name, const int genericProduct, const int manufacturerId,
                      const std::string& barCode, const double price, const double cost, 
                      const std::string& reference, const int quantity);

   bool deleteProduct(const int id);

   bool updateProduct(const int id, const std::string& name, const int manufacturerId,
                      const int quantity, const int category, const std::string& barCode,
                      const std::string& reference, const double cost, const double price);

   bool updateCategoryPriceByNumber(const int category, const double price);
   bool updateCategoryPriceByPercentage(const int category, const double percentage);
private:
   static inline int s_id{0};
   static inline int s_genericProductId{0};
   DafoeGod& m_theos;
};

#endif

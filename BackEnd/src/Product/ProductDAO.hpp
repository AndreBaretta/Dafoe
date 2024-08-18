#ifndef PRODUCTDAO_1836
#define PRODUCTDAO_1836
#include "../DafoeGod/DafoeGod.hpp"
#include "Product.hpp"
#include <mariadb/conncpp/ResultSet.hpp>

class ProductDAO{
public:

   ProductDAO(DafoeGod& zeus);
   std::vector<Product> retrieveByName(const std::string& name);
   Product retrieveByID(const int id);
   Product retrieveByReference(const std::string& reference);
   std::vector<Product> retrieveByManufacturer(const std::string& manufacturer);
   Product retrieveByBarCode(const std::string& barCode);

   bool createProduct(const std::string& name, const int manufacturerId, const int quantity,
                      const int category, const std::string& barCode, const std::string& reference,
                      const double cost, const double price);

   bool deleteProduct(const int id);

   bool updateProduct(const int id, const std::string& name, const int manufacturerId,
                      const int quantity, const int category, const std::string& barCode,
                      const std::string& reference, const double cost, const double price);

   bool updateCategoryPriceByNumber(const int category, const double price);
   bool updateCategoryPriceByPercentage(const int category, const double percentage);
private:
   static inline int s_id{0};
   DafoeGod& m_theos;
   sql::ResultSet* result{};
};

#endif

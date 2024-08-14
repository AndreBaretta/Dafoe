#ifndef PRODUCTDAO_1836
#define PRODUCTDAO_1836
#include "../DafoeGod/DafoeGod.hpp"
#include "Product.hpp"
#include <mariadb/conncpp/ResultSet.hpp>
class Manufacturer{};

class ProductDAO{
public:
   ProductDAO(DafoeGod& zeus);
   std::vector<Product> retrieveByName(const std::string& name);
   std::vector<Product> retrieveByID(const int id);
   std::vector<Product> retrieveByReference(const std::string& reference);
   std::vector<Product> retrieveByManufacturer(const Manufacturer& manufacturer);
   std::vector<Product> retrieveByBarCode(const std::string& barCodetd);
private:
   DafoeGod& m_theos;
   sql::ResultSet* result{};
};

#endif

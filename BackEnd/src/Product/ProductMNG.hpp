#ifndef PRODUCTMNG_2208
#define PRODUCTMNG_2208
#include "ProductDAO.hpp"
#include "Product.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <vector>


class ProductMNG{
public:
   ProductMNG(ProductDAO& productDAO, JsonBuilder& jsonBuilder);
   ~ProductMNG();
   // Create
   bool createProduct(const std::string& name, const int genericProduct, const int manufacturer, 
                      const std::string& barcode, const double price, const double cost, 
                      const std::string& reference, const int quantity);

   // Read
   json queryProductByName(const std::string& name);
   json retrieveAll();
   json retrieveProductByID(const int id);
   json retrieveProductByReference(const std::string& reference);
   json retrieveProductByBarCode(const std::string& barCode);

   // Update
   bool updateProduct(const int id, const std::string& name, const int genericProduct, const int manufacturer,
                      const std::string& barcode, const double price, const double cost, const std::string& reference,
                      const int quantity);
   bool updateCategoryPriceByNumber(const int category, const double price);
   bool updateCategoryPriceByPercentage(const int category, const double percentage);

   // Delete
   bool deleteProduct(const int id);

private:
   ProductDAO& m_productDAO;
   JsonBuilder& m_jsonBuilder;
};




#endif


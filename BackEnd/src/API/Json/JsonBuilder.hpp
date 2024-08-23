#ifndef JSONBUILDER_0035
#define JSONBUILDER_0035
#include "../../Product/Product.hpp"
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class JsonBuilder{
   public:
      JsonBuilder();
      ~JsonBuilder();
      json productToJson(const Product& product);
      json productVectorToJson(const std::vector<Product>& products);
      
};


#endif

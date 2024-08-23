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
      json productToJson(Product& product);
      json productVectorToJson(std::vector<Product>& products);
      
};


#endif

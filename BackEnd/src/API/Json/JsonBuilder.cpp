#include "JsonBuilder.hpp"

JsonBuilder::JsonBuilder(){}
JsonBuilder::~JsonBuilder(){}

json JsonBuilder::productToJson(const Product& product){
   json jsonProduct;
   jsonProduct["id"]       = product.getId();
   jsonProduct["name"]     = product.getName();
   jsonProduct["barcode"]  = product.getBarCode();
   jsonProduct["quantity"] = product.getQuantity();
   jsonProduct["category"] = product.getCategory();
   return jsonProduct;
}

json JsonBuilder::productVectorToJson(const std::vector<Product>& products){
   json jsonProductArray = json::array();
   for(int i = 0; i < products.size(); i++){
      json jsonProduct;
      jsonProduct["id"]       = products[i].getId();
      jsonProduct["name"]     = products[i].getName();
      jsonProduct["barcode"]  = products[i].getBarCode();
      jsonProduct["quantity"] = products[i].getQuantity();
      jsonProduct["category"] = products[i].getCategory();
      jsonProductArray.push_back(jsonProduct);
   }
   return jsonProductArray;
}



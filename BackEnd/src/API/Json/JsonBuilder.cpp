#include "JsonBuilder.hpp"

JsonBuilder::JsonBuilder(){}
JsonBuilder::~JsonBuilder(){}

json JsonBuilder::productToJson(Product& product){
   json jsonProduct;
   jsonProduct["id"]        = product.getId();
   jsonProduct["name"]      = product.getName();
   jsonProduct["barcode"]   = product.getBarcode();
   jsonProduct["price"]     = product.getPrice();
   jsonProduct["cost"]      = product.getCost();
   jsonProduct["reference"] = product.getReference();
   jsonProduct["quantity"]  = product.getQuantity();
   return jsonProduct;
}

json JsonBuilder::productVectorToJson(std::vector<Product>& products){
   json jsonProductArray = json::array();
   for(int i = 0; i < products.size(); i++){
      json jsonProduct;
      jsonProduct["id"]        = products[i].getId();
      jsonProduct["name"]      = products[i].getName();
      jsonProduct["barcode"]   = products[i].getBarcode();
      jsonProduct["price"]     = products[i].getPrice();
      jsonProduct["cost"]      = products[i].getCost();
      jsonProduct["reference"] = products[i].getReference();
      jsonProduct["quantity"]  = products[i].getQuantity();
      jsonProductArray.push_back(jsonProduct);
   }
   return jsonProductArray;
}



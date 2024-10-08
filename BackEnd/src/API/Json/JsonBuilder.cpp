#include "JsonBuilder.hpp"
#include <iostream>

JsonBuilder::JsonBuilder(){}
JsonBuilder::~JsonBuilder(){}

json JsonBuilder::productToJson(Product& product){
   json jsonProduct;
   jsonProduct["id"]             = product.getId();
   jsonProduct["manufacturer"]   = product.getManufacturer();
   jsonProduct["genericProduct"] = product.getGenericProduct();
   jsonProduct["name"]           = product.getName();
   jsonProduct["barcode"]        = product.getBarcode();
   jsonProduct["price"]          = product.getPrice();
   jsonProduct["cost"]           = product.getCost();
   jsonProduct["reference"]      = product.getReference();
   jsonProduct["quantity"]       = product.getQuantity();
   return jsonProduct;
}

json JsonBuilder::productVectorToJson(std::vector<Product>& products){
   json jsonProductArray = json::array();
   for(int i = 0; i < products.size(); i++){
      json jsonProduct;
      jsonProduct["id"]             = products[i].getId();
      jsonProduct["manufacturer"]   = products[i].getManufacturer();
      jsonProduct["genericProduct"] = products[i].getGenericProduct();
      jsonProduct["name"]           = products[i].getName();
      jsonProduct["barcode"]        = products[i].getBarcode();
      jsonProduct["price"]          = products[i].getPrice();
      jsonProduct["cost"]           = products[i].getCost();
      jsonProduct["reference"]      = products[i].getReference();
      jsonProduct["quantity"]       = products[i].getQuantity();
      jsonProductArray.push_back(jsonProduct);
   }
   return jsonProductArray;
}

json JsonBuilder::categoryToJson(Category& category){
   json jsonCategory;
   jsonCategory["id"]   = category.getId();
   jsonCategory["name"] = category.getName();
   return jsonCategory;
}

json JsonBuilder::categoryVectorToJson(std::vector<Category>& categories){
   json jsonCategoryArray = json::array();
   for(int i = 0; i < categories.size(); i++){
      json jsonCategory;
      jsonCategory["id"]   = categories[i].getId();
      jsonCategory["name"] = categories[i].getName();
      jsonCategoryArray.push_back(jsonCategory);
   }
   return jsonCategoryArray;
}

json JsonBuilder::paymentMethodToJson(PaymentMethod& paymentMethod){
   json jsonPaymentMethod = json::array();
   jsonPaymentMethod["id"]   = paymentMethod.getId();
   jsonPaymentMethod["name"] = paymentMethod.getName();
   return jsonPaymentMethod;
}

json JsonBuilder::paymentMethodVectorToJson(std::vector<PaymentMethod>& paymentMethods){
   json jsonPaymentMethodArray = json::array();
   for(int i = 0; i < paymentMethods.size(); i++){
      json jsonPaymentMethod;
      jsonPaymentMethod["id"]   = paymentMethods[i].getId();
      jsonPaymentMethod["name"] = paymentMethods[i].getName();
      jsonPaymentMethodArray.push_back(jsonPaymentMethod);
   }
   return jsonPaymentMethodArray;
}

json JsonBuilder::employeeToJson(Employee& employee){
   json jsonEmployee;
   jsonEmployee["id"]    = employee.getId();
   jsonEmployee["name"]  = employee.getName();
   jsonEmployee["cargo"] = employee.getCargo();
   return jsonEmployee;
}

json JsonBuilder::employeeVectorToJson(std::vector<Employee>& employees){
   json jsonEmployeeArray = json::array();
   for(int i = 0; i < employees.size(); i++){
      json jsonEmployee;
      jsonEmployee["id"]    = employees[i].getId();
      jsonEmployee["name"]  = employees[i].getName();
      jsonEmployee["cargo"] = employees[i].getCargo();
      jsonEmployeeArray.push_back(jsonEmployee);
   }
   return jsonEmployeeArray;
}

json JsonBuilder::manufacturerToJson(Manufacturer& manufacturer){
   json jsonManufacturer;
   jsonManufacturer["id"]   = manufacturer.getId();
   jsonManufacturer["name"] = manufacturer.getName();
   return jsonManufacturer;
}

json JsonBuilder::manufacturerVectorToJson(std::vector<Manufacturer>& manufacturers){
   json jsonManufacturerArray = json::array();
   for(int i = 0; i < manufacturers.size(); i++){
      json jsonManufacturer;
      jsonManufacturer["id"]   = manufacturers[i].getId();
      jsonManufacturer["name"] = manufacturers[i].getName();
      jsonManufacturerArray.push_back(jsonManufacturer);
   }
   return jsonManufacturerArray;
}

json JsonBuilder::statusToJson(Status& status){
   json jsonStatus;
   jsonStatus["id"]   = status.getId();
   jsonStatus["name"] = status.getName();
   return jsonStatus;
}

json JsonBuilder::statusVectorToJson(std::vector<Status>& statuses){
   json jsonStatusArray = json::array();
   for(int i = 0; i < statuses.size(); i++){
      json jsonStatus;
      jsonStatus["id"]   = statuses[i].getId();
      jsonStatus["name"] = statuses[i].getName();
      jsonStatusArray.push_back(jsonStatus);
   }
   return jsonStatusArray;
}


json JsonBuilder::sellOrderToJson(SellOrder& sellOrder){
   json jsonSellOrder;
   jsonSellOrder["id"]            = sellOrder.getId();
   jsonSellOrder["clientId"]      = sellOrder.getClientId();
   jsonSellOrder["sellerId"]      = sellOrder.getSellerId();
   jsonSellOrder["statusId"]      = sellOrder.getStatusId();
   jsonSellOrder["paymentMethod"] = sellOrder.getPaymentMethod();
   jsonSellOrder["date"]          = sellOrder.getDate();
   jsonSellOrder["price"]         = sellOrder.getPrice();
   return jsonSellOrder;
}

json JsonBuilder::sellOrderVectorToJson(std::vector<SellOrder>& sellOrders){
   json jsonSellOrderArray = json::array();
   for(int i = 0; i < sellOrders.size(); i++){
      json jsonSellOrder;
      jsonSellOrder["id"]            = sellOrders[i].getId();
      jsonSellOrder["clientId"]      = sellOrders[i].getClientId();
      jsonSellOrder["sellerId"]      = sellOrders[i].getSellerId();
      jsonSellOrder["statusId"]      = sellOrders[i].getStatusId();
      jsonSellOrder["paymentMethod"] = sellOrders[i].getPaymentMethod();
      jsonSellOrder["date"]          = sellOrders[i].getDate();
      jsonSellOrder["price"]         = sellOrders[i].getPrice();
      jsonSellOrderArray.push_back(jsonSellOrder);
   }
   return jsonSellOrderArray;
}

json JsonBuilder::genericProductToJson(GenericProduct& genericProduct){
   json jsonGenericProduct;
   jsonGenericProduct["id"]        = genericProduct.getId();
   jsonGenericProduct["name"]      = genericProduct.getName();
   jsonGenericProduct["category"]  = genericProduct.getCategory();
   return jsonGenericProduct;
}

json JsonBuilder::genericProductVectorToJson(std::vector<GenericProduct>& genericProducts){
   json jsonGenericProductArray = json::array();
   for(int i = 0; i < genericProducts.size(); i++){
      json jsonGenericProduct;
      jsonGenericProduct["id"]        = genericProducts[i].getId();
      jsonGenericProduct["name"]      = genericProducts[i].getName();
      jsonGenericProduct["category"]  = genericProducts[i].getCategory();
      jsonGenericProductArray.push_back(jsonGenericProduct);
   }
   return jsonGenericProductArray;
}

json JsonBuilder::productOrderToJson(ProductOrder& productOrder){
   json jsonProductOrder;
   jsonProductOrder["sellOrder"] = productOrder.getSellOrder();
   jsonProductOrder["product"]   = productOrder.getProduct();
   jsonProductOrder["quantity"]  = productOrder.getQuantity();
   jsonProductOrder["discount"]  = productOrder.getDiscount();
   jsonProductOrder["price"]     = productOrder.getPrice();
   return jsonProductOrder;
}

json JsonBuilder::productOrderVectorToJson(std::vector<ProductOrder>& productOrders){
   json jsonProductOrderArray = json::array();
   for(int i = 0; i < productOrders.size(); i++){
      json jsonProductOrder;
      jsonProductOrder["sellOrder"] = productOrders[i].getSellOrder();
      jsonProductOrder["product"]   = productOrders[i].getProduct();
      jsonProductOrder["quantity"]  = productOrders[i].getQuantity();
      jsonProductOrder["discount"]  = productOrders[i].getDiscount();
      jsonProductOrder["price"]     = productOrders[i].getPrice();     
      jsonProductOrderArray.push_back(jsonProductOrder);
   }
   return jsonProductOrderArray;
}

std::vector<ProductOrder> JsonBuilder::jsonToProductOrderVector(json json, int order){
   try{
      std::vector<ProductOrder> products;
      for (const auto& e: json["products"]){
         int id = e["id"];
         std::string name = e["name"];
         int quantity = e["quantity"];
         double discount = e["discount"];
         double price = e["price"];

         products.push_back(ProductOrder(order, id, quantity, discount, price));
      }
      return products;
   }catch(std::exception &e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

json JsonBuilder::clientToJson(Client& client){
   json jsonClient;
   jsonClient["id"]          = client.getId();
   jsonClient["name"]        = client.getName();
   jsonClient["bill"]        = client.getBill();
   jsonClient["address"]     = client.getAddress();
   jsonClient["phoneNumber"] = client.getPhoneNumber(); 
   return jsonClient;
}

json JsonBuilder::clientVectorToJson(std::vector<Client>& clients){
   json jsonClientArray = json::array();
   for(int i = 0; i < clients.size(); i++){
      json jsonClient;
      jsonClient["id"]           = clients[i].getId();
      jsonClient["name"]         = clients[i].getName();
      jsonClient["bill"]         = clients[i].getBill();
      jsonClient["address"]      = clients[i].getAddress();
      jsonClient["phoneNumber"]  = clients[i].getPhoneNumber();
      jsonClientArray.push_back(jsonClient);
   }
   return jsonClientArray;
}




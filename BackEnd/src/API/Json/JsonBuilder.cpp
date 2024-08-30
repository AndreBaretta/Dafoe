#include "JsonBuilder.hpp"

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
   json jsonCategoryArray;
   for(int i = 0; i < categories.size(); i++){
      json jsonCategory;
      jsonCategory["id"]   = categories[i].getId();
      jsonCategory["name"] = categories[i].getName();
      jsonCategoryArray.push_back(jsonCategory);
   }
   return jsonCategoryArray;
}

json JsonBuilder::paymentMethodToJson(PaymentMethod& paymentMethod){
   json jsonPaymentMethod;
   jsonPaymentMethod["id"]   = paymentMethod.getId();
   jsonPaymentMethod["name"] = paymentMethod.getName();
   return jsonPaymentMethod;
}

json JsonBuilder::paymentMethodVectorToJson(std::vector<PaymentMethod>& paymentMethods){
   json jsonPaymentMethodArray;
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
   jsonEmployee["id"]   = employee.getId();
   jsonEmployee["name"] = employee.getName();
   return jsonEmployee;
}

json JsonBuilder::employeeVectorToJson(std::vector<Employee>& employees){
   json jsonEmployeeArray;
   for(int i = 0; i < employees.size(); i++){
      json jsonEmployee;
      jsonEmployee["id"]   = employees[i].getId();
      jsonEmployee["name"] = employees[i].getName();
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
   json jsonManufacturerArray;
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
   json jsonStatusArray;
   for(int i = 0; i < statuses.size(); i++){
      json jsonStatus;
      jsonStatus["id"]   = statuses[i].getId();
      jsonStatus["name"] = statuses[i].getName();
      jsonStatusArray.push_back(jsonStatus);
   }
   return jsonStatusArray;
}






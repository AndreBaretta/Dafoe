#include "Test.hpp"


Test::Test(){}
Test::~Test(){}

bool Test::assertInt(int answer, int method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

bool Test::assertTrue(bool method){
   if(!method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return method;
}

bool Test::assertFalse(bool method){
   if(method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return !method;
}

bool Test::assertDouble(double answer, double method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

bool Test::assertString(std::string answer, std::string method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

bool Test::assertChar(char answer, char method){
   if(answer != method){
      this->m_errorCounter++;
      this->m_errorCommands[m_errorCommands.size()] = this->m_commandCounter;
   }
   this->m_commandCounter++;
   return answer == method;
}

HTTPRequest Test::testCreateProduct(const std::string& name, const int genericProduct, const int manufacturer,
                                    const std::string& barcode, const double price, const double cost,
                                    const std::string& reference, const int quantity){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   
   json jsonbody;
   jsonbody["name"] = name;
   jsonbody["genericProduct"] = genericProduct;
   jsonbody["manufacturer"] = manufacturer;
   jsonbody["barcode"] = barcode;
   jsonbody["price"] = price;
   jsonbody["cost"] = cost;
   jsonbody["reference"] = reference;
   jsonbody["quantity"] = quantity;
   std::string body = jsonbody.dump();

   HTTPRequest request = HTTPRequest();
   request.setMethod("POST");
   request.setPath(path);
   request.setBody(body);
   request.setVersion("HTTP/1.1");
   
   return request;
}

HTTPRequest Test::testDeleteProduct(const int id){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   path[2] = std::to_string(id);

   HTTPRequest request = HTTPRequest();
   request.setMethod("DELETE");
   request.setPath(path);
   request.setVersion("HTTP/1.1");
   
   return request;
}

HTTPRequest Test::testUpdateProduct(const int id, const std::string& name, const int genericProduct,
                                    const int manufacturer, const std::string& barcode, const double price,
                                    const double cost, const std::string& reference, const int quantity){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   path[2] = std::to_string(id);

   HTTPRequest request = HTTPRequest();
   request.setMethod("PUT");
   request.setPath(path);
   request.setVersion("HTTP/1.1");

   return request;
}

HTTPRequest Test::testRetrieveProductById(const int id){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   path[2] = std::to_string(id);

   HTTPRequest request = HTTPRequest();
   request.setMethod("GET");
   request.setPath(path);
   request.setVersion("HTTP/1.1");

   return request;
}

HTTPRequest Test::testQueryProductByName(const std::string& name){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   
   HTTPRequest request = HTTPRequest();
   request.setPath(path);
   request.setMethod("GET");
   request.setQuery("name=" + name);
   request.setVersion("HTTP/1.1");

   return request;
}

HTTPRequest Test::testRetrieveProductByReference(const std::string& reference){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   
   HTTPRequest request = HTTPRequest();
   request.setPath(path);
   request.setMethod("GET");
   request.setQuery("reference=" + reference);
   request.setVersion("HTTP/1.1");

   return request;
}

HTTPRequest Test::testRetrieveProductByBarcode(const std::string& barcode){
   std::vector<std::string> path;
   path[0] = "api";
   path[1] = "product";
   
   HTTPRequest request = HTTPRequest();
   request.setPath(path);
   request.setMethod("GET");
   request.setQuery("barcode=" + barcode);
   request.setVersion("HTTP/1.1");

   return request;
}






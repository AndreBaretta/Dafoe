#include "HTTPRequestHandler.hpp"
#include <iostream>

HTTPRequestHandler::HTTPRequestHandler(HTTPResponseBuilder& responseBuilder, ProductMNG& productMNG, CategoryMNG& categoryMNG)
: m_productMNG{productMNG}
, m_categoryMNG{categoryMNG}
, m_responseBuilder{responseBuilder}
{}

HTTPRequestHandler::~HTTPRequestHandler(){}

std::string HTTPRequestHandler::handleRequest(HTTPRequest& request){
   std::string responseBody{};
   std::string version{"HTTP/1.1"};
   std::string statusCode{};
   std::string statusMessage{};
   std::string stringResponse{};
   std::map<std::string,std::string> headers{};

   std::string method = request.getMethod();
   std::vector<std::string> path = request.getPath();
   std::string query = request.getQuery();
   std::string requestBody = request.getBody();

   // Lidando com o metodo GET
   if(method == "GET"){
      // Product
      if(path.size() == 2 && path[0] == "api" && path[1] == "product"){
	 if(query.empty()) {
	    responseBody = handleRetrieveAllProduct();
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 }else if (query.find("name=") == 0) {
	    std::string name = query.substr(5);
	    responseBody = handleQueryProductByName(name);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 }else if (query.find("reference=") == 0) {
	    std::string reference = query.substr(10);
	    responseBody = handleRetrieveProductByReference(reference);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 }else if (query.find("barcode=") == 0) {
	    std::string barcode = query.substr(8);
	    responseBody = handleRetrieveProductByBarcode(barcode);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
      }

      if(path.size() == 3 && path[0] == "api" && path[1] == "product"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrieveProductById(temp);
	 headers["Content-Type"] = "application/json";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      // Category
      if(path.size() == 2 && path[0] == "api" && path[1] == "category"){
	 responseBody = handleRetrieveAllCategory();
	 headers["Content-Type"] = "application/json";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path.size() == 3 && path[0] == "api" && path[1] == "category"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrieveCategory(temp);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      statusCode = "404";
      statusMessage = "Not Found";
      HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
      stringResponse = this->m_responseBuilder.buildResponseString(response);
      return stringResponse;
   }

   if(method == "POST"){
      /*if(!headers.contains("Content-Length")){
	 statusCode = "411";
	 statusMessage = "Length Required";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }*/
      if(path.size() != 2){
	 statusCode = "400";
	 statusMessage = "Bad Request";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[0] != "api"){
	 statusCode = "404";
	 statusMessage = "Not Found";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "product"){
	 handleCreateProduct(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "category"){
	 handleCreateCategory(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      statusCode = "404";
      statusMessage = "Not Found";
      HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
      stringResponse = this->m_responseBuilder.buildResponseString(response);
      return stringResponse;
   }else if(method == "DELETE"){
      if(path.size() != 3){
	 statusCode = "400";
	 statusMessage = "Bad Request";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[0] != "api"){
	 statusCode = "404";
	 statusMessage = "Not Found";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(!isNumber(path[2])){
	 statusCode = "404";
	 statusMessage = "Not Found";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "product"){
	 int id = std::stoi(path[2]);
	 handleDeleteProduct(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "category"){
	 int id = std::stoi(path[2]);
	 handleDeleteCategory(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      statusCode = "404";
      statusMessage = "Not Found";
      HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
      stringResponse = this->m_responseBuilder.buildResponseString(response);
      return stringResponse;
   }else if(method == "PUT"){
      if(path.size() != 3){
	 statusCode = "400";
	 statusMessage = "Bad Request";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[0] != "api"){
	 statusCode = "404";
	 statusMessage = "Not Found";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(!isNumber(path[2])){
	 statusCode = "404";
	 statusMessage = "Not Found";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "product"){
	 int id = std::stoi(path[2]);
	 handleUpdateProduct(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "category"){
	 int id = std::stoi(path[2]);
	 handleUpdateCategory(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      statusCode = "404";
      statusMessage = "Not Found";
      HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
      stringResponse = this->m_responseBuilder.buildResponseString(response);
      return stringResponse;
   }

   statusCode = "400";
   statusMessage = "Bad Request";
   HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
   stringResponse = this->m_responseBuilder.buildResponseString(response);
   return stringResponse;
}

std::string HTTPRequestHandler::handleRetrieveAllProduct(){
   std::string response = this->m_productMNG.retrieveAll().dump();
   return response;
}

std::string HTTPRequestHandler::handleQueryProductByName(const std::string& name){
   std::string response = this->m_productMNG.queryProductByName(name).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveProductByReference(const std::string& reference){
   std::string response = this->m_productMNG.retrieveProductByReference(reference).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveProductByBarcode(const std::string& barcode){
   std::string response = this->m_productMNG.retrieveProductByBarCode(barcode).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveProductById(const int id){
   std::string response = this->m_productMNG.retrieveProductByID(id).dump();
   return response; 
}

std::string HTTPRequestHandler::handleRetrieveAllCategory(){
   std::string response = this->m_categoryMNG.retrieveAllCategories().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveCategory(const int id){
   std::string response = this->m_categoryMNG.retrieveCategory(id).dump();
   return response;
}

bool HTTPRequestHandler::handleCreateProduct(const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   int genericProduct = json["genericProduct"];
   int manufacturer = json["manufacturer"];
   std::string barcode = json["barcode"];
   double price = json["price"];
   double cost = json["cost"];
   std::string reference = json["reference"];
   int quantity = json["quantity"];
   bool response = this->m_productMNG.createProduct(name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);
   return response;
};

bool HTTPRequestHandler::handleUpdateProduct(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   int genericProduct = json["genericProduct"];
   int manufacturer = json["manufacturer"];
   std::string barcode = json["barcode"];
   double price = json["price"];
   double cost = json["cost"];
   std::string reference = json["reference"];
   int quantity = json["quantity"];
   bool response = this->m_productMNG.updateProduct(id,name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);
   return response;
}

bool HTTPRequestHandler::handleCreateCategory(const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   bool response = this->m_categoryMNG.createCategory(name);
   return response;
}

bool HTTPRequestHandler::handleUpdateCategory(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   bool response = this->m_categoryMNG.updateCategory(id,name);
   return response;
}

bool HTTPRequestHandler::isNumber(const std::string& string){
   for(int i = 0; i < string.size(); i++){
      if(!std::isdigit(string[i])){
	 return false;
      }
   }
   return true;
}

bool HTTPRequestHandler::handleDeleteProduct(const int id){
   bool response = this->m_productMNG.deleteProduct(id);
   return response;
}

bool HTTPRequestHandler::handleDeleteCategory(const int id){
   bool response = this->m_categoryMNG.deleteCategory(id);
   return response;
}






#include "HTTPRequestHandler.hpp"
#include <iostream>
#include <string>

HTTPRequestHandler::HTTPRequestHandler(HTTPResponseBuilder& responseBuilder, ProductMNG& productMNG, CategoryMNG& categoryMNG, PaymentMethodMNG& paymentMethodMNG,
				       ClientMNG& clientMNG, EmployeeMNG& employeeMNG, ManufacturerMNG& manufacturerMNG, SellOrderMNG& sellOrderMNG,
				       StatusMNG& statusMNG, GenericProductMNG& genericProductMNG, UserMNG& userMNG)
: m_productMNG{productMNG}
, m_categoryMNG{categoryMNG}
, m_paymentMethodMNG{paymentMethodMNG}
, m_clientMNG{clientMNG}
, m_employeeMNG{employeeMNG}
, m_manufacturerMNG{manufacturerMNG}
, m_sellOrderMNG{sellOrderMNG}
, m_statusMNG{statusMNG}
, m_genericProductMNG{genericProductMNG}
, m_userMNG{userMNG}
, m_responseBuilder{responseBuilder}
{}

HTTPRequestHandler::~HTTPRequestHandler(){}

std::string HTTPRequestHandler::handleRequest(HTTPRequest& request){
   std::string responseBody{};
   std::string version{"HTTP/1.1"};
   std::string stringResponse{};
   std::map<std::string,std::string> headers{};

   headers["Access-Control-Allow-Origin"] = "*";
   std::string method = request.getMethod();
   std::vector<std::string> path = request.getPath();
   std::string query = request.getQuery();
   std::string requestBody = request.getBody();
   std::map<std::string, std::string> requestHeaders = request.getHeaders();

   // Lidando com o metodo GET
   if(method == "GET"){
      // Product
      if(path.size() == 2){
	 if(path[0].compare("api"))
	    return return404(version,headers,responseBody);
	 if(!path[1].compare("product")){
	    if(query.empty()) {
	       responseBody = handleRetrieveAllProduct();
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("name=") == 0) {
	       std::string name = query.substr(5);
	       responseBody = handleQueryProductByName(name);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("reference=") == 0) {
	       std::string reference = query.substr(10);
	       responseBody = handleRetrieveProductByReference(reference);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("barcode=") == 0) {
	       std::string barcode = query.substr(8);
	       responseBody = handleRetrieveProductByBarcode(barcode);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("category")){
	    if(query.empty()){
	       responseBody = handleRetrieveAllCategory();
	       headers["Content-Type"] = "application/json";
	       return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("payment-method")){
	    if(query.empty()){
	       responseBody = handleRetrieveAllPaymentMethod();
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("client")){
	    if(query.empty()) {
	       responseBody = handleRetrieveAllClient();
	       headers["Content-Type"] = "application/json";
	       return return200(version, headers, responseBody);
	    }else if (query.find("name=") == 0) {
	       std::string name = query.substr(5);
	       responseBody = handleRetrieveClientByName(name);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("employee")){
	    if(query.empty()){
	       responseBody = handleRetrieveAllEmployee();
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("name=") == 0) {
	       std::string name = query.substr(5);
	       responseBody = handleRetrieveEmployeeByName(name);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("manufacturer")){
	    if(query.empty()){
	       responseBody = handleRetrieveAllManufacturer();
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("name=") == 0) {
	       std::string name = query.substr(5);
	       responseBody = handleRetrieveManufacturerByName(name);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("order")){
	    if(query.empty()){
	       responseBody = handleRetrieveAllOrder();
	       headers["Content-Type"] = "application/json"; 
	       return return200(version,headers,responseBody);
	    }else if (query.find("client=") == 0) {
	       if(!isNumber(query.substr(7))){
		  return return400(version,headers,responseBody);
	       }
	       int clientId = std::stoi(query.substr(7));
	       responseBody = handleRetrieveOrderByClient(clientId);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("product=") == 0) {
	       if(!isNumber(query.substr(8))){
		  return return400(version,headers,responseBody);
	       }
	       int productId = std::stoi(query.substr(8));
	       responseBody = handleRetrieveOrderByProduct(productId);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("seller=") == 0) {
	       if(!isNumber(query.substr(7))){
		  return return400(version,headers,responseBody);
	       }
	       int sellerId = std::stoi(query.substr(7));
	       responseBody = handleRetrieveOrderBySeller(sellerId);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }else if (query.find("status=") == 0) {
	       if(!isNumber(query.substr(7))){
		  return return400(version,headers,responseBody);
	       }
	       int statusId = std::stoi(query.substr(7));
	       responseBody = handleRetrieveOrderByStatus(statusId);
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return400(version,headers,responseBody);
	 }
	 if(!path[1].compare("status")){
	    if(query.empty()){
	       responseBody = handleRetrieveAllStatus();
	       headers["Content-Type"] = "application/json";
	       return return200(version,headers,responseBody);
	    }
	    return return400(version,headers,responseBody);
	 }
      }
      if(path.size() == 3){
	 if(path[0].compare("api"))
	    return404(version,headers,responseBody);
	 if(!isNumber(path[2]))
	    return400(version,headers,responseBody);
	 if(!path[1].compare("product")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveProductById(temp);
	    headers["Content-Type"] = "application/json";
	    return200(version,headers,responseBody);
	 }
	 if(!path[1].compare("category")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveCategory(temp);
	    return return200(version,headers,responseBody);
	 }
	 if(!path[1].compare("payment-method")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrievePaymentMethod(temp);
	    headers["Content-Type"] = "application/json";
	    return return200(version, headers, responseBody);
	 }
	 if(!path[1].compare("client")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveClient(temp);
	    headers["Content-Type"] = "application/json";
	    return return200(version,headers,responseBody);
	 }
	 if(!path[1].compare("employee")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveEmployee(temp);
	    headers["Content-Type"] = "application/json";
	    return return200(version,headers,responseBody);
	 }
	 if(!path[1].compare("manufacturer")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveEmployee(temp);
	    headers["Content-Type"] = "application/json";
	    return return200(version,headers,responseBody);
	 }
	 if(!path[1].compare("order")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveOrder(temp);
	    headers["Content-Type"] = "application/json";
	    return return200(version,headers,responseBody);
	 }
	 if(!path[1].compare("status")){
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveStatus(temp);
	    headers["Content-Type"] = "application/json";
	    return return200(version,headers,responseBody);
	 }
      }
   }

   if(method == "POST"){
      if(!requestHeaders.contains("Content-Length")){
	 return return411(version,headers,responseBody);
      }
      if(path.size() != 2)
	 return return400(version,headers,responseBody);
      if(path[0] != "api")
	 return return404(version,headers,responseBody);
      if(path[1] == "product"){
	 handleCreateProduct(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "category"){
	 handleCreateCategory(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "payment-method"){
	 handleCreatePaymentMethod(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "client"){
	 handleCreateClient(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "employee"){
	 handleCreateEmployee(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "manufacturer"){
	 handleCreateManufacturer(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "order"){
	 handleCreateOrder(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "status"){
	 handleCreateStatus(requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "generic-product"){
	 handleCreateGenericProduct(requestBody);
	 return return204(version,headers,responseBody);
      }
      /*if(path[1] == "login"){
	 handle
      }*/
      return return404(version,headers,responseBody);
   }else if(method == "DELETE"){
      if(path.size() != 3)
	 return return400(version,headers,responseBody);
      if(path[0] != "api")
	 return return404(version,headers,responseBody);
      if(!isNumber(path[2]))
	 return return404(version,headers,responseBody);
      if(path[1] == "product"){
	 int id = std::stoi(path[2]);
	 handleDeleteProduct(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "category"){
	 int id = std::stoi(path[2]);
	 handleDeleteCategory(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "payment-method"){
	 int id = std::stoi(path[2]);
	 handleDeletePaymentMethod(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "client"){
	 int id = std::stoi(path[2]);
	 handleDeleteClient(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "employee"){
	 int id = std::stoi(path[2]);
	 handleDeleteEmployee(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "manufacturer"){
	 int id = std::stoi(path[2]);
	 handleDeleteManufacturer(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "status"){
	 int id = std::stoi(path[2]);
	 handleDeleteStatus(id);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "generic-product"){
	 int id = std::stoi(path[2]);
	 handleDeleteGenericProduct(id);
	 return return204(version,headers,responseBody);
      }
      return return404(version,headers,responseBody);
   }else if(method == "PUT"){
      if(!requestHeaders.contains("Content-Length")){
	 return return411(version,headers,responseBody);
      }
      if(path.size() != 3)
	 return return400(version,headers,responseBody);
      if(path[0] != "api")
	 return return404(version,headers,responseBody);
      if(!isNumber(path[2]))
	 return return400(version,headers,responseBody);
      if(path[1] == "product"){
	 int id = std::stoi(path[2]);
	 handleUpdateProduct(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "category"){
	 int id = std::stoi(path[2]);
	 handleUpdateCategory(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "payment-method"){
	 int id = std::stoi(path[2]);
	 handleUpdatePaymentMethod(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "client"){
	 int id = std::stoi(path[2]);
	 handleUpdateClient(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "employee"){
	 int id = std::stoi(path[2]);
	 handleUpdateEmployee(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "manufacturer"){
	 int id = std::stoi(path[2]);
	 handleUpdateManufacturer(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "order"){
	 int id = std::stoi(path[2]);
	 handleUpdateOrder(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "status"){
	 int id = std::stoi(path[2]);
	 handleUpdateStatus(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      if(path[1] == "generic-product"){
	 int id = std::stoi(path[2]);
	 handleUpdateGenericProduct(id,requestBody);
	 return return204(version,headers,responseBody);
      }
      return return404(version,headers,responseBody);
   }
   return return400(version,headers,responseBody);
}

std::string HTTPRequestHandler::return200(const std::string& version, const std::map<std::string, std::string> headers, const std::string& body){
   std::string statusCode = "200";
   std::string statusMessage = "OK";
   HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, body);
   std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
   return stringResponse;  
}

std::string HTTPRequestHandler::return204(const std::string& version, const std::map<std::string, std::string> headers, const std::string& body){
   std::string statusCode = "204";
   std::string statusMessage = "No Content";
   HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, body);
   std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
   return stringResponse;  
}

std::string HTTPRequestHandler::return400(const std::string& version, const std::map<std::string, std::string> headers, const std::string& body){
   std::string statusCode = "400";
   std::string statusMessage = "Bad Request";
   HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, body);
   std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
   return stringResponse;  
}

std::string HTTPRequestHandler::return404(const std::string& version, const std::map<std::string, std::string> headers, const std::string& body){
   std::string statusCode = "404";
   std::string statusMessage = "Not Found";
   HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, body);
   std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
   return stringResponse;  
}

std::string HTTPRequestHandler::return411(const std::string& version, const std::map<std::string, std::string> headers, const std::string& body){
   std::string statusCode = "411";
   std::string statusMessage = "Length Required";
   HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, body);
   std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
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
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      int genericProduct = std::stoi(json["genericProduct"].get<std::string>());
      int manufacturer = std::stoi(json["manufacturer"].get<std::string>());
      std::string barcode = json["barcode"].get<std::string>();
      double price = std::stod(json["price"].get<std::string>());
      double cost = std::stod(json["cost"].get<std::string>());
      std::string reference = json["reference"].get<std::string>();
      int quantity = std::stoi(json["quantity"].get<std::string>());
      bool response = this->m_productMNG.createProduct(name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);
      return response;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
};

bool HTTPRequestHandler::handleUpdateProduct(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      int genericProduct = std::stoi(json["genericProduct"].get<std::string>());
      int manufacturer = std::stoi(json["manufacturer"].get<std::string>());
      std::string barcode = json["barcode"].get<std::string>();
      double price = std::stod(json["price"].get<std::string>());
      double cost = std::stod(json["cost"].get<std::string>());
      std::string reference = json["reference"].get<std::string>();
      int quantity = std::stoi(json["quantity"].get<std::string>());
      bool response = this->m_productMNG.updateProduct(id,name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);
      return response;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleCreateCategory(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      bool response = this->m_categoryMNG.createCategory(name);
      return response;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateCategory(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      bool response = this->m_categoryMNG.updateCategory(id,name);
      return response;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
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

bool HTTPRequestHandler::handleDeletePaymentMethod(const int id){
   bool response = this->m_paymentMethodMNG.deletePaymentMethod(id);
   return response;
}

bool HTTPRequestHandler::handleCreatePaymentMethod(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      bool response = this->m_paymentMethodMNG.createPaymentMethod(name);
      return response;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdatePaymentMethod(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      bool response = this->m_paymentMethodMNG.updatePaymentMethod(id,name);
      return response;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

std::string HTTPRequestHandler::handleRetrieveAllPaymentMethod(){
   std::string response = this->m_paymentMethodMNG.retrieveAllPaymentMethod().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrievePaymentMethod(const int id){
   std::string response = this->m_paymentMethodMNG.retrievePaymentMethod(id).dump();
   return response;
}

bool HTTPRequestHandler::handleCreateClient(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	   = json["name"].get<std::string>();
      std::string phoneNumber = json["phoneNumber"].get<std::string>();
      std::string address	   = json["address"].get<std::string>();
      double bill		   = std::stod(json["bill"].get<std::string>());
      return this->m_clientMNG.createClient(name,phoneNumber,address,bill);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateClient(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	   = json["name"].get<std::string>();
      std::string phoneNumber = json["phoneNumber"].get<std::string>();
      std::string address	   = json["address"].get<std::string>();
      double bill		   = std::stod(json["bill"].get<std::string>());
      return this->m_clientMNG.updateClient(id,name,phoneNumber,address,bill);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleDeleteClient(const int id){
   return this->m_clientMNG.deleteClient(id);
}

bool HTTPRequestHandler::handleCreateEmployee(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	   = json["name"].get<std::string>();
      std::string cargo       = json["cargo"].get<std::string>();
      return this->m_employeeMNG.createEmployee(name,cargo);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateEmployee(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	   = json["name"].get<std::string>();
      std::string cargo       = json["cargo"].get<std::string>();
      return this->m_employeeMNG.updateEmployee(id,name,cargo);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleDeleteEmployee(const int id){
   return this->m_employeeMNG.deleteEmployee(id);
}

bool HTTPRequestHandler::handleCreateManufacturer(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	   = json["name"].get<std::string>();
      return this->m_manufacturerMNG.createManufacturer(name);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateManufacturer(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	   = json["name"].get<std::string>();
      return this->m_manufacturerMNG.updateManufacturer(id,name);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleDeleteManufacturer(const int id){
   return this->m_manufacturerMNG.deleteManufacturer(id);
}

bool HTTPRequestHandler::handleCreateOrder(const std::string& body){
   try{
      json json = json::parse(body);
      int clientId		= std::stoi(json["clientId"].get<std::string>());
      int sellerId		= std::stoi(json["sellerId"].get<std::string>());
      int deliveredBy	= std::stoi(json["deliveredBy"].get<std::string>());
      int statusId		= std::stoi(json["statusId"].get<std::string>());
      int paymentMethod	= std::stoi(json["paymentMethod"].get<std::string>());
      std::string date     = json["date"].get<std::string>();
      double price   	= std::stod(json["price"].get<std::string>());
      return this->m_sellOrderMNG.createOrder(clientId,sellerId,deliveredBy,statusId,paymentMethod,date,price);
   }catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateOrder(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      int clientId		= std::stoi(json["clientId"].get<std::string>());
      int sellerId		= std::stoi(json["sellerId"].get<std::string>());
      int deliveredBy	= std::stoi(json["deliveredBy"].get<std::string>());
      int statusId		= std::stoi(json["statusId"].get<std::string>());
      int paymentMethod	= std::stoi(json["paymentMethod"].get<std::string>());
      std::string date     = json["date"].get<std::string>();
      double price   	= std::stod(json["price"].get<std::string>());
      return this->m_sellOrderMNG.updateOrder(id, clientId,sellerId,deliveredBy,statusId,paymentMethod,date,price);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleCreateStatus(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      return this->m_statusMNG.createStatus(name);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateStatus(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name = json["name"].get<std::string>();
      return this->m_statusMNG.updateStatus(id, name);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleDeleteStatus(const int id){
   return this->m_statusMNG.deleteStatus(id);
}

bool HTTPRequestHandler::handleCreateGenericProduct(const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	 = json["name"].get<std::string>();
      int quantity		 = std::stoi(json["quantity"].get<std::string>());
      int category		 = std::stoi(json["category"].get<std::string>());
      std::string reference = json["reference"].get<std::string>();
      return this->m_genericProductMNG.createGenericProduct(name,quantity,category,reference);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleUpdateGenericProduct(const int id, const std::string& body){
   try{
      json json = json::parse(body);
      std::string name	 = json["name"].get<std::string>();
      int quantity		 = std::stoi(json["quantity"].get<std::string>());
      int category		 = std::stoi(json["category"].get<std::string>());
      std::string reference = json["reference"].get<std::string>();
      return this->m_genericProductMNG.updateGenericProduct(id, name,quantity,category,reference);
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool HTTPRequestHandler::handleDeleteGenericProduct(const int id){
   return this->m_genericProductMNG.deleteGenericProduct(id);
}

std::string HTTPRequestHandler::handleRetrieveAllClient(){
   std::string response = this->m_clientMNG.retrieveAllClient().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveClient(const int id){
   std::string response = this->m_clientMNG.retrieveClient(id).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveClientByName(const std::string& name){
   std::string response = this->m_clientMNG.retrieveClientByName(name).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveEmployeeByName(const std::string& name){
   std::string response = this->m_employeeMNG.retrieveEmployeeByName(name).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveEmployee(const int id){
   std::string response = this->m_employeeMNG.retrieveEmployee(id).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveAllEmployee(){
   std::string response = this->m_employeeMNG.retrieveAllEmployee().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveAllManufacturer(){
   std::string response = this->m_manufacturerMNG.retrieveAllManufacturer().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveManufacturer(const int id){
   std::string response = this->m_manufacturerMNG.retrieveManufacturer(id).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveManufacturerByName(const std::string& name){
   std::string response = this->m_manufacturerMNG.retrieveManufacturerByName(name).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveOrder(const int id){
   std::string response = this->m_sellOrderMNG.retrieveOrder(id).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveOrderByClient(const int clientId){
   std::string response = this->m_sellOrderMNG.retrieveOrderByClient(clientId).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveOrderByProduct(const int productId){
   std::string response = this->m_sellOrderMNG.retrieveOrderByProduct(productId).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveOrderBySeller(const int sellerId){
   std::string response = this->m_sellOrderMNG.retrieveOrderBySeller(sellerId).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveOrderByStatus(const int statusId){
   std::string response = this->m_sellOrderMNG.retrieveOrderByStatus(statusId).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveAllOrder(){
   std::string response = this->m_sellOrderMNG.retrieveAllSellOrder().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveAllStatus(){
   std::string response = this->m_statusMNG.retrieveAllStatus().dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveStatus(const int id){
   std::string response = this->m_statusMNG.retrieveStatus(id).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveGenericProductByName(const std::string& name){
   std::string response = this->m_genericProductMNG.retrieveGenericProductByName(name);
   return response;
}

std::string HTTPRequestHandler::handleLogin(const int id, const std::string& password){
   //s
   std::string response = "a";
   //std::string response = this->m_userMNG.
   return response;
}


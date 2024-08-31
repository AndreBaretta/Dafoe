#include "HTTPRequestHandler.hpp"
#include <iostream>

HTTPRequestHandler::HTTPRequestHandler(HTTPResponseBuilder& responseBuilder, ProductMNG& productMNG, CategoryMNG& categoryMNG, PaymentMethodMNG& paymentMethodMNG,
				       ClientMNG& clientMNG, EmployeeMNG& employeeMNG, ManufacturerMNG& manufacturerMNG, SellOrderMNG& sellOrderMNG,
				       StatusMNG& statusMNG, GenericProductMNG& genericProductMNG)
: m_productMNG{productMNG}
, m_categoryMNG{categoryMNG}
, m_paymentMethodMNG{paymentMethodMNG}
, m_clientMNG{clientMNG}
, m_employeeMNG{employeeMNG}
, m_manufacturerMNG{manufacturerMNG}
, m_sellOrderMNG{sellOrderMNG}
, m_statusMNG{statusMNG}
, m_genericProductMNG{genericProductMNG}
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

      // PaymentMethod
      if(path.size() == 2 && path[0] == "api" && path[1] == "payment-method"){
	 responseBody = handleRetrieveAllPaymentMethod();
	 headers["Content-Type"] = "application/json";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      if(path.size() == 3 && path[0] == "api" && path[1] == "payment-method"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrievePaymentMethod(temp);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      // PaymentMethod
      if(path.size() == 2 && path[0] == "api" && path[1] == "client"){
	 if(query.empty()) {
	    responseBody = handleRetrieveAllClient();
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 }else if (query.find("name=") == 0) {
	    std::string name = query.substr(5);
	    responseBody = handleRetrieveClientByName(name);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
      }

      if(path.size() == 3 && path[0] == "api" && path[1] == "client"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrieveClient(temp);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      // Employee
      if(path.size() == 2 && path[0] == "api" && path[1] == "employee"){
	 if(query.empty()){
	    responseBody = handleRetrieveAllEmployee();
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }else if (query.find("name=") == 0) {
	    std::string name = query.substr(5);
	    responseBody = handleRetrieveEmployeeByName(name);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
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

      if(path.size() == 3 && path[0] == "api" && path[1] == "employee"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrieveEmployee(temp);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      // Manufacturer
      if(path.size() == 2 && path[0] == "api" && path[1] == "manufacturer"){
	 if(query.empty()){
	    responseBody = handleRetrieveAllManufacturer();
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }else if (query.find("name=") == 0) {
	    std::string name = query.substr(5);
	    responseBody = handleRetrieveManufacturerByName(name);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
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

      if(path.size() == 3 && path[0] == "api" && path[1] == "manufacturer"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrieveEmployee(temp);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }

      // Order
      if(path.size() == 2 && path[0] == "api" && path[1] == "order"){
	 if(query.empty()){
	    responseBody = handleRetrieveAllOrder();
	    headers["Content-Type"] = "application/json"; 
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }else if (query.find("client=") == 0) {
	    if(!isNumber(query.substr(7))){
	       statusCode = "400";
	       statusMessage = "Bad Request";
	       HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	       stringResponse = this->m_responseBuilder.buildResponseString(response);
	       return stringResponse;
	    }
	    int clientId = std::stoi(query.substr(7));
	    responseBody = handleRetrieveOrderByClient(clientId);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }else if (query.find("product=") == 0) {
	    if(!isNumber(query.substr(8))){
	       statusCode = "400";
	       statusMessage = "Bad Request";
	       HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	       stringResponse = this->m_responseBuilder.buildResponseString(response);
	       return stringResponse;
	    }
	    int productId = std::stoi(query.substr(8));
	    responseBody = handleRetrieveOrderByProduct(productId);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }else if (query.find("seller=") == 0) {
	    if(!isNumber(query.substr(7))){
	       statusCode = "400";
	       statusMessage = "Bad Request";
	       HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	       stringResponse = this->m_responseBuilder.buildResponseString(response);
	       return stringResponse;
	    }
	    int sellerId = std::stoi(query.substr(7));
	    responseBody = handleRetrieveOrderBySeller(sellerId);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }else if (query.find("status=") == 0) {
	    if(!isNumber(query.substr(7))){
	       statusCode = "400";
	       statusMessage = "Bad Request";
	       HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	       stringResponse = this->m_responseBuilder.buildResponseString(response);
	       return stringResponse;
	    }
	    int statusId = std::stoi(query.substr(7));
	    responseBody = handleRetrieveOrderByStatus(statusId);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }

	 // Status
	 if(path.size() == 2 && path[0] == "api" && path[1] == "status"){
	    if(query.empty()){
	       responseBody = handleRetrieveAllStatus();
	       headers["Content-Type"] = "application/json";
	       statusCode = "200";
	       statusMessage = "OK";
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

	 if(path.size() == 3 && path[0] == "api" && path[1] == "status"){
	    if(!isNumber(path[2])){
	       statusCode = "400";
	       statusMessage = "Bad Request";
	       HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	       stringResponse = this->m_responseBuilder.buildResponseString(response);
	       return stringResponse;
	    }
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveStatus(temp);
	    statusCode = "200";
	    statusMessage = "OK";
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

      if(path.size() == 3 && path[0] == "api" && path[1] == "order"){
	 if(!isNumber(path[2])){
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 int temp = std::stoi(path[2]);
	 responseBody = handleRetrieveOrder(temp);
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
      if(path[1] == "payment-method"){
	 handleCreatePaymentMethod(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "client"){
	 handleCreateClient(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "employee"){
	 handleCreateEmployee(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "manufacturer"){
	 handleCreateManufacturer(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "order"){
	 handleCreateOrder(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "status"){
	 handleCreateStatus(requestBody);
	 statusCode = "204";
	 statusMessage = "No Content";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "generic-product"){
	 handleCreateGenericProduct(requestBody);
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
      if(path[1] == "payment-method"){
	 int id = std::stoi(path[2]);
	 handleDeletePaymentMethod(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "client"){
	 int id = std::stoi(path[2]);
	 handleDeleteClient(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "employee"){
	 int id = std::stoi(path[2]);
	 handleDeleteEmployee(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "manufacturer"){
	 int id = std::stoi(path[2]);
	 handleDeleteManufacturer(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "status"){
	 int id = std::stoi(path[2]);
	 handleDeleteStatus(id);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "generic-product"){
	 int id = std::stoi(path[2]);
	 handleDeleteGenericProduct(id);
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
	 statusCode = "400";
	 statusMessage = "Bad Request";
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
      if(path[1] == "payment-method"){
	 int id = std::stoi(path[2]);
	 handleUpdatePaymentMethod(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "client"){
	 int id = std::stoi(path[2]);
	 handleUpdateClient(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "employee"){
	 int id = std::stoi(path[2]);
	 handleUpdateEmployee(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "manufacturer"){
	 int id = std::stoi(path[2]);
	 handleUpdateManufacturer(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "order"){
	 int id = std::stoi(path[2]);
	 handleUpdateOrder(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "status"){
	 int id = std::stoi(path[2]);
	 handleUpdateStatus(id,requestBody);
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
      if(path[1] == "generic-product"){
	 int id = std::stoi(path[2]);
	 handleUpdateGenericProduct(id,requestBody);
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

bool HTTPRequestHandler::handleDeletePaymentMethod(const int id){
   bool response = this->m_paymentMethodMNG.deletePaymentMethod(id);
   return response;
}

bool HTTPRequestHandler::handleCreatePaymentMethod(const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   bool response = this->m_paymentMethodMNG.createPaymentMethod(name);
   return response;
}

bool HTTPRequestHandler::handleUpdatePaymentMethod(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   bool response = this->m_paymentMethodMNG.updatePaymentMethod(id,name);
   return response;
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
   json json = json::parse(body);
   std::string name	   = json["name"];
   std::string phoneNumber = json["phoneNumber"];
   std::string address	   = json["address"];
   double bill		   = json["bill"];
   return this->m_clientMNG.createClient(name,phoneNumber,address,bill);
}

bool HTTPRequestHandler::handleUpdateClient(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name	   = json["name"];
   std::string phoneNumber = json["phoneNumber"];
   std::string address	   = json["address"];
   double bill		   = json["bill"];
   return this->m_clientMNG.updateClient(id,name,phoneNumber,address,bill);
}

bool HTTPRequestHandler::handleDeleteClient(const int id){
   return this->m_clientMNG.deleteClient(id);
}

bool HTTPRequestHandler::handleCreateEmployee(const std::string& body){
   json json = json::parse(body);
   std::string name	   = json["name"];
   std::string cargo       = json["cargo"];
   return this->m_employeeMNG.createEmployee(name,cargo);
}

bool HTTPRequestHandler::handleUpdateEmployee(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name	   = json["name"];
   std::string cargo       = json["cargo"];
   return this->m_employeeMNG.updateEmployee(id,name,cargo);
}

bool HTTPRequestHandler::handleDeleteEmployee(const int id){
   return this->m_employeeMNG.deleteEmployee(id);
}

bool HTTPRequestHandler::handleCreateManufacturer(const std::string& body){
   json json = json::parse(body);
   std::string name	   = json["name"];
   return this->m_manufacturerMNG.createManufacturer(name);
}

bool HTTPRequestHandler::handleUpdateManufacturer(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name	   = json["name"];
   return this->m_manufacturerMNG.updateManufacturer(id,name);
}

bool HTTPRequestHandler::handleDeleteManufacturer(const int id){
   return this->m_manufacturerMNG.deleteManufacturer(id);
}

bool HTTPRequestHandler::handleCreateOrder(const std::string& body){
   json json = json::parse(body);
   int clientId		= json["clientId"];
   int sellerId		= json["sellerId"];
   int deliveredBy	= json["deliveredBy"];
   int statusId		= json["statusId"];
   int paymentMethod	= json["paymentMethod"];
   std::string date     = json["date"];
   double price   	= json["price"];
   return this->m_sellOrderMNG.createOrder(clientId,sellerId,deliveredBy,statusId,paymentMethod,date,price);
}

bool HTTPRequestHandler::handleUpdateOrder(const int id, const std::string& body){
   json json = json::parse(body);
   int clientId		= json["clientId"];
   int sellerId		= json["sellerId"];
   int deliveredBy	= json["deliveredBy"];
   int statusId		= json["statusId"];
   int paymentMethod	= json["paymentMethod"];
   std::string date     = json["date"];
   double price   	= json["price"];
   return this->m_sellOrderMNG.updateOrder(id, clientId,sellerId,deliveredBy,statusId,paymentMethod,date,price);
}

bool HTTPRequestHandler::handleCreateStatus(const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   return this->m_statusMNG.createStatus(name);
}

bool HTTPRequestHandler::handleUpdateStatus(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name = json["name"];
   return this->m_statusMNG.updateStatus(id, name);
}

bool HTTPRequestHandler::handleDeleteStatus(const int id){
   return this->m_statusMNG.deleteStatus(id);
}

bool HTTPRequestHandler::handleCreateGenericProduct(const std::string& body){
   json json = json::parse(body);
   std::string name	 = json["name"];
   int quantity		 = json["quantity"];
   int category		 = json["category"];
   std::string reference = json["reference"];
   return this->m_genericProductMNG.createGenericProduct(name,quantity,category,reference);
}

bool HTTPRequestHandler::handleUpdateGenericProduct(const int id, const std::string& body){
   json json = json::parse(body);
   std::string name	 = json["name"];
   int quantity		 = json["quantity"];
   int category		 = json["category"];
   std::string reference = json["reference"];
   return this->m_genericProductMNG.updateGenericProduct(id, name,quantity,category,reference);
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



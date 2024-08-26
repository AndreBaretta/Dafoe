#include "HTTPRequestHandler.hpp"

HTTPRequestHandler::HTTPRequestHandler(ProductMNG& productMNG, HTTPResponseBuilder& responseBuilder)
: m_productMNG{productMNG}
, m_responseBuilder{responseBuilder}
{}

HTTPRequestHandler::~HTTPRequestHandler(){}

std::string HTTPRequestHandler::handleRequest(HTTPRequest& request){
   json responseBody{};
   std::string version{"HTTP/1.1"};
   std::string statusCode{};
   std::string statusMessage{};
   std::string stringResponse{};
   std::map<std::string,std::string> headers{};

   std::string method = request.getMethod();
   std::vector<std::string> path = request.getPath();
   std::string query = request.getQuery();
  
   // Lidando com o metodo GET
   if(method == "GET"){
      // Product
      if (path.size() == 2 && path[0] == "api" && path[1] == "product"){
	 if (query.empty()) {
	    responseBody = handleRetrieveAll();
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 } else if (query.find("name=") == 0) {
	    std::string name = query.substr(5);
	    responseBody = handleQueryProductByName(name);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 } else if (query.find("reference=") == 0) {
	    std::string reference = query.substr(10);
	    responseBody = handleRetrieveProductByReference(reference);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;

	 } else if (query.find("barcode=") == 0) {
	    std::string barcode = query.substr(8);
	    responseBody = handleRetrieveProductByBarcode(barcode);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
      }

      if (path.size() == 3 && path[0] == "api" && path[1] == "product"){
	 try
	 {
	    int temp = std::stoi(path[2]);
	    responseBody = handleRetrieveProductById(temp);
	    headers["Content-Type"] = "application/json";
	    statusCode = "200";
	    statusMessage = "OK";
	    HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
	 catch(std::invalid_argument const& exception)
	 {
	    statusCode = "400";
	    statusMessage = "Bad Request";
	    HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	    stringResponse = this->m_responseBuilder.buildResponseString(response);
	    return stringResponse;
	 }
      }

      statusCode = "404";
      statusMessage = "Not Found";
      HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
      stringResponse = this->m_responseBuilder.buildResponseString(response);
      return stringResponse;
   }
   if(method == "POST"){
      if(!headers.contains("Content-Length")){
	 statusCode = "411";
	 statusMessage = "Length Required";
	 HTTPResponse response = HTTPResponse(version, statusCode, statusMessage, headers, responseBody);
	 stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
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

std::string HTTPRequestHandler::handleRetrieveAll(){
   std::string response = this->m_productMNG.retrieveAll().dump();
   return response;
}

std::string HTTPRequestHandler::handleQueryProductByName(std::string& name){
   std::string response = this->m_productMNG.queryProductByName(name).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveProductByReference(std::string& reference){
   std::string response = this->m_productMNG.retrieveProductByReference(reference).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveProductByBarcode(std::string& barcode){
   std::string response = this->m_productMNG.retrieveProductByBarCode(barcode).dump();
   return response;
}

std::string HTTPRequestHandler::handleRetrieveProductById(int& id){
   std::string response = this->m_productMNG.retrieveProductByID(id).dump();
   return response; 
}



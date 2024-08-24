#include "HTTPRequestHandler.hpp"

HTTPRequestHandler::HTTPRequestHandler(ProductMNG& productMNG, HTTPResponseBuilder& responseBuilder)
: m_productMNG{productMNG}
, m_responseBuilder{responseBuilder}
{}

HTTPRequestHandler::~HTTPRequestHandler(){}

std::string HTTPRequestHandler::handleRequest(HTTPRequest& request){
   json responseBody;
   std::string version;
   std::string statusCode;
   std::string statusMessage;
   std::map<std::string,std::string> headers;

   std::vector<std::string> path = request.getPath();
   std::string query = request.getQuery();
   // Lidando com o path /api/product
   if (path.size() == 2 && path[0] == "api" && path[1] == "product"){
      if (query.empty()) {
	 responseBody = handleRetrieveAll();
	 version = "HTTP/1.1";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	 std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;

      } else if (query.find("name=") == 0) {
	 std::string name = query.substr(5);
	 responseBody = handleQueryProductByName(name);
	 version = "HTTP/1.1";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	 std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;

      } else if (query.find("reference=") == 0) {
	 std::string reference = query.substr(10);
	 responseBody = handleRetrieveProductByReference(reference);
	 version = "HTTP/1.1";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	 std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;

      } else if (query.find("barcode=") == 0) {
	 std::string barcode = query.substr(8);
	 responseBody = handleRetrieveProductByBarcode(barcode);
	 version = "HTTP/1.1";
	 statusCode = "200";
	 statusMessage = "OK";
	 HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
	 std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
	 return stringResponse;
      }
   }

   if (path.size() == 3 && path[0] == "api" && path[1] == "product"){
      int temp = std::stoi(path[2]);
      responseBody = handleRetrieveProductById(temp);
      version = "HTTP/1.1";
      statusCode = "200";
      statusMessage = "OK";
      HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
      std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
      return stringResponse;
   }


   responseBody = "Page not found.";
   version = "HTTP/1.1";
   statusCode = "404";
   statusMessage = "Not Found";
   headers["Content-Type"] = "text/plain";
   HTTPResponse response = HTTPResponse(version,statusCode,statusMessage,headers,responseBody);
   std::string stringResponse = this->m_responseBuilder.buildResponseString(response);
   return stringResponse;
}

std::string HTTPRequestHandler::handleRetrieveAll(){
   return this->m_productMNG.retrieveAll();
}

std::string HTTPRequestHandler::handleQueryProductByName(std::string& name){
   return this->m_productMNG.queryProductByName(name);
}

std::string HTTPRequestHandler::handleRetrieveProductByReference(std::string& reference){
   return this->m_productMNG.retrieveProductByReference(reference);
}

std::string HTTPRequestHandler::handleRetrieveProductByBarcode(std::string& barcode){
   return this->m_productMNG.retrieveProductByBarCode(barcode);
}

std::string HTTPRequestHandler::handleRetrieveProductById(int& id){
   std::string response = this->m_productMNG.retrieveProductByID(id).dump();
   return response; 
}



#include "HTTPRequestHandler.hpp"

HTTPRequestHandler::HTTPRequestHandler(ProductMNG& productMNG)
: m_productMNG{productMNG}
{}

HTTPRequestHandler::~HTTPRequestHandler(){}

std::string HTTPRequestHandler::handleRequest(HTTPRequest& request){
   std::vector<std::string> path = request.getPath();
   std::string query = request.getQuery();

   // Lidando com a rota /api/product
   if (path.size() == 2 && path[0] == "api" && path[1] == "product") {
      if (query.empty()) {
	 return handleRetrieveAll();
      } else if (query.find("name=") == 0) {
	 std::string name = query.substr(5);
	 return handleQueryProductByName(name);
      } else if (query.find("reference=") == 0) {
	 std::string reference = query.substr(10);
	 return handleRetrieveProductByReference(reference);
      } else if (query.find("barcode=") == 0) {
	 std::string barcode = query.substr(8);
	 return handleRetrieveProductByBarCode(barcode);
      }
   }

   if (path.size() == 3 && path[0] == "api" && path[1] == "product") {
      return handleRetrieveProductById(path[2]);
   }

   return handleNotFound();
}

std::string HTTPRequestHandler::handleRetrieveAll(){
   this->m_productMNG.retrieveAll();
}

std::string HTTPRequestHandler::handleQueryProductByName(std::string name){
   this->m_productMNG.queryProductByName(name);
}

std::string HTTPRequestHandler::handleRetrieveProductByReference(std::string reference){
   this->m_productMNG.retrieveProductByReference(reference);
}

std::string HTTPRequestHandler::handleRetrieveProductByBarCode(std::string barcode){
   this->m_productMNG.retrieveProductByBarCode(barcode);
}

std::string HTTPRequestHandler::handleNotFound() {
   return "HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nPage not found.";
}











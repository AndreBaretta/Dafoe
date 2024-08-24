#include "HTTPRequestHandler.hpp"

HTTPRequestHandler::HTTPRequestHandler(ProductMNG& productMNG)
: m_productMNG{productMNG}
{}

HTTPRequestHandler::~HTTPRequestHandler(){}

json HTTPRequestHandler::handleRequest(HTTPRequest& request){
   nlohmann::json json;
   std::vector<std::string> path = request.getPath();
   std::string query = request.getQuery();
  
   // Lidando com o path /api/product
   if (path.size() == 2 && path[0] == "api" && path[1] == "product"){
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

   if (path.size() == 3 && path[0] == "api" && path[1] == "product"){
      return handleRetrieveProductById(path[2]);
   }

   return handleNotFound();
}

json HTTPRequestHandler::handleRetrieveAll(){
   return this->m_productMNG.retrieveAll();
}

json HTTPRequestHandler::handleQueryProductByName(std::string name){
   return this->m_productMNG.queryProductByName(name);
}

json HTTPRequestHandler::handleRetrieveProductByReference(std::string reference){
   return this->m_productMNG.retrieveProductByReference(reference);
}

json HTTPRequestHandler::handleRetrieveProductByBarCode(std::string barcode){
   return this->m_productMNG.retrieveProductByBarCode(barcode);
}

std::string HTTPRequestHandler::handleRetrieveProductById(int& id){
   std::string response = this->m_productMNG.retrieveProductByID(id).dump();
   return response; 
}











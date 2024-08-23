#ifndef HTTPREQUESTHANDLER_1453
#define HTTPREQUESTHANDLER_1453
#include "../HTTPRequest/HTTPRequest.hpp"
#include "../../Product/ProductMNG.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include <iostream>
#include "../HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>

class HTTPRequestHandler{
   public:
      HTTPRequestHandler(ProductMNG& productMNG, HTTPResponseBuilder& responseBuilder);
      ~HTTPRequestHandler();
      std::string handleRequest(HTTPRequest& request);
   private:
      std::string handleQueryProductByName(std::string& name);
      std::string handleRetrieveAll();
      std::string handleRetrieveProductById(int& id);
      std::string handleRetrieveProductByReference(std::string& reference);
      std::string handleRetrieveProductByBarcode(std::string& barCode);
      std::string handleNotFound();
      ProductMNG& m_productMNG;
      HTTPResponseBuilder& m_responseBuilder;

};

#endif

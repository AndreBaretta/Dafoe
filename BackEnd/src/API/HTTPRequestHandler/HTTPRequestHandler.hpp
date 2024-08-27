#ifndef HTTPREQUESTHANDLER_1453
#define HTTPREQUESTHANDLER_1453
#include "../HTTPRequest/HTTPRequest.hpp"
#include "../../Product/ProductMNG.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include <stdexcept>
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
      std::string handleQueryProductByName(const std::string& name);
      std::string handleRetrieveAll();
      std::string handleRetrieveProductById(int id);
      std::string handleRetrieveProductByReference(const std::string& reference);
      std::string handleRetrieveProductByBarcode(const std::string& barCode);
      bool isNumber(const std::string& string);
      bool handleDeleteProduct(const int id);
      bool handleCreateProduct(const std::string& body);
      ProductMNG& m_productMNG;
      HTTPResponseBuilder& m_responseBuilder;

};

#endif

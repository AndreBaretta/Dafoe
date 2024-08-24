#ifndef HTTPREQUESTHANDLER_1453
#define HTTPREQUESTHANDLER_1453
#include "../HTTPRequest/HTTPRequest.hpp"
#include "../../Product/ProductMNG.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>
#include <map>
#include <vector>

class HTTPRequestHandler{
   public:
      HTTPRequestHandler(ProductMNG& productMNG);
      ~HTTPRequestHandler();
      json handleRequest(HTTPRequest& request);
   private:
      json handleQueryProductByName(std::string& name);
      json handleRetrieveAll();
      json handleRetrieveProductById(int& id);
      json handleRetrieveProductByReference(std::string& reference);
      json handleRetrieveProductByBarcode(std::string& barCode);
      ProductMNG& m_productMNG;

};

#endif

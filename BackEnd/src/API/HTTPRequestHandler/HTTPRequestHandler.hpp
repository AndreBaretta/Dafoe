#ifndef HTTPREQUESTHANDLER_1453
#define HTTPREQUESTHANDLER_1453
#include "../HTTPRequest/HTTPRequest.hpp"
#include "../../Product/ProductMNG.hpp"
#include <string>
#include <map>
#include <vector>

class HTTPRequestHandler{
   public:
      HTTPRequestHandler(ProductMNG& productMNG);
      ~HTTPRequestHandler();
      bool handleRequest(HTTPRequest& request);
   private:
      handleQueryProductByName(std::string& name);
      handleRetrieveAll();
      handleRetrieveProductById(int& id);
      handleRetrieveProductByReference(std::string& reference);
      handleRetrieveProductByBarcode(std::string& barCode);
      ProductMNG& m_productMNG;

};

#endif

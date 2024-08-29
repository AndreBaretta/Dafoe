#ifndef HTTPREQUESTHANDLER_1453
#define HTTPREQUESTHANDLER_1453
#include "../HTTPRequest/HTTPRequest.hpp"
#include "../../Product/ProductMNG.hpp"
#include "../../Category/CategoryMNG.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include "../HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>

class HTTPRequestHandler{
   public:
      HTTPRequestHandler(HTTPResponseBuilder& responseBuilder, ProductMNG& productMNG, CategoryMNG& categoryMNG);
      ~HTTPRequestHandler();
      std::string handleRequest(HTTPRequest& request);

   private:
      std::string handleQueryProductByName(const std::string& name);
      std::string handleRetrieveAllProduct();
      std::string handleRetrieveProductById(int id);
      std::string handleRetrieveProductByReference(const std::string& reference);
      std::string handleRetrieveProductByBarcode(const std::string& barCode);
      bool isNumber(const std::string& string);
      bool handleDeleteProduct(const int id);
      bool handleCreateProduct(const std::string& body);
      bool handleUpdateProduct(const int id, const std::string& body);
      bool handleCreateCategory(const std::string& body);
      bool handleUpdateCategory(const int id, const std::string& body);
      bool handleDeleteCategory(const int id);
      std::string handleRetrieveAllCategory();
      std::string handleRetrieveCategory(int id);
      ProductMNG& m_productMNG;
      HTTPResponseBuilder& m_responseBuilder;
      CategoryMNG& m_categoryMNG;
};

#endif

#ifndef HTTPREQUESTHANDLER_1453
#define HTTPREQUESTHANDLER_1453
#include "../HTTPRequest/HTTPRequest.hpp"
#include "../../Product/ProductMNG.hpp"
#include "../../Category/CategoryMNG.hpp"
#include "../../PaymentMethod/PaymentMethodMNG.hpp"
#include "../../Client/ClientMNG.hpp"
#include "../../Employee/EmployeeMNG.hpp"
#include "../../Manufacturer/ManufacturerMNG.hpp"
#include "../../SellOrder/SellOrderMNG.hpp"
#include "../../Status/StatusMNG.hpp"
#include "../../GenericProduct/GenericProductMNG.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include "../HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>

class HTTPRequestHandler{
public:
   HTTPRequestHandler(HTTPResponseBuilder& responseBuilder, ProductMNG& productMNG, CategoryMNG& categoryMNG, PaymentMethodMNG& paymentMethodMNG, ClientMNG& clientMNG,
                      EmployeeMNG& employeeMNG, ManufacturerMNG& manufacturerMNG, SellOrderMNG& sellOrderMNG, StatusMNG& statusMNG, GenericProductMNG& genericProductMNG);
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
   bool handleCreatePaymentMethod(const std::string& body);
   bool handleUpdatePaymentMethod(const int id, const std::string& body);
   bool handleDeletePaymentMethod(const int id);
   bool handleCreateClient(const std::string& body);
   bool handleUpdateClient(const int id, const std::string& name);
   bool handleDeleteClient(const int id);
   bool handleCreateEmployee(const std::string& body);
   bool handleUpdateEmployee(const int id, const std::string& name);
   bool handleDeleteEmployee(const int id);
   bool handleCreateManufacturer(const std::string& body);
   bool handleUpdateManufacturer(const int id, const std::string& body);
   bool handleDeleteManufacturer(const int id);
   bool handleCreateOrder(const std::string& body);
   bool handleUpdateOrder(const int id, const std::string& body);
   bool handleCreateStatus(const std::string& body);
   bool handleUpdateStatus(const int id, const std::string& body);
   bool handleDeleteStatus(const int id);
   bool handleCreateGenericProduct(const std::string& body);
   bool handleUpdateGenericProduct(const int id, const std::string& body);
   bool handleDeleteGenericProduct(const int id);
   std::string handleRetrieveAllCategory();
   std::string handleRetrieveCategory(const int id);
   std::string handleRetrieveAllPaymentMethod();
   std::string handleRetrievePaymentMethod(const int id);
   std::string handleRetrieveAllClient();
   std::string handleRetrieveClient(const int id);
   std::string handleRetrieveClientByName(const std::string& name);
   std::string handleRetrieveEmployeeByName(const std::string& name);
   std::string handleRetrieveEmployee(const int id);
   std::string handleRetrieveAllEmployee();
   std::string handleRetrieveAllManufacturer();
   std::string handleRetrieveManufacturer(const int id);
   std::string handleRetrieveManufacturerByName(const std::string& name);
   std::string handleRetrieveOrder(const int id);
   std::string handleRetrieveOrderByClient(const int clientId);
   std::string handleRetrieveOrderByProduct(const int productId);
   std::string handleRetrieveOrderBySeller(const int sellerId);
   std::string handleRetrieveOrderByStatus(const int statusId);
   std::string handleRetrieveAllOrder();
   std::string handleRetrieveAllStatus();
   std::string handleRetrieveStatus(const int id);
   std::string handleRetrieveGenericProductByName(const std::string& name);


   HTTPResponseBuilder& m_responseBuilder;
   ProductMNG& m_productMNG;
   PaymentMethodMNG& m_paymentMethodMNG;
   CategoryMNG& m_categoryMNG;
   ClientMNG& m_clientMNG;
   EmployeeMNG& m_employeeMNG;
   ManufacturerMNG& m_manufacturerMNG;
   SellOrderMNG& m_sellOrderMNG;
   StatusMNG& m_statusMNG;
   GenericProductMNG& m_genericProductMNG;
};

#endif

#ifndef MAIN_0704
#define MAIN_0704

#include <string>
#include <iostream>
#include "API/Server/Server.hpp"
#include "API/HTTPRequest/HTTPRequest.hpp"
#include "API/HTTPRequestParser/HTTPRequestParser.hpp"
#include "API/HTTPRequestHandler/HTTPRequestHandler.hpp"
#include "DafoeGod/DafoeGod.hpp"
#include "Product/ProductDAO.hpp"
#include "Product/ProductMNG.hpp"
#include "Category/CategoryDAO.hpp"
#include "Category/CategoryMNG.hpp"
#include "PaymentMethod/PaymentMethodDAO.hpp"
#include "PaymentMethod/PaymentMethodMNG.hpp"
#include "Client/ClientDAO.hpp"
#include "Client/ClientMNG.hpp"
#include "Manufacturer/ManufacturerDAO.hpp"
#include "Manufacturer/ManufacturerMNG.hpp"
#include "Employee/EmployeeDAO.hpp"
#include "Employee/EmployeeMNG.hpp"
#include "SellOrder/SellOrderDAO.hpp"
#include "SellOrder/SellOrderMNG.hpp"
#include "Status/StatusDAO.hpp"
#include "Status/StatusMNG.hpp"
#include "GenericProduct/GenericProductDAO.hpp"
#include "GenericProduct/GenericProductMNG.hpp"
#include "User/UserDAO.hpp"
#include "User/UserMNG.hpp"
#include "API/Token/JWToken.hpp"
#include "API/HTTPResponse/HTTPResponse.hpp"
#include "API/HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;

int main(){
   std::string secret = "Dafoe111111Secret";
   std::string issuer = "Dafoe";
   std::chrono::seconds expireTime = std::chrono::seconds(36000);
   HTTPResponseBuilder httpResponseBuilder = HTTPResponseBuilder();
   
   std::this_thread::sleep_for(std::chrono::seconds(20));

   DafoeGod dafoeGod                       = DafoeGod();
   JsonBuilder jsonBuilder                 = JsonBuilder();
   JWToken jwt                             = JWToken(secret, issuer, expireTime);
   
   // DAOs
   CategoryDAO categoryDAO                 = CategoryDAO(dafoeGod);
   ProductDAO productDAO                   = ProductDAO(dafoeGod);
   PaymentMethodDAO paymentMethodDAO       = PaymentMethodDAO(dafoeGod);
   ClientDAO clientDAO                     = ClientDAO(dafoeGod);
   EmployeeDAO employeeDAO                 = EmployeeDAO(dafoeGod);
   ManufacturerDAO manufacturerDAO         = ManufacturerDAO(dafoeGod);
   SellOrderDAO sellOrderDAO               = SellOrderDAO(dafoeGod, productDAO);
   StatusDAO statusDAO                     = StatusDAO(dafoeGod);
   GenericProductDAO genericProductDAO     = GenericProductDAO(dafoeGod);
   UserDAO userDAO                         = UserDAO(dafoeGod);
   ProductOrderDAO productOrderDAO         = ProductOrderDAO(dafoeGod);
   
   // MNGs
   ProductMNG productMNG                   = ProductMNG(productDAO, jsonBuilder);
   CategoryMNG categoryMNG                 = CategoryMNG(categoryDAO, jsonBuilder);
   PaymentMethodMNG paymentMethodMNG       = PaymentMethodMNG(paymentMethodDAO, jsonBuilder);
   ClientMNG clientMNG                     = ClientMNG(clientDAO, jsonBuilder);
   EmployeeMNG employeeMNG                 = EmployeeMNG(employeeDAO, jsonBuilder);
   ManufacturerMNG manufacturerMNG         = ManufacturerMNG(manufacturerDAO, jsonBuilder);
   SellOrderMNG sellOrderMNG               = SellOrderMNG(sellOrderDAO, productOrderDAO, productDAO, jsonBuilder);
   StatusMNG statusMNG                     = StatusMNG(statusDAO, jsonBuilder);
   GenericProductMNG genericProductMNG     = GenericProductMNG(genericProductDAO, jsonBuilder);
   UserMNG userMNG                         = UserMNG(userDAO, jwt);

   Server server                           = Server("172.19.0.3", 12354, true);

   HTTPRequestParser httpParser            = HTTPRequestParser();
   HTTPRequestHandler httpHandler          = HTTPRequestHandler(httpResponseBuilder, productMNG, categoryMNG, paymentMethodMNG, clientMNG, employeeMNG, manufacturerMNG,
                                                                sellOrderMNG, statusMNG, genericProductMNG, userMNG);

   HTTPRequest request                     = HTTPRequest();
   HTTPResponse httpResponse               = HTTPResponse();
   std::string requestString{};
   std::string response{};

   server.startListen();
   while(true){
      if(server.acceptConnection() == 0){
         requestString  = server.readRequest();
         request        = httpParser.parseRequest(requestString);
         response       = httpHandler.handleRequest(request);
         server.setResponse(response);
         server.writeResponse();
      }
   }

   return 0;
}

#endif


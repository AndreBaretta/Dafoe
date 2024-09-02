#ifndef TESTESERVER_0130
#define TESTESERVER_0130

#include <string>
#include <iostream>
#include "../Test/Test.hpp"
#include "Server/Server.hpp"
#include "HTTPRequest/HTTPRequest.hpp"
#include "HTTPRequestParser/HTTPRequestParser.hpp"
#include "HTTPRequestHandler/HTTPRequestHandler.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "../Product/ProductDAO.hpp"
#include "../Product/ProductMNG.hpp"
#include "../Category/CategoryDAO.hpp"
#include "../Category/CategoryMNG.hpp"
#include "../PaymentMethod/PaymentMethodDAO.hpp"
#include "../PaymentMethod/PaymentMethodMNG.hpp"
#include "../Client/ClientDAO.hpp"
#include "../Client/ClientMNG.hpp"
#include "../Manufacturer/ManufacturerDAO.hpp"
#include "../Manufacturer/ManufacturerMNG.hpp"
#include "../Employee/EmployeeDAO.hpp"
#include "../Employee/EmployeeMNG.hpp"
#include "../SellOrder/SellOrderDAO.hpp"
#include "../SellOrder/SellOrderMNG.hpp"
#include "../Status/StatusDAO.hpp"
#include "../Status/StatusMNG.hpp"
#include "../GenericProduct/GenericProductDAO.hpp"
#include "../GenericProduct/GenericProductMNG.hpp"
#include "../User/UserDAO.hpp"
#include "../User/UserMNG.hpp"
#include "HTTPResponse/HTTPResponse.hpp"
#include "HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(){
   Test tester = Test();
   HTTPResponseBuilder httpResponseBuilder = HTTPResponseBuilder();
   
   DafoeGod dafoeGod                       = DafoeGod();
   JsonBuilder jsonBuilder                 = JsonBuilder();
   
   // DAOs
   CategoryDAO categoryDAO                 = CategoryDAO(dafoeGod);
   ProductDAO productDAO                   = ProductDAO(dafoeGod);
   PaymentMethodDAO paymentMethodDAO       = PaymentMethodDAO(dafoeGod);
   ClientDAO clientDAO                     = ClientDAO(dafoeGod);
   EmployeeDAO employeeDAO                 = EmployeeDAO(dafoeGod);
   ManufacturerDAO manufacturerDAO         = ManufacturerDAO(dafoeGod);
   SellOrderDAO sellOrderDAO               = SellOrderDAO(dafoeGod);
   StatusDAO statusDAO                     = StatusDAO(dafoeGod);
   GenericProductDAO genericProductDAO     = GenericProductDAO(dafoeGod);
   UserDAO userDAO                         = UserDAO(dafoeGod);
   
   // MNGs
   ProductMNG productMNG                   = ProductMNG(productDAO, jsonBuilder);
   CategoryMNG categoryMNG                 = CategoryMNG(categoryDAO, jsonBuilder);
   PaymentMethodMNG paymentMethodMNG       = PaymentMethodMNG(paymentMethodDAO, jsonBuilder);
   ClientMNG clientMNG                     = ClientMNG(clientDAO, jsonBuilder);
   EmployeeMNG employeeMNG                 = EmployeeMNG(employeeDAO, jsonBuilder);
   ManufacturerMNG manufacturerMNG         = ManufacturerMNG(manufacturerDAO, jsonBuilder);
   SellOrderMNG sellOrderMNG               = SellOrderMNG(sellOrderDAO, jsonBuilder);
   StatusMNG statusMNG                     = StatusMNG(statusDAO, jsonBuilder);
   GenericProductMNG genericProductMNG     = GenericProductMNG(genericProductDAO, jsonBuilder);
   UserMNG userMNG                         = UserMNG(userDAO);

   Server server                           = Server("127.0.0.1", 12354, true);

   HTTPRequestParser httpParser            = HTTPRequestParser();
   HTTPRequestHandler httpHandler          = HTTPRequestHandler(httpResponseBuilder, productMNG, categoryMNG, paymentMethodMNG, clientMNG, employeeMNG, manufacturerMNG,
                                                                sellOrderMNG, statusMNG, genericProductMNG, userMNG);
   HTTPRequest request                     = HTTPRequest();
   HTTPResponse httpResponse               = HTTPResponse();
   std::string requestString{};
   std::string response{};

   

   // Teste criar produto

   /*
   request = tester.testCreateProduct("Oculos Do Teste", 1, 1, "codigodebastes", 3.2, 3.1, "213231", 9);
   httpHandler.handleRequest(request);

   request = tester.testCreateProduct("Oculos Do marcao", 1, 1, "marcaoocasd", 24.2, 12.3, "231213", 1);
   httpHandler.handleRequest(request);

   request = tester.testCreateProduct("Binoculo do marcao", 1, 1, "binoculo", 2.3, 4.2, "123123", 23);
   httpHandler.handleRequest(request);

   request = tester.testCreateProduct("Oculos do André", 1, 1, "12345231", 23.3,4.3,"231", 99);
   httpHandler.handleRequest(request);
   */

   // Teste criar categoria
   
  /*
   request = tester.testCreateCategory("categoria1");
   httpHandler.handleRequest(request);
   
   request = tester.testCreateCategory("categoria3");
   httpHandler.handleRequest(request);

   request = tester.testCreateCategory("cateogry");
   httpHandler.handleRequest(request);
   */

   // Teste criar metodo de pagamento

   /*
   request = tester.testCreatePaymentMethod("pmethod1");
   httpHandler.handleRequest(request);
   
   request = tester.testCreatePaymentMethod("pmethod3");
   httpHandler.handleRequest(request);

   request = tester.testCreatePaymentMethod("pmethod92");
   httpHandler.handleRequest(request);
   */

   // Teste deletar produto
   
   /*
   request = tester.testDeleteProduct(3);
   httpHandler.handleRequest(request);
   */
   
   // Teste deletar categoria
  
   /*
   request = tester.testDeleteCategory(5);
   httpHandler.handleRequest(request);
   
   request = tester.testDeleteCategory(6);
   httpHandler.handleRequest(request);
   
   request = tester.testDeleteCategory(7);
   httpHandler.handleRequest(request);
   */

   // Teste deletar metodo de pagamento
  
   /*
   request = tester.testDeletePaymentMethod(5);
   httpHandler.handleRequest(request);
   
   request = tester.testDeletePaymentMethod(6);
   httpHandler.handleRequest(request);
   
   request = tester.testDeletePaymentMethod(7);
   httpHandler.handleRequest(request);
   */

   // Teste atualizar produto
   
   /*
   request = tester.testUpdateProduct(3,"Oculos 3", 1, 1, "atualizado", 3.2,3.2, "21323132", 3);
   httpHandler.handleRequest(request);
   */

   // Teste atualizar categoria

   /*
   request = tester.testUpdateCategory(2,"Categoria7");
   httpHandler.handleRequest(request);
   */

   // Teste atualizar metodo de pagamento

   /**/
   //request = tester.testRetrievePaymentMethod(3);
   //std::cout << "\nretrievePaymentMethod(3);\n:" << httpHandler.handleRequest(request) << '\n';

   //request = tester.testUpdatePaymentMethod(3,"pme3");
   //httpHandler.handleRequest(request);
   /**/

   // Teste GET produto

   /*
   request = tester.testQueryProductByName("oculos");
   response = httpHandler.handleRequest(request);
   std::cout << "\nname=oculos:\n" << response << '\n';

   request = tester.testQueryProductByName("marcao");
   response = httpHandler.handleRequest(request);
   std::cout << "\nname=marcao:\n" << response << '\n';

   request = tester.testRetrieveProductById(3);
   response = httpHandler.handleRequest(request);
   std::cout << "\nid=3\n" << response << '\n';

   request = tester.testRetrieveProductByBarcode("binoculo");
   response = httpHandler.handleRequest(request);
   std::cout << "\nbarcode=binoculo:\n" << response << '\n';

   request = tester.testRetrieveProductByReference("123123");
   response = httpHandler.handleRequest(request);
   std::cout << "\nreference=123123:\n" << response << '\n';
   */

   // Teste GET categoria
   /*
   request = tester.testRetrieveAllCategories();
   std::cout << "\nRetrieveAll:\n" << httpHandler.handleRequest(request) << '\n';

   request = tester.testRetrieveCategory(2);
   httpHandler.handleRequest(request);
   */

   // Teste GET categoria
   /**/
   //request = tester.testRetrieveAllPaymentMethod();
   //std::cout << "\nRetrieveAll:\n" << httpHandler.handleRequest(request) << '\n';

   //request = tester.testRetrievePaymentMethod(3);
   //std::cout << "\nretrievePaymentMethod(3);\n:" << httpHandler.handleRequest(request) << '\n';
   /**/

   
   // requestString = "GET / HTTP/1.1\r\nHost: 127.0.0.1:12345\r\nUser-Agent: curl/8.9.1\r\nAccept: */*\r\n";
   // request = httpParser.parseRequest(requestString);
   // response = httpHandler.handleRequest(request);
   // std::cout << response << '\n';
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
   return 1;
}



#endif


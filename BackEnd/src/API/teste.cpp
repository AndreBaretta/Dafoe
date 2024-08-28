#ifndef TESTESERVER_0130
#define TESTESERVER_0130

#include <string>
#include <iostream>
#include "../Test/Test.hpp"
#include "TCPServer/TCPServer.hpp"
#include "HTTPRequest/HTTPRequest.hpp"
#include "HTTPRequestParser/HTTPRequestParser.hpp"
#include "HTTPRequestHandler/HTTPRequestHandler.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "../Product/ProductDAO.hpp"
#include "../Product/ProductMNG.hpp"
#include "HTTPResponse/HTTPResponse.hpp"
#include "HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(){
   Test* tester = new Test();
   HTTPResponseBuilder* httpResponseBuilder = new HTTPResponseBuilder();
   DafoeGod* dafoeGod = new DafoeGod();
   ProductDAO* productDAO = new ProductDAO(*dafoeGod);
   JsonBuilder* jsonBuilder = new JsonBuilder();
   ProductMNG* productMNG = new ProductMNG(*productDAO, *jsonBuilder);
   TCPServer* server = new TCPServer("127.0.0.1",12354);
   HTTPRequestParser* httpParser = new HTTPRequestParser();
   HTTPRequestHandler* httpHandler = new HTTPRequestHandler(*productMNG, *httpResponseBuilder);
   std::string requestString{};
   HTTPRequest request = HTTPRequest();
   HTTPResponse* httpResponse = new HTTPResponse();
   std::string response;

   // Teste criar produto
   request = tester->testCreateProduct("Oculos Do Teste", 1, 1, "codigodebarrasteste", 3.2, 3.1, "213231", 9);

   // Teste deletar produto
   // request = tester->testDeleteProduct(4);
   
   // Teste atualizar produto
   // request = tester->testUpdateProduct(5,"Oculos 3", 1, 1, "codigodebarrasatualizado", 3.2,3.2, "213231", 9);


   httpHandler->handleRequest(request);

   /*server->startListen();
   while(true){
      server->acceptConnection();
      requestString  = server->readRequest();
      *request       = httpParser->parseRequest(requestString);
      response       = httpHandler->handleRequest(*request);
      server->setResponse(response);
      server->writeResponse();
   }*/
   return 1;
}



#endif


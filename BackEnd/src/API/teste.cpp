#ifndef TESTESERVER_0130
#define TESTESERVER_0130

#include "TCPServer/TCPServer.hpp"
#include "HTTPRequest/HTTPRequest.hpp"
#include "HTTPRequestParser/HTTPRequestParser.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "../Product/Product.hpp"
#include "../Product/ProductDAO.hpp"
#include "../Product/PRoductMNG.hpp"
#include "HTTPResponse/HTTPResponse.hpp"
#include "HTTPResponseBuilder/HTTPResponseBuilder.hpp"

int main(){
   DafoeGod* dafoeGod = new DafoeGod();
   ProductDAO* productDAO = new ProductDAO(dafoeGod);
   JsonBuilder* jsonBuilder = new JsonBuilder();
   ProductMNG* productMNG = new ProductMNG(productDAO, jsonBuilder);
   TCPServer* server = new TCPServer("127.0.0.1",12354);
   HTTPRequestParser* httpParser = new HTTPRequestParser();
   HTTPRequestHandler* httpHandler = new HTTPRequestHandler()
   std::string requestString{};
   HTTPRequest* request = new HTTPRequest();
   HTTPResponse* response = new HTTPResponse();
   json
   
   s1->startListen();
   while(true){
      server->acceptConnection();
      requestString  = server->readRequest();
      request        = httpParser->parseRequest(requestString);
      response       = httpHandler->handleRequest(request);
      
      
   }
   return 1;
}



#endif


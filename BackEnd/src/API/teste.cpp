#ifndef TESTESERVER_0130
#define TESTESERVER_0130

#include <string>
#include "TCPServer/TCPServer.hpp"
#include "HTTPRequest/HTTPRequest.hpp"
#include "HTTPRequestParser/HTTPRequestParser.hpp"
#include "HTTPRequestHandler/HTTPRequestHandler.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "HTTPResponseCreator/HTTPResponseCreator.hpp"
#include "../Product/ProductDAO.hpp"
#include "../Product/ProductMNG.hpp"
#include "HTTPResponse/HTTPResponse.hpp"
#include "HTTPResponseBuilder/HTTPResponseBuilder.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(){
   DafoeGod* dafoeGod = new DafoeGod();
   ProductDAO* productDAO = new ProductDAO(*dafoeGod);
   JsonBuilder* jsonBuilder = new JsonBuilder();
   ProductMNG* productMNG = new ProductMNG(*productDAO, *jsonBuilder);
   TCPServer* server = new TCPServer("127.0.0.1",12354);
   HTTPRequestParser* httpParser = new HTTPRequestParser();
   HTTPRequestHandler* httpHandler = new HTTPRequestHandler(*productMNG);
   std::string requestString{};
   HTTPRequest* request = new HTTPRequest();
   HTTPResponse* httpResponse = new HTTPResponse();
   HTTPResponseCreator* responseCreator = new HTTPResponseCreator();
   HTTPResponseBuilder* httpResponseBuilder = new HTTPResponseBuilder();
   json response;

   
   server->startListen();
   while(true){
      server->acceptConnection();
      requestString  = server->readRequest();
      *request       = httpParser->parseRequest(requestString);
      response       = httpHandler->handleRequest(*request);
   }
   return 1;
}



#endif


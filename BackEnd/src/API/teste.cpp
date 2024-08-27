#ifndef TESTESERVER_0130
#define TESTESERVER_0130

#include <string>
#include <iostream>
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
   HTTPResponseBuilder* httpResponseBuilder = new HTTPResponseBuilder();
   DafoeGod* dafoeGod = new DafoeGod();
   ProductDAO* productDAO = new ProductDAO(*dafoeGod);
   JsonBuilder* jsonBuilder = new JsonBuilder();
   ProductMNG* productMNG = new ProductMNG(*productDAO, *jsonBuilder);
   TCPServer* server = new TCPServer("127.0.0.1",12354);
   HTTPRequestParser* httpParser = new HTTPRequestParser();
   HTTPRequestHandler* httpHandler = new HTTPRequestHandler(*productMNG, *httpResponseBuilder);
   std::string requestString{};
   HTTPRequest* request = new HTTPRequest();
   HTTPResponse* httpResponse = new HTTPResponse();
   std::string response;

   std::string path1 = "api";
   std::string path2 = "product";
   std::string metodo = "POST";
   // Teste criar produto
/*    request->setMethod(metodo);
      std::vector<std::string> path;
      path.push_back(path1);
      path.push_back(path2);
      json jsonbody;
      jsonbody["name"] = "Oculos do André";
      jsonbody["genericProduct"] = 1;
      jsonbody["manufacturer"] = 1;
      jsonbody["barcode"] = "ijkdsajdas";
      jsonbody["price"] = 6.5;
      jsonbody["cost"] = 3.0;
      jsonbody["reference"] = "321321312";
      jsonbody["quantity"] = 9;
      request->setPath(path);
      std::string bodystring = jsonbody.dump();
      request->setBody(bodystring);
      request->setVersion("HTTP/1.1");
      response = httpHandler->handleRequest(*request);
      std::cout << response << '\n';
*/
   
   server->startListen();
   while(true){
      server->acceptConnection();
      requestString  = server->readRequest();
      *request       = httpParser->parseRequest(requestString);
      response       = httpHandler->handleRequest(*request);
      server->setResponse(response);
      server->writeResponse();
   }
   return 1;
}



#endif


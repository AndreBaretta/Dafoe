#include "TCPServer/TCPServer.hpp"
#include "HTTPRequest/HTTPRequest.hpp"
#include "HTTPRequestParser/HTTPRequestParser.hpp"

int main(){
   TCPServer* s1 = new TCPServer("127.0.0.1",12354);
   HTTPRequestParser* p1 = new HTTPRequestParser();
   std::string* buffer = new std::string;

   s1->startListen();
   while(true){
      s1->acceptConnection();
      s1->readRequest(buffer);
      p1->parseRequest(buffer*);
      
   }
}











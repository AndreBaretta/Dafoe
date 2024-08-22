#include "HTTPRequestParser.hpp"
#include "../HTTPRequest/HTTPRequest.hpp"
#include <iostream>

int main(){
   HTTPRequestParser* p1 = new HTTPRequestParser();
   HTTPRequest r1;

   r1 = p1->parseRequest("GET /api/product?name=teste");

   std::cout << "metodo: " << r1.getMethod() << "\npath: " << r1.getStringPath() << "\nquery: " << r1.getQuery() << '\n';
   
   return 1;
}

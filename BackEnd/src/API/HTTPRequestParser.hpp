#ifndef HTTPREQUESTPARSER_2208
#define HTTPREQUESTPARSER_2208

#include <string>
#include <map>
#include "HTTPRequest.hpp"

class HTTPRequestParser {
   public:
      HTTPRequestParser();
   
      ~HTTPRequestParser();

      HTTPRequest parseRequest(std::string request);
};

#endif


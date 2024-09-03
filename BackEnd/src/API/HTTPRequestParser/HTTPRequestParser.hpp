#ifndef HTTPREQUESTPARSER_2208
#define HTTPREQUESTPARSER_2208

#include "../HTTPRequest/HTTPRequest.hpp"
#include <string>
#include <map>

class HTTPRequestParser {
public:
   HTTPRequestParser();

   ~HTTPRequestParser();

   HTTPRequest parseRequest(std::string request);
private:
   bool isNumber(const std::string& string);

};

#endif


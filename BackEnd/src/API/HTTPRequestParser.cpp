#include "HTTPRequestParser.hpp"
#include <sstream>
#include <iostream>

HTTPRequestParser::HTTPRequestParser(){}
HTTPRequestParser::~HTTPRequestParser(){}

HTTPRequest HTTPRequestParser::parseRequest(std::string request){
   std::string method;
   std::string path;
   std::string version;
   std::map<std::string, std::string> headers;
   std::string body;
   std::istringstream stream(request);
   std::string line;
   if(std::getline(stream,line)){
      std::istringstream lineStream(line);
      lineStream >> method >> path >> version;
   }

   while(std::getline(stream,line) && !line.empty()){
      std::string::size_type division = line.find(':');
      if(division != std::string::npos){
         std::string key = line.substr(0, division);
         std::string value = line.substr(division+2);
         headers[key] = value;
      }
   }
   
   if(stream.peek() != EOF){
      std::getline(stream,body, '\0');
   }
   HTTPRequest req = HTTPRequest(method,path,version,headers);
   req.setBody(body);
   return req;
}





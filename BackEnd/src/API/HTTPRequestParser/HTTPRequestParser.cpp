#include "HTTPRequestParser.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

HTTPRequestParser::HTTPRequestParser(){}
HTTPRequestParser::~HTTPRequestParser(){}

HTTPRequest HTTPRequestParser::parseRequest(std::string request){
   std::string method{};
   std::string tempPath{};
   std::vector<std::string> path{};
   std::string query{};
   std::string version{};
   std::map<std::string, std::string> headers{};
   std::string body{};
   std::istringstream stream{request};
   std::string line{};
   if(std::getline(stream,line)){
      std::istringstream lineStream(line);
      lineStream >> method >> tempPath >> version;
   }

   std::istringstream pathStream{tempPath};
   std::string buffer;
   std::string::size_type division;
   
   while(std::getline(stream,line) && line.find(':') != std::string::npos){
      division = line.find(':');
      if(division != std::string::npos){
         std::string key = line.substr(0, division);
         std::string value = line.substr(division+2);
         headers[key] = value;
      }
   }
   
   if(!(tempPath == "/")){
      while(std::getline(pathStream,buffer,'/')){
         if(buffer != ""){
            path.push_back(buffer);
         }
      }
      division = path[path.size() - 1].find('?');
      if(division != std::string::npos){
         query = path[path.size() - 1].substr(division+1);
         path[path.size() - 1] = path[path.size() -1].substr(0,division);
      }
   }
   try{
      if(headers.find("Content-Length") != headers.end()){
         if(stream.peek() != EOF){
            std::getline(stream, body, '\0');
            size_t length = std::stoi(headers["Content-Length"]);
            body = body.substr(0,length);
         }
      }
   }catch (std::invalid_argument const& ex)
   {
        std::cerr << "#1: " << ex.what() << '\n';
   }

   HTTPRequest req = HTTPRequest(method,path,version,headers);
   req.setBody(body);
   req.setQuery(query);
   return req;
}



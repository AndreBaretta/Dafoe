#include "HTTPRequestParser.hpp"
#include <sstream>
#include <iostream>

HTTPRequestParser::HTTPRequestParser(){}
HTTPRequestParser::~HTTPRequestParser(){}

std::string HTTPRequestParser::getPath(){
   return this->m_path;
}

std::string HTTPRequestParser::getMethod(){
   return this->m_method;
}

std::string HTTPRequestParser::getVersion(){
   return this->m_version;
}

std::string HTTPRequestParser::getHeader(std::string key){
   return this->m_headers[key];
}

std::string HTTPRequestParser::getData(){
   return this->m_data;
}

bool HTTPRequestParser::parseRequest(std::string request){
   std::istringstream stream(request);
   std::string line;
   if(std::getline(stream,line)){
      std::istringstream lineStream(line);
      lineStream >> m_method >> m_path >> m_version;
   }

   while(std::getline(stream,line) && !line.empty()){
      std::string::size_type division = line.find(':');
      if(division != std::string::npos){
         std::string key = line.substr(0, division);
         std::string value = line.substr(division+2);
         m_headers[key] = value;
      }
   }
   
   if(stream.peek() != EOF){
      std::getline(stream,m_data, '\0');
   }
   return true;
}





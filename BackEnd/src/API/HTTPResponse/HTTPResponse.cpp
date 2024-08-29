#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse(){}

HTTPResponse::HTTPResponse(std::string version, std::string statusCode, std::string statusMessage, std::map<std::string, std::string> headers, std::string body)
: m_version{version}
, m_statusCode{statusCode}
, m_statusMessage{statusMessage}
, m_headers{headers}
, m_body{body}
{
   //this->m_headers["Date"] = std::chrono::system_clock::now();
}

HTTPResponse::~HTTPResponse(){}

// Setters
bool HTTPResponse::setVersion(std::string version){
   this->m_version = version;
   return true;
}

bool HTTPResponse::setStatusCode(std::string statusCode){
   this->m_statusCode = statusCode;
   return true;
}

bool HTTPResponse::setStatusMessage(std::string statusMessage){
   this->m_statusMessage = statusMessage;
   return true;
}

bool HTTPResponse::setHeaders(std::map<std::string,std::string> headers){
   this->m_headers = headers;
   return true;
}

bool HTTPResponse::setBody(std::string body){
   this->m_body = body;
   return true;
}


// Getters
std::string HTTPResponse::getVersion(){return this->m_version;}
std::string HTTPResponse::getStatusCode(){return this->m_statusCode;}
std::string HTTPResponse::getStatusMessage(){return this->m_statusMessage;}
std::map<std::string,std::string> HTTPResponse::getHeaders(){return this->m_headers;}
std::string HTTPResponse::getBody(){return this->m_body;}




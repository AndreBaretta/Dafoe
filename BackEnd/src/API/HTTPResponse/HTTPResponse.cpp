#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse(std::string version, std::string statusCode, std::string statusMessage, std::map<std::string, std::string> headers, std::string body)
: m_version{version}
, m_statusCode{statusCode}
, m_statusMessage{statusMessage}
, m_headers{headers}
, m_body{body}
{}

HTTPResponse::~HTTPResponse(){}

// Setters
bool HTTPResponse::setVersion(std::string version){
   this->m_version = version;
}

bool HTTPResponse::setStatusCode(std::string statusCode){
   this->m_statusCode = statusCode;
}

bool HTTPResponse::setStatusMessage(std::string statusMessage){
   this->m_statusMessage = statusMessage;
}

bool HTTPResponse::setHeaders(std::map<std::string,std::string> headers){
   this->m_headers = headers;
}

bool HTTPResponse::setBody(std::string body){
   this->m_body = body;
}


// Getters
std::string getVersion(){return this->m_version;}
std::string getStatusCode(){return this->m_statusCode;}
std::string getStatusMessage(){return this->m_statusMessage;}
std::map<std::string,std::string> getHeaders(){return this->m_headers;}
std::string getBody(){return this->m_body;}




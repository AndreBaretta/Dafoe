#include "HTTPRequest.hpp"


HTTPRequest::HTTPRequest(std::string method, std::string path, std::string version, std::map<std::string, std::string> headers)
: m_method{method}
, m_path{path}
, m_version{version}
, m_headers{headers}
{}

HTTPRequest::HTTPRequest(std::string method, std::string path, std::string version, std::map<std::string, std::string> headers, std::string body)
: m_method{method}
, m_path{path}
, m_version{version}
, m_headers{headers}
, m_body{body}
{}

bool HTTPRequest::setMethod(std::string method){
   this->m_method = method;
   return true;
}

bool HTTPRequest::setPath(std::string path){
   this->m_path = path;
   return true;
}

bool HTTPRequest::setVersion(std::string version){
   this->m_version = version;
   return true;
}

bool HTTPRequest::setHeaders(std::map<std::string, std::string> headers){
   this->m_headers = headers;
   return true;
}

bool HTTPRequest::setBody(std::string body){
   this->m_body = body;
   return true;
}

std::string HTTPRequest::getMethod(){return m_method;}
std::string HTTPRequest::getPath(){return m_path;}
std::string HTTPRequest::getVersion(){return m_version;}
std::map<std::string,std::string> HTTPRequest::getHeaders(){return m_headers;}
std::string HTTPRequest::getBody(){return m_body;}














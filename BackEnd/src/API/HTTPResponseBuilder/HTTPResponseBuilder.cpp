#include "HTTPResponseBuilder.hpp"

HTTPResponseBuilder::HTTPResponseBuilder(){}

HTTPResponseBuilder::~HTTPResponseBuilder(){}

std::string HTTPResponseBuilder::buildStatusLine(HTTPResponse& response){
   std::string statusLine = response.getVersion() + " " + response.getStatusCode() + " " + response.getStatusMessage();
   return statusLine;
}

std::string HTTPResponseBuilder::buildHeaders(HTTPResponse& response){
   std::string headersString;
   std::map<std::string, std::string> headers = response.getHeaders();
   for(auto const& [key,val] : headers){
      headersString += key + ": " + val + "\r\n";
   }
   return headersString;
}

std::string HTTPResponseBuilder::buildResponseString(HTTPResponse& response){
   std::string responseString;
   responseString += buildStatusLine(response) + "\r\n";
   responseString += buildHeaders(response) + "\r\n";
   responseString += response.getBody();
   return responseString;
}



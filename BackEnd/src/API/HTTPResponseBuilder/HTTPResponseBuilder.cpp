#include "HTTPResponse.hpp"

HTTPResponseBuilder::HTTPResponseBuilder(){}

HTTPResponseBuilder::~HTTPResponseBuilder(){}

HTTPResponseBuilder::buildStatusLine(const HTTPResponse& response){
   std::string statusLine = response.getVersion() + " " + response.getStatusCode() + " " + response.getStatusMessage();
   return statusLine;
}

HTTPResponseBuilder::buildHeaders(const HTTPResponse& response){
   std::string headersString;
   std::map<std::string, std::string> headers = response.getHeaders();
   for(auto const& [key,val] : headers){
      headersString += key + ": " + val + "\r\n";
   }
   return headersString;
}

HTTPResponseBuilder::buildResponseString(const HTTPResponse& response){
   std::string responseString;
   responseString += buildStatusLine(response) + "\r\n";
   responseString += buildHeaders(response) + "\r\n";
   responseString += response.getBody();
   return responseString;
}



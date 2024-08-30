#ifndef HTTPRESPONSE_1640
#define HTTPRESPONSE_1640

#include <string>
#include <map>
//#include <chrono>

class HTTPResponse{
   public:
      HTTPResponse();
      HTTPResponse(std::string version, std::string statusCode, std::string statusMessage, std::map<std::string, std::string> headers, std::string body);
      ~HTTPResponse();
      
      // Setters
      bool setVersion(std::string version);
      bool setStatusCode(std::string statusCode);
      bool setStatusMessage(std::string statusMessage);
      bool setHeaders(std::map<std::string,std::string> headers);
      bool setBody(std::string body);

      // Getters
      std::string getVersion();
      std::string getStatusCode();
      std::string getStatusMessage();
      std::map<std::string,std::string> getHeaders();
      std::string getBody();

   private:
      std::string m_version;
      std::string m_statusCode;
      std::string m_statusMessage;
      std::map<std::string, std::string> m_headers;
      std::string m_body;
};

#endif

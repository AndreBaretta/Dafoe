#ifndef HTTPREQUEST_2208
#define HTTPREQUEST_2208
#include <string>
#include <map>

class HTTPRequest{
   public:
      HTTPRequest(std::string method, std::string path, std::string version, std::map<std::string, std::string> headers);
      HTTPRequest(std::string method, std::string path, std::string version, std::map<std::string, std::string> headers, std::string body);
      ~HTTPRequest();

      // Setters
      bool setMethod(std::string method);
      bool setPath(std::string path);
      bool setVersion(std::string version);
      bool setBody(std::string body);
      bool setHeaders(std::map<std::string, std::string> headers);

      // Getters
      std::string getMethod();
      std::string getPath();
      std::string getVersion();
      std::string getBody();
      std::map<std::string, std::string> getHeaders();

   private:
      std::string m_method;
      std::string m_path;
      std::string m_version; 
      std::map<std::string, std::string> m_headers;
      std::string m_body;
};

#endif

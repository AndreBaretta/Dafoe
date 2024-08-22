#ifndef HTTPREQUEST_2208
#define HTTPREQUEST_2208
#include <string>
#include <map>
#include <vector>

class HTTPRequest{
   public:
      HTTPRequest();
      HTTPRequest(std::string method, std::vector<std::string> path, std::string version, std::map<std::string, std::string> headers);
      HTTPRequest(std::string method, std::vector<std::string> path, std::string version, std::map<std::string, std::string> headers, std::string body);
      ~HTTPRequest();

      // Setters
      bool setPath(std::vector<std::string> path);
      bool setQuery(std::string query);
      bool setMethod(std::string method);
      bool setVersion(std::string version);
      bool setBody(std::string body);
      bool setHeaders(std::map<std::string, std::string> headers);

      // Getters
      std::vector<std::string> getPath();
      std::string getQuery();
      std::string getMethod();
      std::string getVersion();
      std::string getBody();
      std::map<std::string, std::string> getHeaders();
      std::string getStringPath();

   private:
      std::string m_method;
      std::vector<std::string> m_path;
      std::string m_query;
      std::string m_version; 
      std::map<std::string, std::string> m_headers;
      std::string m_body;
};

#endif

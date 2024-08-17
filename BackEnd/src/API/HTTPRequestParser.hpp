#ifndef HTTPREQUESTPARSER_2208
#define HTTPREQUESTPARSER_2208

#include <string>
#include <map>

class HTTPRequestParser {
public:
    HTTPRequestParser();

    ~HTTPRequestParser();

    std::string getMethod();

    std::string getPath();

    std::string getVersion();

    std::string getHeader(std::string key);

    bool parseRequest(std::string request);

private:
    std::string m_request;
    std::string m_method;
    std::string m_path;
    std::string m_version;
    std::map<std::string, std::string> m_headers;
};

#endif


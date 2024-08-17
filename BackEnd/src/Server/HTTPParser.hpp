#ifndef HTTPPARSER_2208
#define HTTPPARSER_2208

#include <string>
#include <map>

class HTTPParser {
public:
    HTTPParser();

    ~HTTPParser();

    std::string getMethod();

    std::string getPath();

    std::string getVersion();

    std::string getHeader(std::string key);

    void setRequest(std::string httpRequest);

private:
    std::string m_request;
    std::string m_method;
    std::string m_path;
    std::string m_version;
    std::map<std::string, std::string> m_headers;

    void parse();
};

#endif


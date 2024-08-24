#ifndef HTTPRESPONSEBUILDER_2130
#define HTTPRESPONSEBUILDER_2130

#include "../HTTPResponse/HTTPResponse.hpp"
#include <string>
#include <map>

class HTTPResponseBuilder{
   public:
      HTTPResponseBuilder();
      ~HTTPResponseBUilder();
      std::string buildResponseString(const HTTPResponse& response);

   private:
      std::string buildStatusLine(const HTTPResponse& response);
      std::string buildHeaders(const HTTPResponse& response);

};

#endif

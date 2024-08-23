#ifndef HTTPRESPONSEBUILDER_2130
#define HTTPRESPONSEBUILDER_2130

#include "../HTTPResponse/HTTPResponse.hpp"
#include <string>

class HTTPResponseBuilder{
   public:
      HTTPResponseBuilder();
      ~HTTPResponseBuilder();
      std::string buildResponseString(HTTPResponse& response);

   private:
      std::string buildStatusLine(HTTPResponse& response);
      std::string buildHeaders(HTTPResponse& response);

};

#endif

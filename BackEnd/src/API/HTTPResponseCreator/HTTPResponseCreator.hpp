#ifndef HTTPRESPONSECREATOR_0146
#define HTTPRESPONSECREATOR_0146
#include "../HTTPResponse/HTTPResponse.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class HTTPResponseCreator{
   public:
      HTTPResponseCreator();
      ~HTTPResponseCreator();
      HTTPResponse CreateResponse(json body);
};

#endif

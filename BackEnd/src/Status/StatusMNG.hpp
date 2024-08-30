#ifndef STATUSMNG_0254
#define STATUSMNG_0254
#include "StatusDAO.hpp"
#include "Status.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class StatusMNG{
   public:
      StatusMNG(StatusDAO& statusDAO, JsonBuilder& jsonBuilder);
      json retrieveAllStatus();
      json retrieveStatus(const int id);
      bool createStatus(const std::string& name);
      bool deleteStatus(const int id);
      bool updateStatus(const int id, const std::string& name);

   private:
      StatusDAO& m_statusDAO;
      JsonBuilder& m_jsonBuilder;
};

#endif

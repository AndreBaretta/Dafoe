#include "StatusMNG.hpp"

StatusMNG::StatusMNG(StatusDAO& statusDAO, JsonBuilder& jsonBuilder)
: m_statusDAO{statusDAO}
, m_jsonBuilder{jsonBuilder}
{}

json StatusMNG::retrieveAllStatus(){
   std::vector<Status> statuss = this->m_statusDAO.listAllStatus();
   json json = this->m_jsonBuilder.statusVectorToJson(statuss);
   return json;
}

json StatusMNG::retrieveStatus(const int id){
   std::vector<Status> status = this->m_statusDAO.retrieveStatus(id);
   json json = this->m_jsonBuilder.statusVectorToJson(status);
   return json;
}

bool StatusMNG::createStatus(const std::string& name){
   bool response = this->m_statusDAO.createStatus(name);
   return response;
}

bool StatusMNG::updateStatus(const int id, const std::string& name){
   bool response = this->m_statusDAO.updateStatus(id,name);
   return response;
}

bool StatusMNG::deleteStatus(const int id){
   bool response = this->m_statusDAO.deleteStatus(id);
   return response;
}

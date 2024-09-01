#include "ClientMNG.hpp"

ClientMNG::ClientMNG(ClientDAO& cDAO, JsonBuilder& jsonBuilder)
: m_clientDAO{cDAO}
, m_jsonBuilder{jsonBuilder}
{}

bool ClientMNG::createClient(const std::string& name, const std::string& phoneNumber, 
                             const std::string& address, const double bill){

   m_clientDAO.createClient(name, phoneNumber, address, bill);
   return true;
}

bool ClientMNG::deleteClient(const int id){
   m_clientDAO.deleteClient(id);
   return true;
}

json ClientMNG::retrieveClientByName(const std::string& name){
   std::vector<Client> clients = this->m_clientDAO.retrieveClientByName(name);
   json response = this->m_jsonBuilder.clientVectorToJson(clients);
   return response;
}

json ClientMNG::retrieveAllClient(){
   std::vector<Client> clients = this->m_clientDAO.listAllClient();
   json response = this->m_jsonBuilder.clientVectorToJson(clients);
   return response;
}

json ClientMNG::retrieveClient(const int id){
   std::vector<Client> client = m_clientDAO.retrieveClient(id);
   json response = this->m_jsonBuilder.clientVectorToJson(client);
   return response;
}


bool ClientMNG::updateClient(const int id, const std::string& name, 
                             const std::string& phoneNumber, const std::string& 
                             address, const double bill){
   m_clientDAO.updateClient(id, name, phoneNumber, address, bill);
   return true;
}



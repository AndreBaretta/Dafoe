#ifndef CLIENTMNG_0103
#define CLIENTMNG_0103
#include "ClientDAO.hpp"
#include "../API/Json/JsonBuilder.hpp"

class ClientMNG{
public:
   ClientMNG(ClientDAO& cDAO, JsonBuilder& jsonBuilder);
   bool createClient(const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);
   bool deleteClient(const int id);
   bool updateClient(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);
   json retrieveClientByName(const std::string& name);
   json retrieveAllClient();
   json retrieveClient(const int id);

private:
   ClientDAO& m_clientDAO;
   JsonBuilder& m_jsonBuilder;
};

#endif

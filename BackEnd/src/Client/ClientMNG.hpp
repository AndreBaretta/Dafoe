#ifndef CLIENTMNG_0103
#define CLIENTMNG_0103
#include "ClientDAO.hpp"

class ClientMNG{
public:
   ClientMNG(ClientDAO& cDAO);
   bool createClient(const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);
   bool deleteClient(const int id);
   bool updateClient(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);
   std::vector<Client> retrieveClientByName(const std::string& name);
   std::vector<Client> retrieveAllClient();
   Client retrieveClient(const int id);

private:
   ClientDAO& m_clientDAO;

};

#endif

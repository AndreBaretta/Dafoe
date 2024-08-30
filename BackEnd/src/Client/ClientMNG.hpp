#ifndef CLIENTMNG_0103
#define CLIENTMNG_0103
#include "ClientDAO.hpp"

class ClientMNG{
public:
   ClientMNG(ClientDAO& cDAO);
   bool createClient(const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);
   bool deleteClient(const int id);
   std::vector<Client> retrieveClient(const std::string& name);
   bool updateClient(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);

private:
   ClientDAO& m_cDAO;

};

#endif

#ifndef CLIENTDAO_0150
#define CLIENTDAO_0150
#include "Client.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include <vector>

class ClientDAO{
public:
   ClientDAO(DafoeGod& dafoe);
   bool createClient(const std::string& name, const std::string& phoneNumber = "", const std::string& address = "", const double bill = 0);
   bool deleteClient(const int id);
   std::vector<Client> retrieveClientByName(const std::string& name);
   std::vector<Client> listAllClient();
   std::vector<Client> retrieveClient(const int id);
   bool updateClient(const int id, const std::string& name, const std::string& phoneNumber = "", const std::string& address = "", const double bill = 0);

private:
   DafoeGod& m_theos;   
};


#endif

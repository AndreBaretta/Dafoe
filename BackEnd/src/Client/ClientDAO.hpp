#ifndef CLIENTDAO_0150
#define CLIENTDAO_0150
#include "Client.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include <vector>

class ClientDAO{

public:

   ClientDAO(DafoeGod& dafoe);
   bool createClient(const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);
   bool deleteClient(const int id);
   std::vector<Client> retrieveClient(const std::string& name);
   bool updateClient(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill);

private:

   static inline int s_id{};
   DafoeGod& m_theos;   
};


#endif

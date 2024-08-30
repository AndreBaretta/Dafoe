#ifndef STATUSDAO_2108
#define STATUSDAO_2108
#include "../DafoeGod/DafoeGod.hpp"
#include "Status.hpp"

class StatusDAO{
public:
   StatusDAO(DafoeGod& dafoe);
   bool createStatus(const std::string& name);
   bool updateStatus(const int id, const std::string& name);
   Status retrieveStatus(const int id);
   std::vector<Status> listAllStatus();
   bool deleteStatus(const int id);
private:
   DafoeGod& m_theos;
};

#endif

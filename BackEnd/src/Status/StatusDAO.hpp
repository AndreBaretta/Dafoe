#ifndef STATUSDAO_2108
#define STATUSDAO_2108
#include "../DafoeGod/DafoeGod.hpp"

class StatusDAO{
public:
   StatusDAO(DafoeGod& dafoe);
   bool createStatus(const std::string& name);
   bool updateStatus(const int id, const std::string& name);
private:
   DafoeGod& m_theos;
   static inline int s_id{0};
};

#endif

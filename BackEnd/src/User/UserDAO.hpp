#ifndef USERDAO_0257
#define USERDAO_0257

#include "User.hpp"
#include "../DafoeGod/DafoeGod.hpp"

class UserDAO{
public:
   UserDAO(DafoeGod& dafoe);
   bool createUser(const std::string& name, const std::string& password);
   bool deleteUser(const int id);
   bool updateUser(const int id, const std::string& name, const std::string& password);

private:
   DafoeGod& m_theos;    
};

#endif

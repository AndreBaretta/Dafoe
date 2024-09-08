#ifndef USERDAO_0257
#define USERDAO_0257

#include "User.hpp"
#include "../DafoeGod/DafoeGod.hpp"

class UserDAO{
public:
   UserDAO(DafoeGod& dafoe);
   std::string retrieveUsername(const int id);
   bool createUser(const int id, const std::string& name, const std::string& password);
   bool deleteUser(const int id);
   bool updateUsername(const int id, const std::string& name);
   bool updateUserPassword(const int id, const std::string& newPassword);
   bool validatePassword(const int id, const std::string& password);
   bool getPermission(const int id);

private:
   DafoeGod& m_theos;    
};

#endif

#ifndef USERMNG_0136
#define USERMNG_0136

#include "User.hpp"
#include "UserDAO.hpp"
#include <vector>
#include "nlohmann/json.hpp"
using json = nlohmann::json;


class UserMNG{
public:
   UserMNG(UserDAO& userDAO);
   ~UserMNG();
   // Create
   bool createUser(const std::string& name, const std::string& password);

   // Read
   json retrieveUsername(const int id);

   // Update
   bool updateUsername(const int id, const std::string& name);
   bool updateUserPassword(const int id, const std::string& password, const std::string& newPassword);

   // Delete
   bool deleteUser(const int id, const std::string& password);

private:
   UserDAO& m_userDAO;
};

#endif



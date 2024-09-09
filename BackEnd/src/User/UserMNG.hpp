#ifndef USERMNG_0136
#define USERMNG_0136

#include "User.hpp"
#include "UserDAO.hpp"
#include <vector>
#include "../API/Token/JWToken.hpp"
#include "../API/Token/Session.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;


class UserMNG{
public:
   UserMNG(UserDAO& userDAO, JWToken& jwt);
   ~UserMNG();
   // Create
   bool createUser(const int id, const std::string& name, const std::string& password);

   // Read
   json retrieveUsername(const int id);

   // Update
   bool updateUsername(const int id, const std::string& name);
   bool updateUserPassword(const int id, const std::string& password, const std::string& newPassword);

   // Delete
   bool deleteUser(const int id, const std::string& password);

   // Authentication
   bool loginUser(const int id, const std::string& password);
   bool validateSession(const std::string& token);
   std::string getToken(const int id);
   Session getSession(const std::string& token);

private:
   UserDAO& m_userDAO;
   JWToken& m_jwt;
};

#endif



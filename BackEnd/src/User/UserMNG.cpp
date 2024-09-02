#include "UserMNG.hpp"

UserMNG::UserMNG(UserDAO& userDAO)
: m_userDAO{userDAO}
{}

UserMNG::~UserMNG(){}

bool UserMNG::createUser(const std::string& name, const std::string& password){
   return this->m_userDAO.createUser(name, password);
}

bool UserMNG::updateUserPassword(const int id, const std::string& password, const std::string& newPassword){
   if(this->m_userDAO.validatePassword(id, password))
      return this->m_userDAO.updateUserPassword(id, newPassword);
   return false;
}

bool UserMNG::updateUsername(const int id, const std::string& name){
   return this->m_userDAO.updateUsername(id, name);
}

bool UserMNG::deleteUser(const int id, const std::string& password){
   if(this->m_userDAO.validatePassword(id, password))
      return this->m_userDAO.deleteUser(id);
   return false;
}

json UserMNG::retrieveUsername(const int id){
   std::string name = this->m_userDAO.retrieveUsername(id);
   json json;
   json["name"] = name;
   return json;
}




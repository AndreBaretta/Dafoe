#include "UserDAO.hpp"
#include "User.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

UserDAO::UserDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

std::string UserDAO::retrieveUsername(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select name from user where id = ?")};
   stmt->setInt(1,id);
   sql::ResultSet* res{stmt->executeQuery()};
   std::string name{};
   if(res->next()){
      return name;
   }
   name = res->getString("name").c_str();
   return name;
}

bool UserDAO::createUser(const std::string& name, const std::string& password){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select SHA2(?, 256) as hash_value")};
   stmt->setString(1, password);
   sql::ResultSet* res{stmt->executeQuery()};
   res->next();
   std::unique_ptr<sql::PreparedStatement> stam{m_theos.conn->prepareStatement("insert into user (name, password) values (?,?)")};
   stmt->setString(1, name);
   stmt->setString(2, res->getString("hash_value"));
   
   return true;
}

bool UserDAO::deleteUser(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from user where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();
   return true;
}

bool UserDAO::updateUsername(const int id, const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update user set name = ? where id = ?")};
   stmt->setString(1, name);
   stmt->setInt(2, id);
   stmt->executeQuery();

   return true;
}

bool UserDAO::updateUserPassword(const int id, const std::string& newPassword){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select SHA2(?, 256) as hash_value")};
   stmt->setString(1, newPassword);
   sql::ResultSet* res{stmt->executeQuery()};
   res->next();
   std::string hashNewPassword = res->getString("hash_value").c_str();
   std::unique_ptr<sql::PreparedStatement> stam{m_theos.conn->prepareStatement("update user set password = ? where id = ?")};
   stam->setString(1, hashNewPassword);
   stam->setInt(2,id);
   stam->executeQuery();

   return true;
}

bool UserDAO::validatePassword(const int id, const std::string& password){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select password from user where id = ?")};
   stmt->setInt(1,id);
   sql::ResultSet* res{stmt->executeQuery()};
   if(res->next()){
      std::unique_ptr<sql::PreparedStatement> stam{m_theos.conn->prepareStatement("select SHA2(?, 256) as hash_value")};
      stam->setString(1,password);
      std::string hashDBPassword = res->getString("hash_value").c_str();
      sql::ResultSet* res2{stmt->executeQuery()};
      std::string hashArgPassword = res2->getString("hash_value").c_str();
      if(hashDBPassword == hashArgPassword){
         return true;
      }
   }
   return false;
}


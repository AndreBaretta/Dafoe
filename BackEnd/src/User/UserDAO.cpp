#include "UserDAO.hpp"
#include "User.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

UserDAO::UserDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

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

bool UserDAO::updateUser(const int id, const std::string& name, const std::string& password){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select SHA2(?, 256) as hash_value")};
   
   stmt->setString(1, password);
   sql::ResultSet* res{stmt->executeQuery()};
   res->next();
   std::unique_ptr<sql::PreparedStatement> stam{m_theos.conn->prepareStatement("update user set name=?, password=? where id =?")};
   stmt->setString(1, name);
   stmt->setString(2, res->getString("hash_value"));
   stmt->setInt(3, id);

   return true;
}


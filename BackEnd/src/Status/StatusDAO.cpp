#include "StatusDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

StatusDAO::StatusDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{};

bool StatusDAO::createStatus(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into status (id, name) values (?,?)")};
   stmt->setInt(1, s_id++);
   stmt->setString(2, name);
   stmt->executeQuery();

   return true;
}

bool StatusDAO::updateStatus(const int id,const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update status set name = ? where id = ?")};
   stmt->setString(1, name);
   stmt->setInt(2, id);
   stmt->executeQuery();

   return true;
}

Status StatusDAO::retriveStatus(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from status where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   result->next();
   return Status(result->getInt("id"), result->getString("name").c_str());
}

bool StatusDAO::deleteStatus(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from status where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();
   return true;
} 

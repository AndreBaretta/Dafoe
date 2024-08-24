#include "StatusDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>

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

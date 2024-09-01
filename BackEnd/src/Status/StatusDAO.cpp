#include "StatusDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

StatusDAO::StatusDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{};

bool StatusDAO::createStatus(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into status (name) values (?)")};
   stmt->setString(1, name);
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

std::vector<Status> StatusDAO::retrieveStatus(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from status where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<Status> status{};
   if(!result->next())
      return status;
   status.push_back(Status(result->getInt("id"), result->getString("name").c_str()));
   return status;
}

std::vector<Status> StatusDAO::listAllStatus(){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from status")};
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<Status> statuses{};
   while(result->next()){
      statuses.push_back(Status(result->getInt("id"), result->getString("name").c_str()));
   }
   return statuses;
}

bool StatusDAO::deleteStatus(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from status where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();
   return true;
} 

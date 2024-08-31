#include "GenericProductDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

GenericProductDAO::GenericProductDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool GenericProductDAO::createGenericProduct(const std::string& name, const int quantity, const int category, const std::string& reference){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into genericProduct (name, quantity, category, reference) values (?,?,?,?)")};
   stmt->setString(1, name);
   stmt->setInt(2, quantity);
   stmt->setInt(3, category);
   stmt->setString(4, reference);
   stmt->executeQuery();

   return true;
}

bool GenericProductDAO::deleteGenericProduct(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from genericProduct where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

bool GenericProductDAO::updateGenericProduct(const int id, const std::string& name, const int quantity, const int category, const std::string& reference){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update genericProduct set name=?, quantity=?, category=?, reference=? where id = ?")};
   stmt->setString(1, name);
   stmt->setInt(2, quantity);
   stmt->setInt(3, category);
   stmt->setString(4, reference);
   stmt->setInt(5, id);
   stmt->executeQuery();

   return true;
}

std::vector<GenericProduct> GenericProductDAO::retrieveGenericProductByName(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from genericProduct where name like ?")};
   stmt->setString(1, '%' + name + '%');
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<GenericProduct> vec{};
   while(result->next()){
      vec.push_back(GenericProduct(result->getInt("id"), result->getString("name").c_str(), result->getInt("quantity"), result->getInt("category"), result->getString("reference").c_str()));
   }

   return vec;
}

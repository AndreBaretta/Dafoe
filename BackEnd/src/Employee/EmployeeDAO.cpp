#include "EmployeeDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

EmployeeDAO::EmployeeDAO( DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool EmployeeDAO::createEmployee(const std::string& name, const std::string& cargo){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into employee (id, name, cargo) values (?,?,?)")};
   stmt->setInt(1, s_id++);
   stmt->setString(2, name);
   stmt->setString(3, cargo);
   stmt->executeQuery();

   return true;

}

bool EmployeeDAO::deleteEmployee(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from employee where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

bool EmployeeDAO::updateEmployee(const int id, const std::string& name, const std::string& cargo){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update employee set (name = ?, cargo = ?) where id = ?")};
   stmt->setString(1, name);
   stmt->setString(2, cargo);
   stmt->setInt(3, id);
   stmt->executeQuery();

   return true;
}

std::vector<std::map<std::string, std::string>> EmployeeDAO::retrieveEmployeeByName(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from employee where name like ?")};
   stmt->setString(1, '%' + name + '%');

   sql::ResultSet* result{stmt->executeQuery()};

   std::vector<std::map<std::string, std::string>> vectores{};
   std::map<std::string, std::string> maps{};

   while(result->next()){
      maps["id"] = std::to_string(result->getInt("id"));
      maps["name"] = result->getString("name");
      maps["cargo"] = result->getString("cargo");
      vectores.push_back(maps);

   }

   return vectores;
}

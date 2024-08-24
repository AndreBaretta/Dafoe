#include "ManufacturerDAO.hpp"
#include "Manufacturer.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>
#include <vector>

ManufacturerDAO::ManufacturerDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ManufacturerDAO::createManufacturer(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into manufacturer (id, name) values (?,?)")};
   stmt->setInt(1, this->s_id++);
   stmt->setString(2, name);
   stmt->executeQuery();

   return true;
}

bool ManufacturerDAO::updateManufacturer(const int id, const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update manufacturer set name = ? where id = ?")};
   stmt->setString(1, name);
   stmt->setInt(2, id);

   stmt->executeQuery();
   return true;
}

bool ManufacturerDAO::deleteManufacturer(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from manufacturer where id = ?")};
   stmt->setInt(1, id);
   stmt->executeQuery();

   return true;
}

std::vector<Manufacturer> ManufacturerDAO::retriveByManufacturerName(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from manufacturer where name like ?")};

   stmt->setString(1, '%'+ name +'%');
   sql::ResultSet* result {stmt->executeQuery()};
   
   std::vector<Manufacturer> vec{};

   while(result->next()){
      vec.push_back(Manufacturer(result->getInt("id"), static_cast<std::string>(result->getString("name"))));
   }

   return vec;
}

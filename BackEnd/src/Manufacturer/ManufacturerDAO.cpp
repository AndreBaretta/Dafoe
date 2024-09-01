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
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into manufacturer (name) values (?)")};
   stmt->setString(1, name);
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

std::vector<Manufacturer> ManufacturerDAO::retrieveManufacturerByName(const std::string& name){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from manufacturer where name like ?")};
   stmt->setString(1, '%'+ name +'%');
   sql::ResultSet* result {stmt->executeQuery()};

   std::vector<Manufacturer> manufacturers{};

   while(result->next()){
      manufacturers.push_back(Manufacturer(result->getInt("id"), static_cast<std::string>(result->getString("name"))));
   }

   return manufacturers;
}

Manufacturer ManufacturerDAO::retrieveManufacturer(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from manufacturer where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result {stmt->executeQuery()};
   result->next();

   Manufacturer manufacturer = Manufacturer(result->getInt("id"), result->getString("name").c_str());
   
   return manufacturer;
}

std::vector<Manufacturer> ManufacturerDAO::listAllManufacturer(){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from manufacturer")};
   sql::ResultSet* result {stmt->executeQuery()};
   std::vector<Manufacturer> manufacturers{};
   
   while(result->next()){
      manufacturers.push_back(Manufacturer(result->getInt("id"), result->getString("name").c_str()));
   }
   return manufacturers;
}



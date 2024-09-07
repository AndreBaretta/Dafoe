#include "ManufacturerDAO.hpp"
#include "Manufacturer.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <memory>
#include <vector>
#include <iostream>

ManufacturerDAO::ManufacturerDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ManufacturerDAO::createManufacturer(const std::string& name){
   try{
      m_theos.prepareStatement("insert into manufacturer (name) values (?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool ManufacturerDAO::updateManufacturer(const int id, const std::string& name){
   try{
      m_theos.prepareStatement("update manufacturer set name = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool ManufacturerDAO::deleteManufacturer(const int id){
   try{
      m_theos.prepareStatement("delete from manufacturer where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Manufacturer> ManufacturerDAO::retrieveManufacturerByName(const std::string& name){
   try{
      m_theos.prepareStatement("select * from manufacturer where name like ?");
      m_theos.getStatement()->setString(1, '%'+ name +'%');
      m_theos.query(RETRIEVE);

      std::vector<Manufacturer> manufacturers{};

      while(m_theos.getResult()->next()){
         manufacturers.push_back(Manufacturer(m_theos.getResult()->getInt("id"), 
                                              m_theos.getResult()->getString("name").c_str()));
      }

      return manufacturers;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Manufacturer> ManufacturerDAO::retrieveManufacturer(const int id){
   try{
      m_theos.prepareStatement("select * from manufacturer where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(RETRIEVE);

      std::vector<Manufacturer> manufacturer{};

      if(!m_theos.getResult()->next())
         return manufacturer;
      manufacturer.push_back(Manufacturer(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str()));

      return manufacturer;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Manufacturer> ManufacturerDAO::listAllManufacturer(){
   try{
      m_theos.prepareStatement("select * from manufacturer");
      m_theos.query(RETRIEVE);

      std::vector<Manufacturer> manufacturers{};

      while(m_theos.getResult()->next()){
         manufacturers.push_back(Manufacturer(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str()));
      }

      return manufacturers;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}



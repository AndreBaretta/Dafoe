#include "GenericProductDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <memory>
#include <iostream>

GenericProductDAO::GenericProductDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool GenericProductDAO::createGenericProduct(const std::string& name, const int category){
   try{
      m_theos.prepareStatement("insert into genericProduct (name, category) values (?,?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, category);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool GenericProductDAO::deleteGenericProduct(const int id){
   try{
      m_theos.prepareStatement("delete from genericProduct where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool GenericProductDAO::updateGenericProduct(const int id, const std::string& name, const int category){
   try{
      m_theos.prepareStatement("update genericProduct set name=?, category=? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, category);
      m_theos.getStatement()->setInt(3, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<GenericProduct> GenericProductDAO::retrieveGenericProductByName(const std::string& name){
   try{
   m_theos.prepareStatement("select * from genericProduct where name like ?");
   m_theos.getStatement()->setString(1, '%' + name + '%');
   m_theos.query(RETRIEVE);

   std::vector<GenericProduct> vec{};

   while(m_theos.getResult()->next()){
      vec.push_back(GenericProduct(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str(), 
                                   m_theos.getResult()->getInt("category")));
   }

   return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<GenericProduct> GenericProductDAO::retrieveGenericProduct(){
   try{
   m_theos.prepareStatement("select * from genericProduct");
   m_theos.query(RETRIEVE);

   std::vector<GenericProduct> vec{};

   while(m_theos.getResult()->next()){
      vec.push_back(GenericProduct(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str(), 
                                   m_theos.getResult()->getInt("category")));
   }

   return vec;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

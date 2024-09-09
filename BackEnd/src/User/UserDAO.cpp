#include "UserDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <iostream>

UserDAO::UserDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

std::string UserDAO::retrieveUsername(const int id){
   try{
      m_theos.prepareStatement("select name from user where id = ?");
      m_theos.getStatement()->setInt(1,id);
      m_theos.query(RETRIEVE);

      std::string name{};
      if(m_theos.getResult()->next()){
         return name;
      }
      name = m_theos.getResult()->getString("name").c_str();

      return name;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool UserDAO::getPermission(const int id){
   try{
      m_theos.prepareStatement("select admin from user where id = ?");
      m_theos.getStatement()->setInt(1,id);
      m_theos.query(RETRIEVE);
      m_theos.getResult()->next();

      bool admin = m_theos.getResult()->getBoolean("admin");
      return admin;
   } catch(std::exception &e){
      std::cerr << e.what() << '\n';
      return false;
   }
}

bool UserDAO::createUser(const int id, const std::string& name, const std::string& password){
   try{
      m_theos.prepareStatement("select SHA2(?, 256) as hash_value");
      m_theos.getStatement()->setString(1, password);
      m_theos.query(RETRIEVE);
      m_theos.getResult()->next();

      std::string hash {m_theos.getResult()->getString("hash_value").c_str()};

      m_theos.prepareStatement("insert into user (id, name, password) values (?,?,?)");
      m_theos.getStatement()->setInt(1, id);
      m_theos.getStatement()->setString(2, name);
      m_theos.getStatement()->setString(3, hash);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool UserDAO::deleteUser(const int id){
   try{
      m_theos.prepareStatement("delete from user where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool UserDAO::updateUsername(const int id, const std::string& name){
   try{
      m_theos.prepareStatement("update user set name = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool UserDAO::updateUserPassword(const int id, const std::string& newPassword){
   try{
      m_theos.prepareStatement("select SHA2(?, 256) as hash_value");
      m_theos.getStatement()->setString(1, newPassword);
      m_theos.query(RETRIEVE);  

      if(m_theos.getResult()->next()){

         std::string hashNewPassword {m_theos.getResult()->getString("hash_value").c_str()};
         m_theos.prepareStatement("update user set password = ? where id = ?");
         m_theos.getStatement()->setString(1, hashNewPassword);
         m_theos.getStatement()->setInt(2,id);
         m_theos.query(UPDATE);

         return true;

      }

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

   return false;

}

bool UserDAO::validatePassword(const int id, const std::string& password){
   try{

      m_theos.prepareStatement("select password from user where id = ?");
      m_theos.getStatement()->setInt(1,id);
      m_theos.query(RETRIEVE);   

      if(m_theos.getResult()->next()){
         m_theos.prepareStatement("select SHA2(?, 256) as hash_value");
         m_theos.getStatement()->setString(1,password);
         std::string hashDBPassword {m_theos.getResult()->getString("hash_value").c_str()};
         m_theos.query(RETRIEVE);

         std::string hashArgPassword {m_theos.getResult()->getString("hash_value").c_str()};
         if(hashDBPassword == hashArgPassword){
            return true;
         }
      }

      return false;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}


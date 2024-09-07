#include "ClientDAO.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <iostream>
ClientDAO::ClientDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ClientDAO::createClient(const std::string& name, const std::string& phoneNumber,
                             const std::string& address, const double bill){
   try{
      std::shared_ptr<sql::PreparedStatement> stmt{m_theos.getConnection()->prepareStatement("insert into client (name, phoneNumber, address, bill) values (?,?,?,?)")};
      stmt->setString(1, name);
      stmt->setString(2, phoneNumber);
      stmt->setString(3, address);
      stmt->setDouble(4, bill);

      m_theos.query(stmt, INSERT);
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }

   return true;
}

bool ClientDAO::deleteClient(const int id){
   try{

      std::shared_ptr<sql::PreparedStatement> stmt{m_theos.getConnection()->prepareStatement("delete from client where id = ?")};
      stmt->setInt(1, id);
      m_theos.query(stmt, DELETE);

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
   return true;
}

bool ClientDAO::updateClient(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill){
   try{
      std::shared_ptr<sql::PreparedStatement> stmt{m_theos.getConnection()->prepareStatement("update client set name = ?, phoneNumber = ?, address = ?, bill = ? where id = ?")};

      stmt->setString(1, name);
      stmt->setString(2, phoneNumber);
      stmt->setString(3, address);
      stmt->setDouble(4, bill);
      stmt->setInt(5, id);
      m_theos.query(stmt, UPDATE);

   }catch(sql::SQLException& e){
      std::cerr << e.what() << '\n';
      return false;
   }
   return true;
}

std::vector<Client> ClientDAO::retrieveClientByName(const std::string& name){
   try{

      std::shared_ptr<sql::PreparedStatement> stmt{m_theos.getConnection()->prepareStatement("select * from client where name like ?")};
      stmt->setString(1, '%'+ name + '%');
      sql::ResultSet* result {m_theos.query(stmt, RETRIEVE)};

      std::vector<Client> clients{};

      while(result->next()){
         clients.push_back(Client(result->getInt("id"), static_cast<std::string>(result->getString("name")),
                                  static_cast<std::string>(result->getString("phoneNumber")), static_cast<std::string>(result->getString("address")),
                                  result->getDouble("bill")));

      }

      return clients;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw e;
   }

}

std::vector<Client> ClientDAO::listAllClient(){
   try{
      std::shared_ptr<sql::PreparedStatement> stmt{m_theos.getConnection()->prepareStatement("select * from client")};

      sql::ResultSet* result {m_theos.query(stmt, RETRIEVE)};
      std::vector<Client> clients{};
      while(result->next()){
         clients.push_back(Client(result->getInt("id"), result->getString("name").c_str(), result->getString("phoneNumber").c_str(), 
                                  result->getString("address").c_str(), result->getDouble("bill")));
      }

      return clients;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw e;
   }
}

std::vector<Client> ClientDAO::retrieveClient(const int id){
   try{
   std::shared_ptr<sql::PreparedStatement> stmt{m_theos.getConnection()->prepareStatement("select * from client where id = ?")};
   stmt->setInt(1,id);
   sql::ResultSet* result {m_theos.query(stmt, RETRIEVE)};
   std::vector<Client> client{};
   if(!result->next())
      return client;

   client.push_back(Client(result->getInt("id"), result->getString("name").c_str(), result->getString("phoneNumber").c_str(),
                           result->getString("address").c_str(), result->getDouble("bill")));
   return client;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw e;
   }
}

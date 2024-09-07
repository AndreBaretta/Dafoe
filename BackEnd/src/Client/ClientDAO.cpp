#include "ClientDAO.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <iostream>
ClientDAO::ClientDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ClientDAO::createClient(const std::string& name, const std::string& phoneNumber,
                             const std::string& address, const double bill){
   try{
      m_theos.prepareStatement("insert into client (name, phoneNumber, address, bill) values (?,?,?,?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setString(2, phoneNumber);
      m_theos.getStatement()->setString(3, address);
      m_theos.getStatement()->setDouble(4, bill);
      m_theos.query(INSERT);

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }

   return true;
}

bool ClientDAO::deleteClient(const int id){
   try{

      m_theos.prepareStatement("delete from client where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      return false;
   }
   return true;
}

bool ClientDAO::updateClient(const int id, const std::string& name, const std::string& phoneNumber, const std::string& address, const double bill){
   try{
      m_theos.prepareStatement("update client set name = ?, phoneNumber = ?, address = ?, bill = ? where id = ?");

      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setString(2, phoneNumber);
      m_theos.getStatement()->setString(3, address);
      m_theos.getStatement()->setDouble(4, bill);
      m_theos.getStatement()->setInt(5, id);
      m_theos.query(UPDATE);

   }catch(sql::SQLException& e){
      std::cerr << e.what() << '\n';
      return false;
   }
   return true;
}

std::vector<Client> ClientDAO::retrieveClientByName(const std::string& name){
   try{

      m_theos.prepareStatement("select * from client where name like ?");
      m_theos.getStatement()->setString(1, '%'+ name + '%');
      m_theos.query(RETRIEVE);

      std::vector<Client> clients{};

      while(m_theos.getResult()->next()){
         clients.push_back(Client(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str(), 
                                  m_theos.getResult()->getString("phoneNumber").c_str(), m_theos.getResult()->getString("address").c_str(), 
                                  m_theos.getResult()->getDouble("bill")));

      }

      return clients;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw e;
   }

}

std::vector<Client> ClientDAO::listAllClient(){
   try{
      m_theos.prepareStatement("select * from client");
      m_theos.query(RETRIEVE);

      std::vector<Client> clients{};
      while(m_theos.getResult()->next()){
         clients.push_back(Client(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str(), 
                                  m_theos.getResult()->getString("phoneNumber").c_str(), 
                                  m_theos.getResult()->getString("address").c_str(), m_theos.getResult()->getDouble("bill")));
      }

      return clients;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw e;
   }
}

std::vector<Client> ClientDAO::retrieveClient(const int id){
   try{
      m_theos.prepareStatement("select * from client where id = ?");
      m_theos.getStatement()->setInt(1,id);
      m_theos.query(RETRIEVE);

      std::vector<Client> client{};
      if(!m_theos.getResult()->next())
         return client;

      client.push_back(Client(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str(), 
                              m_theos.getResult()->getString("phoneNumber").c_str(),
                              m_theos.getResult()->getString("address").c_str(), m_theos.getResult()->getDouble("bill")));
      return client;
   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw e;
   }
}

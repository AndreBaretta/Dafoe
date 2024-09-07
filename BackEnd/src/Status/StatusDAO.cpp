#include "StatusDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <iostream>

StatusDAO::StatusDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{};

bool StatusDAO::createStatus(const std::string& name){
   try{
      m_theos.prepareStatement("insert into status (name) values (?)");
      m_theos.getStatement()->setString(1, name);
      m_theos.query(CREATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool StatusDAO::updateStatus(const int id,const std::string& name){
   try{
      m_theos.prepareStatement("update status set name = ? where id = ?");
      m_theos.getStatement()->setString(1, name);
      m_theos.getStatement()->setInt(2, id);
      m_theos.query(UPDATE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }

}

std::vector<Status> StatusDAO::retrieveStatus(const int id){
   try{
      m_theos.prepareStatement("select * from status where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(RETRIEVE);

      std::vector<Status> status{};
      if(!m_theos.getResult()->next())
         return status;
      status.push_back(Status(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str()));

      return status;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

std::vector<Status> StatusDAO::listAllStatus(){
   try{
      m_theos.prepareStatement("select * from status");
      m_theos.query(RETRIEVE);

      std::vector<Status> statuses{};
      while(m_theos.getResult()->next()){
         statuses.push_back(Status(m_theos.getResult()->getInt("id"), m_theos.getResult()->getString("name").c_str()));
      }

      return statuses;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
}

bool StatusDAO::deleteStatus(const int id){
   try{
      m_theos.prepareStatement("delete from status where id = ?");
      m_theos.getStatement()->setInt(1, id);
      m_theos.query(DELETE);

      return true;

   }catch(std::exception& e){
      std::cerr << e.what() << '\n';
      throw;
   }
} 

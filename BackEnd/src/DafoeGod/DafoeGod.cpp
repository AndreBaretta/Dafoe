#include "DafoeGod.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <iostream>

DafoeGod::DafoeGod(){
   try{
      this->m_driver     = sql::mariadb::get_driver_instance();
      this->m_url        = "jdbc:mariadb://172.18.0.2:3306/Dafoe";
      sql::SQLString user = "Atlas";
      sql::SQLString pwd  = "curitiba";

      this->m_conn = m_driver->connect(m_url,user,pwd);


   }catch (sql::SQLException &e) {
      std::cerr << "Error Connecting to the database: "
         << e.what() << std::endl;
   }

}

DafoeGod::~DafoeGod(){
   this->m_conn->close();
}


void DafoeGod::query(TypeOfTransaction type){

   try{ 
      switch(type){
         case RETRIEVE:
            this->m_res = m_statement->executeQuery();
            break;

         default:
            this->m_statement->executeQuery();
            break;
      }
   }catch(sql::SQLException &e){
      throw;
   }

}

bool DafoeGod::prepareStatement(const std::string& stmt){
   this->m_statement = this->m_conn->prepareStatement(stmt);
   return true;
}

sql::ResultSet* DafoeGod::getResult(){return this->m_res;}
sql::PreparedStatement* DafoeGod::getStatement(){return this->m_statement;}
sql::Connection* DafoeGod::getConnection(){return this->m_conn;}

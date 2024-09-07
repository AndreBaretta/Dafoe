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


sql::ResultSet* DafoeGod::query(std::shared_ptr<sql::PreparedStatement> queryArgument, TypeOfTransaction type){

   try{ 
   switch(type){
   RETRIEVE:
      this->m_statement = std::move(queryArgument);
      this->m_res = m_statement->executeQuery();
      return m_res;

      default:
         this->m_statement = std::move(queryArgument);
         this->m_statement->executeQuery();
         break;
      }
   }catch(sql::SQLException &e){
      throw;
   }

   return nullptr;
}


sql::Connection* DafoeGod::getConnection(){return this->m_conn;}
std::shared_ptr<sql::Statement> DafoeGod::getStatement(){return this->m_statement;}

#include "DafoeGod.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <iostream>

DafoeGod::DafoeGod(){
   try{
      this->driver     = sql::mariadb::get_driver_instance();
      this->url        = "jdbc:mariadb://172.18.0.2:3306/Dafoe";
      sql::SQLString user = "Atlas";
      sql::SQLString pwd  = "curitiba";

      this->conn = driver->connect(url,user,pwd);
      this->statement = conn->createStatement();


   }catch (sql::SQLException &e) {
      std::cerr << "Error Connecting to the database: "
         << e.what() << std::endl;
   }

}

DafoeGod::~DafoeGod(){
   this->conn->close();
}

sql::ResultSet* DafoeGod::query(const std::string& queryArgument){
   this->res = this->statement->executeQuery(queryArgument);
   return res;
}


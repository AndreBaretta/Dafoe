#include "DafoeGod.hpp"
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <iostream>

DafoeGod::DafoeGod(){
   try{
      this->driver     = sql::mariadb::get_driver_instance();
      this->url        = "jdbc:mariadb://localhost:3306/DAFOE";
      this->properties = {{
         {"user", "Atlas"},
         {"password", "curitiba"}
      }};

      this->conn = driver->connect(url, properties);
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

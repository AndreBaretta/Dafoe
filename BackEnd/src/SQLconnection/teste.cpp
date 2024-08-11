// Includes
#include <iostream>
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <memory>

// Main Process
int main(int argc, char **argv)
{
   try {
      // Instantiate Driver
      sql::Driver* driver = sql::mariadb::get_driver_instance();

      // Configure Connection
      // The URL or TCP connection string format is
      // ``jdbc:mariadb://host:port/database``.
      sql::SQLString url("jdbc:mariadb://localhost:3306/todo");

      // Use a properties map for the other connection options
      sql::Properties properties({
            {"user", "app_user"},
            {"password", "Password123!"},
         });

      // Establish Connection
      // Use a smart pointer for extra safety
      std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

      // Use Connection
   try{
      std::unique_ptr<sql::PreparedStatement> aaa(conn->prepareStatement("insert into tasks (description) value ('testing')"));
      aaa->executeQuery();
   }
   catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: "  << e.what() << std::endl;
   }

   try{
      std::unique_ptr<sql::PreparedStatement> aaa(conn->prepareStatement("select (description) from tasks where id = 1"));
      aaa->executeQuery();
   }
   catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: "  << e.what() << std::endl;
   }

      // Close Connection
      conn->close();
   }

   // Catch Exceptions
   catch (sql::SQLException& e) {
      std::cerr << "Error Connecting to the database: "
         << e.what() << std::endl;

      // Exit (Failed)
      return 1;
   }


   // Exit (Success)
   return 0;
}

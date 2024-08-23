#include "EmployeeDAO.hpp"
#include "../json.hpp"
#include <iostream>

int main(){
   DafoeGod dafoe;
   EmployeeDAO dao{dafoe};

   auto res = dao.retrieveEmployeeByName("car");

   nlohmann::json json;

   for(auto &a : res){
      json += {
         {"cargo: ", a["cargo"]},
         {"name: ", a["name"]},
         {"id: ",  a["id"]},
      };


   }

   std::cout << json;


}

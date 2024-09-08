#include <iostream>
#include "ClientDAO.hpp"
#include "../DafoeGod/DafoeGod.hpp"
int main(){
   DafoeGod dafoe{};
   ClientDAO client{dafoe};

   client.createClient("andre",  "123123123123897645", "caomouraense",1927837);
   client.deleteClient(2);
   client.updateClient(3, "paulinho",  "12312312312", "caomourae8693712nse",1927837);
   std::vector<Client> clientes {client.retrieveClientByName("rafael")};
   
   for(auto a : clientes){
      std::cout << a.getName();
   }

   return 0;
}

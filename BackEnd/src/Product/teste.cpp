#include "ProductDAO.hpp"
#include <mariadb/conncpp/Driver.hpp>
#include <iostream>
int main(){
    DafoeGod dafoe{};

    ProductDAO prod{dafoe};
    
    Product product {prod.retrieveByID(1)};

    std::cout << product.getName(); 
}

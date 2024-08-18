#include "ProductDAO.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include <iostream>

int main(){
    DafoeGod Atlas{};
    ProductDAO productDAO{Atlas};

    std::vector<Product> produtos{productDAO.retrieveByID(1)};
    
    for(auto& a : produtos){
        std::cout << a.getId() << ' ' << a.getName() << ' ' << ' ' << a.getQuantity() << '\n';
    }

    return 0;


}

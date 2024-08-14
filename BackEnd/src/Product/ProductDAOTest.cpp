#include "ProductDAO.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include <iostream>

int main(){
    DafoeGod Atlas{};
    ProductDAO productDAO{Atlas};

    std::vector<Product> produtos{productDAO.retrieveByName("carlos")};

    for(auto& a : produtos){
        std::cout << a.getId() << ' ' << a.getName() << ' ' << ' ' << a.getQuantity() << '\n';
    }

    return 0;


}

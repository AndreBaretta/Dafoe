#include "ProductDAO.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include <iostream>

int main(){
    DafoeGod Atlas{};
    ProductDAO productDAO{Atlas};

    std::string name = "oculos teste";
    int genericProduct = 1;
    int manufacturer = 1;
    std::string barcode = "stdstdstd";
    double price = 2.1;
    double cost = 3.1;
    std::string reference = "referencia";
    int quantity = 7;
    productDAO.createProduct(name,genericProduct,manufacturer,barcode,price,cost,reference,quantity);

    return 0;


}

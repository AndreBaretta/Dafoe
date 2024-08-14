#include "ProductDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>
#include <vector>

ProductDAO::ProductDAO(DafoeGod& zeus)
: m_theos{zeus}
{}

std::vector<Product> ProductDAO::retrieveByName(const std::string& namee){

    std::string search{"select * from (product) where (name) = '" + namee + "'"};
    sql::ResultSet* result {this->m_theos.query(search)};
    std::vector<Product> produtos{};
    int positionOnVec{0};
    while(result->next()){
        produtos.push_back(Product(result->getInt("id"), static_cast<std::string>(result->getString("name"))));
        ++positionOnVec;
    }
    return produtos;

}


#include "ProductOrderDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>

ProductOrderDAO::ProductOrderDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ProductOrderDAO::createProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into productOrder (sellOrder, product, quantity, discount, price) values (?,?,?,?,?,?)")};  
   stmt->setInt(1, sellOrder);
   stmt->setInt(2, product);
   stmt->setInt(3, quantity)'
   
}

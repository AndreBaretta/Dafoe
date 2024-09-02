#include "ProductOrderDAO.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

ProductOrderDAO::ProductOrderDAO(DafoeGod& dafoe)
: m_theos{dafoe}
{}

bool ProductOrderDAO::createProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into productOrder (sellOrder, product, quantity, discount, price) values (?,?,?,?,?,?)")};  
   stmt->setInt(1, sellOrder);
   stmt->setInt(2, product);
   stmt->setInt(3, quantity);
   stmt->setDouble(4, discount);
   stmt->setDouble(5, price);
   stmt->executeQuery();
   return true;
   
}

bool ProductOrderDAO::deleteProductOrder(const int sellOrder){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("delete from productOrder where sellOrder = ?")};  
   stmt->setInt(1, sellOrder);
   stmt->executeQuery();
   return true;
}

bool ProductOrderDAO::updateProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update productOrder set product=?, quantity=?, discount=?, price=? where sellOrder = ?")};  
   stmt->setInt(1, product);
   stmt->setInt(2, quantity);
   stmt->setDouble(3, discount);
   stmt->setDouble(4, price);
   stmt->setInt(5, sellOrder);
   stmt->executeQuery();
   return true;
}


std::vector<ProductOrder> ProductOrderDAO::retrieveProductOrderById(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from productOrder where sellOrder = ?")};  
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<ProductOrder> vec{};
   while(result->next()){
      vec.push_back(ProductOrder(result->getInt("sellOrder"), result->getInt("product"), result->getInt("quantity"), 
                                 result->getDouble("discount"), result->getDouble("price")));
   }
   
   return vec;
}


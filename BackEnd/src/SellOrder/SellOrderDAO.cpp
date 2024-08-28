#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include "SellOrderDAO.hpp"
#include "SellOrder.hpp"
#include <memory>



SellOrderDAO::SellOrderDAO(DafoeGod& zeus)
: m_theos{zeus}
{}


bool SellOrderDAO::createOrder(const int clientId, const int sellerId,
                               const int deliveredBy, const int status, 
                               const int paymentMethod, const std::string& date, 
                               const double price){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into sellOrder (id, client, seller, deliveredBy, status, paymentMethod, date, price) values (?,?,?,?,?,?,?,?)")};

   stmt->setInt(1, s_id++);
   stmt->setInt(2, clientId);
   stmt->setInt(3, sellerId);
   stmt->setInt(4, deliveredBy);
   stmt->setInt(5, status);
   stmt->setInt(6, paymentMethod);
   stmt->setString(7, date);
   stmt->setDouble(8, price);
   stmt->executeQuery();

   return true;
}


bool SellOrderDAO::updateOrder(const int id, const int clientId, const int sellerId,
                               const int deliveredBy, const int status, 
                               const int paymentMethod, const std::string& date, 
                               const double price){

   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("update sellOrder set client = ?, seller = ?, deliveredBy = ?, status = ?, paymentMethod = ?, date = ?, price = ? where id = ?")};

   stmt->setInt(1, id);
   stmt->setInt(2, clientId);
   stmt->setInt(3, sellerId);
   stmt->setInt(4, deliveredBy);
   stmt->setInt(5, status);
   stmt->setInt(6, paymentMethod);
   stmt->setString(7, date);
   stmt->setDouble(8, price);
   stmt->executeQuery();

   return true;
}

SellOrder SellOrderDAO::retrieveOrderById(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   result->next();
   return SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("deliveredBy"), result->getInt("status"), result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price"));
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByClient(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where client = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
   vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("delivereBy"), result->getInt("status"), result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   }

   return vec;
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByProduct(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where product = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
      vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("delivereBy"), result->getInt("status"), result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   }

   return vec;
}


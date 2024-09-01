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
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into sellOrder (client, seller, deliveredBy, status, paymentMethod, date, price) values (?,?,?,?,?,?,?)")};

   stmt->setInt(1, clientId);
   stmt->setInt(2, sellerId);
   stmt->setInt(3, deliveredBy);
   stmt->setInt(4, status);
   stmt->setInt(5, paymentMethod);
   stmt->setString(6, date);
   stmt->setDouble(7, price);
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

std::vector<SellOrder> SellOrderDAO::retrieveOrderById(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> sellOrder{};
   if(!result->next())
      return sellOrder;
   sellOrder.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("deliveredBy"), result->getInt("status"), 
                                 result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   return sellOrder;
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByClient(const int clientId){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where client = ?")};
   stmt->setInt(1, clientId);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
   vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("delivereBy"), result->getInt("status"), result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   }

   return vec;
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByProduct(const int productId){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where product = ?")};
   stmt->setInt(1, productId);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
      vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("delivereBy"), result->getInt("status"), result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   }

   return vec;
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderByStatus(const int statusId){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where status = ?")};
   stmt->setInt(1, statusId);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
   vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("delivereBy"), result->getInt("status"), result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   }

   return vec;
}

std::vector<SellOrder> SellOrderDAO::retrieveOrderBySeller(const int sellerId){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where seller = ?")};
   stmt->setInt(1, sellerId);
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
      vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("delivereBy"), result->getInt("status"), 
                              result->getInt("paymentMethod"), static_cast<std::string>(result->getString("date")), result->getDouble("price")));
   }

   return vec;
}

std::vector<SellOrder> SellOrderDAO::listAllSellOrder(){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder")};
   sql::ResultSet* result{stmt->executeQuery()};
   std::vector<SellOrder> vec{};
   while(result->next()){
      vec.push_back(SellOrder(result->getInt("id"), result->getInt("client"), result->getInt("seller"), result->getInt("deliveredBy"), result->getInt("status"),
                    result->getInt("paymentMethod"), result->getString("date").c_str(), result->getDouble("price")));
   }
   return vec;
}



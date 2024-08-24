#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include "SellOrderDao.hpp"
#include <memory>



OrderDAO::OrderDAO(DafoeGod& zeus)
: m_theos{zeus}
{}

bool OrderDAO::createOrderNormal(const int clientId, const double price, const std::string& date, std::vector<Product>){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into sellOrder (id, client, status, paymentMethod, date, price) values (?,?,?,?,?,?)")};



}

SellOrder OrderDAO::retrieveOrderById(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result {stmt->executeQuery()};
   result->next();

   std::unique_ptr<sql::PreparedStatement> stam{m_theos.conn->prepareStatement("select (product, quantity) from productOrder where sellOrder = ?")};
   stam->setInt(1, result->getInt("id"));
   sql::ResultSet* anotherResult {stam->executeQuery()};

   std::vector<Product> resultsIds{};
   while(anotherResult->next()){
      std::unique_ptr<sql::PreparedStatement> anotherStam{m_theos.conn->prepareStatement("select * from product where id = ?")};
      anotherStam->setInt(1, anotherResult->getInt("id"));
      sql::ResultSet* anotherResult2 {anotherStam->executeQuery()};
      anotherResult2->next();

      resultsIds.push_back(Product(anotherResult2->getInt("id"), static_cast<std::string>(anotherResult2->getString("name")), anotherResult->getInt("quantity"),anotherResult2->getInt("category")));

   }

   std::chrono::year_month_day dia{static_cast<std::chrono::year>(stringToDate[0]), static_cast<std::chrono::month>(stringToDate[1]), static_cast<std::chrono::day>(stringToDate[2])};
   return Order(result->getInt("id"),  result->getInt("client"), result->getDouble("price"), dia, resultsIds);

}

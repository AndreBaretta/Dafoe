#include "OrderDAO.hpp"
#include <mariadb/conncpp/PreparedStatement.hpp>
#include <mariadb/conncpp/ResultSet.hpp>
#include <memory>

static std::array<int, 3> parse(std::string str){
    std::array<int, 3> arr{};
    int arrPos{0};
    std::string temp{};
    for(int i {0}; i <= str.size(); ++i){
        
        if (i == str.size() || str[i] == '-'){
            arr[arrPos] = std::stoi(temp);
            temp.clear();
            arrPos++;
        }else{
            temp += str[i];
        }
    }

    return arr;
}

OrderDAO::OrderDAO(DafoeGod& zeus)
: m_theos{zeus}
{}

bool OrderDAO::createOrderNormal(const int clientId, const double price, year_month_price date, std::vector<Product>){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("insert into sellOrder (id, client, status, paymentMethod, date, price) values (?,?,?,?,?,?)")};

   
   
}

Order OrderDAO::retrieveOrderById(const int id){
   std::unique_ptr<sql::PreparedStatement> stmt{m_theos.conn->prepareStatement("select * from sellOrder where id = ?")};
   stmt->setInt(1, id);
   sql::ResultSet* result {stmt->executeQuery()};
   result->next();
   std::array<int, 3> stringToDate{parse(static_cast<std::string>(result->getString("date")))};

   std::unique_ptr<sql::PreparedStatement> stam{m_theos.conn->prepareStatement("select (product, quantity) from productOrder where sellOrder = ?")};
   stam->setInt(1, result->getInt("id"));
   sql::ResultSet* anotherResult {stam->executeQuery()};

   std::vector<Product> resultsIds{};
   while(anotherResult->next()){
      std::unique_ptr<sql::PreparedStatement> anotherStam{m_theos.conn->prepareStatement("select * from product where id = ?")};
      sql::ResultSet* anotherResult2 {anotherStam->executeQuery()};
      anotherResult2->next();

      resultsIds.push_back(Product(anotherResult2->getInt("id"), static_cast<std::string>(anotherResult2->getString("name")), anotherResult->getInt("quantity"),anotherResult2->getInt("category")));

   }

   std::chrono::year_month_day dia{static_cast<std::chrono::year>(stringToDate[0]), static_cast<std::chrono::month>(stringToDate[1]), static_cast<std::chrono::day>(stringToDate[2])};
   return Order(result->getInt("id"),  result->getInt("client"), result->getDouble("price"), dia, resultsIds);
   
}

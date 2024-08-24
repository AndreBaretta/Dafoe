#ifndef ORDERDAO_1610
#define ORDERDAO_1610

#include "../Product/Product.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "SellOrder.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

class OrderDAO{
public:
   OrderDAO(DafoeGod& zeus);

   bool createOrderEnshrined(const int clientId, const double price, const std::string& date, std::vector<Product> products);
   bool createOrderNormal(const int clientId, const double price, const std::string& date, std::vector<Product> products);
   bool deleteOrder(const int id);
   bool updateOrder(const int id, const int clientId, const double price, const std::string& date, std::vector<Product> products);
   SellOrder retrieveOrderById(const int id);
   std::vector<SellOrder> retrieveOrderByClient(const int id);
   std::vector<SellOrder> retrieveOrderByProduct(const int id);
   
private:
   static inline int s_id{0};
   DafoeGod& m_theos;
   sql::ResultSet* result{};
};

#endif

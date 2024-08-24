#ifndef ORDERDAO_1610
#define ORDERDAO_1610

#include "Order.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

class OrderDAO{
public:
   OrderDAO(DafoeGod& zeus);

   bool createOrderEnshrined(const int clientId, const double price, year_month_day date, std::vector<Product> products);
   bool createOrderNormal(const int clientId, const double price, year_month_day date, std::vector<Product> products);
   bool deleteOrder(const int id);
   bool updateOrder(const int id, const int clientId, const double price, year_month_day date, std::vector<Product> products);
   Order retrieveOrderById(const int id);
   std::vector<Order> retrieveOrderByClient(const int id);
   std::vector<Order> retrieveOrderByProduct(const int id);
   
private:
   static inline int s_id{0};
   DafoeGod& m_theos;
   sql::ResultSet* result{};
};

#endif

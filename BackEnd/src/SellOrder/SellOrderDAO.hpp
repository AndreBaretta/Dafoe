#ifndef ORDERDAO_1610
#define ORDERDAO_1610

#include "../Product/Product.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "SellOrder.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

class SellOrderDAO{
public:
   SellOrderDAO(DafoeGod& zeus);

   bool createOrder(const int clientId, const int sellerId,
                    const int deliveredBy, const int status, 
                    const int paymentMethod, const std::string& date, const double price);

   bool updateOrder(const int id, const int clientId, const int sellerId,
                    const int deliveredBy, const int status, 
                    const int paymentMethod, const std::string& date, const double price);

   SellOrder retrieveOrderById(const int id);
   std::vector<SellOrder> retrieveOrderByClient(const int id);
   std::vector<SellOrder> retrieveOrderByProduct(const int id);
   
private:
   DafoeGod& m_theos;
};

#endif

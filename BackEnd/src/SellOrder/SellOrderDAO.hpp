#ifndef ORDERDAO_1610
#define ORDERDAO_1610

#include "../Product/Product.hpp"
#include "../DafoeGod/DafoeGod.hpp"
#include "SellOrder.hpp"
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/ResultSet.hpp>

class SellOrderDAO{
public:
   SellOrderDAO(DafoeGod& zeus, ProductDAO& pDAO);

   int createOrder(const int clientId, const int sellerId, const int status, 
                    const int paymentMethod, const std::string& date, const double price);

   bool updateOrder(const int id, const int clientId, const int sellerId, const int status, 
                    const int paymentMethod, const std::string& date, const double price);

   //bool addProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price);
   //bool removeProductOrder(const int sellOrder, const int product);
   //bool updateProductOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price);

   std::vector<SellOrder> retrieveOrderById(const int id);
   std::vector<SellOrder> retrieveOrderByClient(const int clientId);
   std::vector<SellOrder> retrieveOrderByProduct(const int productId);
   std::vector<SellOrder> retrieveOrderByStatus(const int statusId);
   std::vector<SellOrder> retrieveOrderBySeller(const int sellerId);
   std::vector<SellOrder> listAllSellOrder();
   
private:
   DafoeGod& m_theos;
   ProductDAO& m_pDAO;
};

#endif

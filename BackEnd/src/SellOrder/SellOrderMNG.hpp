#ifndef SELLORDERMNG_2318
#define SELLORDERMNG_2318
#include "SellOrderDAO.hpp"
#include "../API/Json/JsonBuilder.hpp"

class SellOrderMNG{
public:
   SellOrderMNG(SellOrderDAO& sellOrderDAO, JsonBuilder& jsonBuilder);
   bool createOrder(const int clientId, const int sellerID, const int deliveredBy, const int statusId,
                    const int paymentMethod, const std::string& date, const double price);
   bool updateOrder(const int id, const int clientId, const int sellerId, const int deliveredBy, const int statusId,
                    const int paymentMethod, const std::string& date, const double price);
   json retrieveOrder(const int id);
   json retrieveOrderByClient(const int clientId);
   json retrieveOrderByProduct(const int productId);
   json retrieveOrderBySeller(const int sellerId);
   json retrieveOrderByStatus(const int statusId);
   json retrieveAllSellOrder();

private:
   SellOrderDAO& m_sellOrderDAO;
   JsonBuilder& m_jsonBuilder;
};

#endif

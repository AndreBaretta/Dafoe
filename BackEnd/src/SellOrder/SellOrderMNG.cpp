#include "SellOrderMNG.hpp"

SellOrderMNG::SellOrderMNG(SellOrderDAO& sellOrderDAO, JsonBuilder& jsonBuilder)
: m_sellOrderDAO{sellOrderDAO}
, m_jsonBuilder{jsonBuilder}
{}

bool SellOrderMNG::createOrder(const int clientId, const int sellerId, const int deliveredBy, const int statusId,
                               const int paymentMethod, const std::string& date, const double price){
   return this->m_sellOrderDAO.createOrder(clientId, sellerId, deliveredBy, statusId, paymentMethod, date, price);
}

bool SellOrderMNG::updateOrder(const int id, const int clientId, const int sellerId, const int deliveredBy, 
                               const int statusId, const int paymentMethod, const std::string& date, const double price){
   return this->m_sellOrderDAO.updateOrder(id,clientId,sellerId,deliveredBy,statusId,paymentMethod,date,price);
}

json SellOrderMNG::retrieveOrder(const int id){
   SellOrder sellOrder = this->m_sellOrderDAO.retrieveOrderById(id);
   json response = this->m_jsonBuilder.sellOrderToJson(sellOrder);
   return response;
}

json SellOrderMNG::retrieveOrderByProduct(const int productId){
   std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderByProduct(productId);
   json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
   return response;
}

json SellOrderMNG::retrieveOrderByClient(const int clientId){
   std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderByClient(clientId);
   json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
   return response;
}

json SellOrderMNG::retrieveOrderBySeller(const int sellerId){
   std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderBySeller(sellerId);
   json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
   return response;
}

json SellOrderMNG::retrieveOrderByStatus(const int statusId){
   std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderByStatus(statusId);
   json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
   return response;
}

json SellOrderMNG::retrieveAllSellOrder(){
   std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.listAllSellOrder();
   json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
   return response;
}




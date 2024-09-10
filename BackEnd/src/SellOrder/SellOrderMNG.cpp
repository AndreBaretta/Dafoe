#include "SellOrderMNG.hpp"

SellOrderMNG::SellOrderMNG(SellOrderDAO& sellOrderDAO, ProductOrderDAO& productOrderDAO, JsonBuilder& jsonBuilder)
: m_sellOrderDAO{sellOrderDAO}
, m_productOrderDAO{productOrderDAO}
, m_jsonBuilder{jsonBuilder}
{}

bool SellOrderMNG::createOrder(const int clientId, const int sellerId, const int statusId,
                               const int paymentMethod, const std::string& date, const double price, json products){

   int sellOrder = this->m_sellOrderDAO.createOrder(clientId, sellerId, statusId, paymentMethod, date, price);
   std::vector<ProductOrder> productVector = this->m_jsonBuilder.jsonToProductOrderVector(products, sellOrder);
   for(auto e: productVector){
      if(!this->m_productOrderDAO.createProductOrder(e.getSellOrder(),e.getProduct(), e.getQuantity(), e.getDiscount(), e.getPrice()))
         return false;
   }
   return true;
}

bool SellOrderMNG::updateOrder(const int id, const int clientId, const int sellerId, 
                               const int statusId, const int paymentMethod, const std::string& date, const double price){
   return this->m_sellOrderDAO.updateOrder(id,clientId,sellerId,statusId,paymentMethod,date,price);
}

bool SellOrderMNG::addProductToOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   return this->m_productOrderDAO.createProductOrder(sellOrder, product, quantity, discount, price);
}

bool SellOrderMNG::updateProduct(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   return this->m_productOrderDAO.updateProductOrder(sellOrder, product, quantity, discount, price);
}

bool SellOrderMNG::removeProductFromOrder(const int sellOrder, const int product){
   return this->m_productOrderDAO.deleteProductOrder(sellOrder, product);
}

json SellOrderMNG::retrieveOrder(const int id){
   try{
      std::vector<ProductOrder> sellOrder = this->m_productOrderDAO.retrieveAllProductOrder(id);
      json response = this->m_jsonBuilder.productOrderVectorToJson(sellOrder);
      return response;
   }catch(std::exception &e){
      throw;
   }
}

json SellOrderMNG::retrieveOrderByProduct(const int productId){
   try{
      std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderByProduct(productId);
      json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
      return response;
   }catch(std::exception &e){
      throw;
   }
}

json SellOrderMNG::retrieveOrderByClient(const int clientId){
   try{
      std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderByClient(clientId);
      json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
      return response;
   }catch(std::exception &e){
      throw;
   }
}

json SellOrderMNG::retrieveOrderBySeller(const int sellerId){
   try{
      std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderBySeller(sellerId);
      json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
      return response;
   }catch(std::exception &e){
      throw;
   }
}

json SellOrderMNG::retrieveOrderByStatus(const int statusId){
   try{
      std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.retrieveOrderByStatus(statusId);
      json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
      return response;
   }catch(std::exception &e){
      throw;
   }
}

json SellOrderMNG::retrieveAllSellOrder(){
   try{
      std::vector<SellOrder> sellOrders = this->m_sellOrderDAO.listAllSellOrder();
      json response = this->m_jsonBuilder.sellOrderVectorToJson(sellOrders);
      return response;
   }catch(std::exception &e){
      throw;
   }
}




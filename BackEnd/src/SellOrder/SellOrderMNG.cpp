#include "SellOrderMNG.hpp"

SellOrderMNG::SellOrderMNG(SellOrderDAO& sellOrderDAO, ProductOrderDAO& productOrderDAO, ProductDAO& productDAO, JsonBuilder& jsonBuilder)
: m_sellOrderDAO{sellOrderDAO}
, m_productOrderDAO{productOrderDAO}
, m_productDAO{productDAO}
, m_jsonBuilder{jsonBuilder}
{}

bool SellOrderMNG::createOrder(const int clientId, const double price, const std::vector<int>& product,
                               const std::vector<int>& quantity, std::vector<double>& priceArray, Session session){

   auto now = std::chrono::system_clock::now();
   std::time_t time_now = std::chrono::system_clock::to_time_t(now);
   std::stringstream ss;
   ss << std::put_time(std::localtime(&time_now), "%Y-%m-%d");
   std::string time_str = ss.str();
   int sellerId = session.getId();
   int statusId = 1;
   int paymentMethod = 1;
   int sellOrder = this->m_sellOrderDAO.createOrder(clientId, sellerId, statusId, paymentMethod, time_str, price, product, quantity, priceArray);
   if(sellOrder == -1)
      return false;
   return true;
}

bool SellOrderMNG::updateOrder(const int id, const int clientId, const int sellerId, 
                               const int statusId, const int paymentMethod, const std::string& date, const double price, const int product, const int quantity){
   return this->m_sellOrderDAO.updateOrder(id,clientId,sellerId,statusId,paymentMethod,date,price,product,quantity);
}

bool SellOrderMNG::addProductToOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price){
   try{
      if(this->m_productOrderDAO.createProductOrder(sellOrder, product, quantity, discount, price)){
         if(!this->m_productDAO.updateQuantity(product,quantity)){
            this->m_productOrderDAO.deleteProductOrder(sellOrder, product);
         }
         return true;
      }
      return false;
   }catch(std::exception &e){
      return false;
   }
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

#ifndef SELLORDERMNG_2318
#define SELLORDERMNG_2318
#include "SellOrderDAO.hpp"
#include "../API/Json/JsonBuilder.hpp"
#include "../ProductOrder/ProductOrderDAO.hpp"
#include "../Product/ProductDAO.hpp"
#include "../API/Token/Session.hpp"

class SellOrderMNG{
public:
   SellOrderMNG(SellOrderDAO& sellOrderDAO, ProductOrderDAO& productOrderDAO, ProductDAO& productDAO, JsonBuilder& jsonBuilder);
   bool createOrder(const int clientId, const double price, const std::vector<int>& product,
                    const std::vector<int>& quantity, std::vector<double>& priceArray, Session session);

   bool updateOrder(const int id, const int clientId, const int sellerId, const int statusId, const int paymentMethod, 
                    const std::string& date, const double price, const int product, const int quantity);
   bool addProductToOrder(const int sellOrder, const int product, const int quantity, const double discount, const double price);
   bool updateProduct(const int sellOrder, const int product, const int quantity, const double discount, const double price);
   bool removeProductFromOrder(const int sellOrder, const int product);
   json retrieveOrder(const int id);
   json retrieveOrderByClient(const int clientId);
   json retrieveOrderByProduct(const int productId);
   json retrieveOrderBySeller(const int sellerId);
   json retrieveOrderByStatus(const int statusId);
   json retrieveAllSellOrder();
 //  bool updateStatus(const int sellOrder, const int status);

private:
   SellOrderDAO& m_sellOrderDAO;
   ProductOrderDAO& m_productOrderDAO;
   ProductDAO& m_productDAO;
   JsonBuilder& m_jsonBuilder;
};

#endif

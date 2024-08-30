#include "ProductOrder.hpp"

ProductOrder::ProductOrder(int sellOrder, int product, int quantity, double discount, double price)
: m_SellOrder(sellOrder)
, m_product(product)
, m_quantity(quantity)
, m_discount(discount)
, m_price(price) 
{}

bool ProductOrder::setSellOrder(int sellOrder){
   m_SellOrder = sellOrder;
   return true;
}

bool ProductOrder::setProduct(int product){
   m_product = product;
   return true;
}

bool ProductOrder::setQuantity(int quantity){
   m_quantity = quantity;
   return true;
}

bool ProductOrder::setDiscount(double discount){
   m_discount = discount;
   return true;
}

bool ProductOrder::setPrice(double price){
   m_price = price;
   return true;
}

int ProductOrder::getSellOrder() const{
   return m_SellOrder;
}

int ProductOrder::getProduct() const{
   return m_product;
}

int ProductOrder::getQuantity() const{
   return m_quantity;
}

double ProductOrder::getDiscount() const{
   return m_discount;
}

double ProductOrder::getPrice() const{
   return m_price;
}

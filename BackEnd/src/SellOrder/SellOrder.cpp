#include "SellOrder.hpp"
SellOrder::SellOrder(int id, int clientId, int sellerId, int status, int paymentMethod, const std::string& date, double price, const int product, const int quantity)
: m_id(id)
, m_clientId(clientId)
, m_sellerId(sellerId)
, m_statusId(status)
, m_paymentMethod(paymentMethod)
, m_date(date)
, m_price(price) 
, m_product(product)
, m_quantity(quantity)
{}

bool SellOrder::setId(int id){
   m_id = id;
   return true;
}

bool SellOrder::setClient(int id){
   m_clientId = id;
   return true;
}

bool SellOrder::setSeller(int id){
   m_sellerId = id;
   return true;
}

bool SellOrder::setPrice(double price){
   m_price = price;
   return true;
}

bool SellOrder::setDate(const std::string& date){
   m_date = date;
   return true;
}

bool SellOrder::setStatusId(int id){
   this->m_statusId = id;
   return true;
}

bool SellOrder::setProduct(int id){
   this->m_product = id;
   return true;
}

bool SellOrder::setQuantity(int quantity){
   this->m_quantity = quantity;
   return true;
}

int SellOrder::getId() const{
   return m_id;
}

int SellOrder::getClientId() const{
   return m_clientId;
}

int SellOrder::getSellerId() const{
   return m_sellerId;
}

int SellOrder::getStatusId() const{
   return m_statusId;
}

int SellOrder::getPaymentMethod() const{
   return m_paymentMethod;
}

double SellOrder::getPrice() const{
   return m_price;
}

int SellOrder::getProduct(){
   return m_product;
}

int SellOrder::getQuantity(){
   return m_quantity;
}

std::string SellOrder::getDate() const{
   return m_date;
}

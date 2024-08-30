#include "SellOrder.hpp"
SellOrder::SellOrder(int id, int clientId, int sellerId, int deliveredBy, int status, int paymentMethod, const std::string& date, double price)
: m_id(id)
, m_clientId(clientId)
, m_sellerId(sellerId)
, m_deliveredBy(deliveredBy)
, m_status(status)
, m_paymentMethod(paymentMethod)
, m_date(date)
, m_price(price) 
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

bool SellOrder::setDeliveredBy(int id){
    m_deliveredBy = id;
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

int SellOrder::getId() const{
    return m_id;
}

int SellOrder::getClientId() const{
    return m_clientId;
}

int SellOrder::getSellerId() const{
    return m_sellerId;
}

int SellOrder::getDeliveredBy() const{
    return m_deliveredBy;
}

int SellOrder::getStatus() const{
    return m_status;
}

int SellOrder::getPaymentMethod() const{
    return m_paymentMethod;
}

double SellOrder::getPrice() const{
    return m_price;
}

const std::string& SellOrder::getDate() const{
    return m_date;
}

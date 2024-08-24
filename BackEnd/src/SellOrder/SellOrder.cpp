#include "SellOrder.hpp"

SellOrder::SellOrder(int id, int clientId, int sellerId, int deliveredBy, int status, int paymentMethod, std::string date, double price)
: m_id{id}
, m_clientId{clientId}
, m_sellerId{sellerId}
, m_deliveredBy{deliveredBy}
, m_status{status}
, m_paymentMethod{paymentMethod}
, m_date{date}
, m_price{price}
{}


